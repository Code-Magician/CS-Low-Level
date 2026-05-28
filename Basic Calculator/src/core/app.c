#include "app.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "../ui/button.h"
#include "../ui/text.h"

#include "../utils/constants.h"
#include "../utils/colors.h"

#include "calculator.h"

void RunApplication()
{
    // SDL Init
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log(
            "SDL Init Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // TTF Init
    if (TTF_Init() == false)
    {
        SDL_Log(
            "TTF Init Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // Window
    SDL_Window* window =
        SDL_CreateWindow(
            "Beautiful Calculator",
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0
        );

    if (!window)
    {
        SDL_Log(
            "Window Creation Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // Renderer
    SDL_Renderer* renderer =
        SDL_CreateRenderer(
            window,
            NULL
        );

    if (!renderer)
    {
        SDL_Log(
            "Renderer Creation Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // Font
    TTF_Font* font =
        TTF_OpenFont(
            "assets/font.ttf",
            32
        );

    if (!font)
    {
        SDL_Log(
            "Font Load Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // Labels
    const char* labels[16] =
    {
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0",".","=","+"
    };

    // Buttons
    Button buttons[16];

    for (int i = 0; i < 16; i++)
    {
        int row = i / 4;
        int col = i % 4;

        SDL_Color normal = BUTTON_COLOR;
        SDL_Color hover = BUTTON_HOVER;

        if (strchr("+-*/=", labels[i][0]))
        {
            normal = OPERATOR_COLOR;
            hover = OPERATOR_HOVER;
        }

        buttons[i] = (Button)
        {
            .x =
                GRID_START_X +
                col * (
                    BUTTON_WIDTH +
                    BUTTON_PADDING
                ),

            .y =
                GRID_START_Y +
                row * (
                    BUTTON_HEIGHT +
                    BUTTON_PADDING
                ),

            .width = BUTTON_WIDTH,
            .height = BUTTON_HEIGHT,

            .color = normal,
            .hoverColor = hover,

            .text = labels[i],

            .hovered = false,
            .pressed = false,

            .scale = 1.0f
        };
    }

    // Calculator State
    CalculatorState calculator =
    {
        .expression = ""
    };

    bool running = true;

    SDL_Event event;

    Uint64 previousTicks =
        SDL_GetTicks();

    // Main Loop
    while (running)
    {
        Uint64 currentTicks =
            SDL_GetTicks();

        float deltaTime =
            (currentTicks - previousTicks)
            / 1000.0f;

        previousTicks = currentTicks;

        float mouseX;
        float mouseY;

        SDL_GetMouseState(
            &mouseX,
            &mouseY
        );

        // Events
        while (SDL_PollEvent(&event))
        {
            if (
                event.type ==
                SDL_EVENT_QUIT
            )
            {
                running = false;
            }

            // Mouse Down
            if (
                event.type ==
                SDL_EVENT_MOUSE_BUTTON_DOWN
            )
            {
                for (int i = 0; i < 16; i++)
                {
                    if (
                        IsPointInsideButton(
                            &buttons[i],
                            mouseX,
                            mouseY
                        )
                    )
                    {
                        buttons[i].pressed = true;

                        const char* value =
                            buttons[i].text;

                        if (
                            strcmp(value, "=") == 0
                        )
                        {
                            EvaluateExpression(
                                &calculator
                            );
                        }
                        else
                        {
                            AppendToExpression(
                                &calculator,
                                value
                            );
                        }
                    }
                }
            }

            // Mouse Up
            if (
                event.type ==
                SDL_EVENT_MOUSE_BUTTON_UP
            )
            {
                for (int i = 0; i < 16; i++)
                {
                    buttons[i].pressed = false;
                }
            }
        }

        // Background
        SDL_SetRenderDrawColor(
            renderer,
            BACKGROUND_COLOR.r,
            BACKGROUND_COLOR.g,
            BACKGROUND_COLOR.b,
            BACKGROUND_COLOR.a
        );

        SDL_RenderClear(renderer);

        // Display Panel
        SDL_FRect display =
        {
            20,
            40,
            360,
            140
        };

        SDL_SetRenderDrawColor(
            renderer,
            28,
            28,
            28,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &display
        );

        // Expression
        DrawText(
            renderer,
            font,
            calculator.expression,
            40,
            100
        );

        // Draw Buttons
    for (int i = 0; i < 16; i++)
    {
        buttons[i].hovered =
            IsPointInsideButton(
                &buttons[i],
                mouseX,
                mouseY
            );

        UpdateButtonAnimation(
            &buttons[i],
            deltaTime
        );

        DrawButton(
            renderer,
            &buttons[i]
        );

        SDL_FRect textRect =
        {
            buttons[i].x,
            buttons[i].y,
            buttons[i].width,
            buttons[i].height
        };

        DrawCenteredText(
            renderer,
            font,
            buttons[i].text,
            textRect
        );
    }

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    TTF_Quit();

    SDL_Quit();
}