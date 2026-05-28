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
    // =========================
    // SDL INIT
    // =========================

    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log(
            "SDL Init Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // =========================
    // TTF INIT
    // =========================

    if (TTF_Init() == false)
    {
        SDL_Log(
            "TTF Init Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // =========================
    // WINDOW
    // =========================

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

    SDL_StartTextInput(window);

    // =========================
    // RENDERER
    // =========================

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

    // =========================
    // FONT
    // =========================

    TTF_Font* font =
        TTF_OpenFont(
            "assets/font.ttf",
            28
        );

    if (!font)
    {
        SDL_Log(
            "Font Load Failed: %s",
            SDL_GetError()
        );

        return;
    }

    // =========================
    // BUTTON LABELS
    // =========================

    const char* labels[20] =
    {
        "C", "⌫", "/", "*",
        "7", "8", "9", "-",
        "4", "5", "6", "+",
        "1", "2", "3", "=",
        "0", ".", "(", ")"
    };

    // =========================
    // BUTTONS
    // =========================

    Button buttons[20];

    for (int i = 0; i < 20; i++)
    {
        int row = i / 4;
        int col = i % 4;

        SDL_Color normal =
            BUTTON_COLOR;

        SDL_Color hover =
            BUTTON_HOVER;

        if (
            strchr(
                "+-*/=C⌫",
                labels[i][0]
            )
        )
        {
            normal =
                OPERATOR_COLOR;

            hover =
                OPERATOR_HOVER;
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

    // =========================
    // CALCULATOR
    // =========================

    CalculatorState calculator =
    {
        .expression = ""
    };

    bool running = true;

    SDL_Event event;

    Uint64 previousTicks =
        SDL_GetTicks();

    // =========================
    // MAIN LOOP
    // =========================

    while (running)
    {
        Uint64 currentTicks =
            SDL_GetTicks();

        float deltaTime =
            (currentTicks - previousTicks)
            / 1000.0f;

        previousTicks =
            currentTicks;

        float mouseX;
        float mouseY;

        SDL_GetMouseState(
            &mouseX,
            &mouseY
        );

        // =========================
        // EVENTS
        // =========================

        while (SDL_PollEvent(&event))
        {
            // CLOSE
            if (
                event.type ==
                SDL_EVENT_QUIT
            )
            {
                running = false;
            }

            // =========================
            // TEXT INPUT
            // =========================

            if (
                event.type ==
                SDL_EVENT_TEXT_INPUT
            )
            {
                AppendToExpression(
                    &calculator,
                    event.text.text
                );
            }

            // =========================
            // KEYBOARD
            // =========================

            if (
                event.type ==
                SDL_EVENT_KEY_DOWN
            )
            {
                SDL_Keycode key =
                    event.key.key;

                SDL_Scancode scan =
                    event.key.scancode;

                // ENTER
                if (
                    key == SDLK_RETURN ||
                    scan == SDL_SCANCODE_KP_ENTER
                )
                {
                    EvaluateExpression(
                        &calculator
                    );
                }

                // BACKSPACE
                if (
                    key == SDLK_BACKSPACE
                )
                {
                    RemoveLastCharacter(
                        &calculator
                    );
                }

                // CLEAR
                if (
                    key == SDLK_ESCAPE
                )
                {
                    ClearExpression(
                        &calculator
                    );
                }
            }

            // =========================
            // MOUSE DOWN
            // =========================

            if (
                event.type ==
                SDL_EVENT_MOUSE_BUTTON_DOWN
            )
            {
                for (int i = 0; i < 20; i++)
                {
                    if (
                        IsPointInsideButton(
                            &buttons[i],
                            mouseX,
                            mouseY
                        )
                    )
                    {
                        buttons[i].pressed =
                            true;

                        const char* value =
                            buttons[i].text;

                        // EQUALS
                        if (
                            strcmp(
                                value,
                                "="
                            ) == 0
                        )
                        {
                            EvaluateExpression(
                                &calculator
                            );
                        }

                        // CLEAR
                        else if (
                            strcmp(
                                value,
                                "C"
                            ) == 0
                        )
                        {
                            ClearExpression(
                                &calculator
                            );
                        }

                        // BACKSPACE
                        else if (
                            strcmp(
                                value,
                                "⌫"
                            ) == 0
                        )
                        {
                            RemoveLastCharacter(
                                &calculator
                            );
                        }

                        // NORMAL INPUT
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

            // =========================
            // MOUSE UP
            // =========================

            if (
                event.type ==
                SDL_EVENT_MOUSE_BUTTON_UP
            )
            {
                for (int i = 0; i < 20; i++)
                {
                    buttons[i].pressed =
                        false;
                }
            }
        }

        // =========================
        // BACKGROUND
        // =========================

        SDL_SetRenderDrawColor(
            renderer,
            BACKGROUND_COLOR.r,
            BACKGROUND_COLOR.g,
            BACKGROUND_COLOR.b,
            BACKGROUND_COLOR.a
        );

        SDL_RenderClear(renderer);

        // =========================
        // DISPLAY PANEL
        // =========================

        SDL_FRect display =
        {
            20,
            40,
            360,
            140
        };

        SDL_SetRenderDrawColor(
            renderer,
            PANEL_COLOR.r,
            PANEL_COLOR.g,
            PANEL_COLOR.b,
            PANEL_COLOR.a
        );

        SDL_RenderFillRect(
            renderer,
            &display
        );

        // =========================
        // NEON BORDER
        // =========================

        SDL_SetRenderDrawColor(
            renderer,
            0,
            220,
            255,
            255
        );

        SDL_RenderRect(
            renderer,
            &display
        );

        // =========================
        // GLOW BORDER
        // =========================

        for (int i = 0; i < 4; i++)
        {
            SDL_FRect glow =
            {
                display.x - i,
                display.y - i,
                display.w + i * 2,
                display.h + i * 2
            };

            SDL_RenderRect(
                renderer,
                &glow
            );
        }

        // =========================
        // DISPLAY TEXT
        // =========================

        DrawResponsiveDisplayText(
            renderer,
            font,
            calculator.expression,
            display,
            SDL_GetTicks() / 1000.0f
        );

        // =========================
        // BUTTONS
        // =========================

        for (int i = 0; i < 20; i++)
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

        // =========================
        // PRESENT FRAME
        // =========================

        SDL_RenderPresent(renderer);
    }

    // =========================
    // CLEANUP
    // =========================

    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    TTF_Quit();

    SDL_Quit();
}