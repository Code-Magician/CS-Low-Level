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

#include "../effects/effects.h"
#include "../effects/ripple.h"
#include "../effects/particles.h"
#include "../effects/crt.h"

#include "../settings/settings.h"

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
            "Cyberpunk Calculator",
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

    SDL_SetRenderDrawBlendMode(
        renderer,
        SDL_BLENDMODE_BLEND
    );

    // =========================
    // SCENE TEXTURE
    // =========================

    SDL_Texture* sceneTexture =
        SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            WINDOW_WIDTH,
            WINDOW_HEIGHT
        );

    // =========================
    // SYSTEMS
    // =========================

    InitializeRipples();

    InitializeParticles();

    InitializeSettings();

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
        "C", "<-", "/", "*",
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
                "+-*/=C<",
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
                180 +
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

    bool settingsOpen = false;

    // =========================
    // SETTINGS DRAGGING
    // =========================

    bool draggingGlow = false;
    bool draggingParticles = false;
    bool draggingChromatic = false;

    // =========================
    // SLIDERS
    // =========================

    SDL_FRect glowSlider =
    {
        220,
        175,
        120,
        8
    };

    SDL_FRect particleSlider =
    {
        220,
        245,
        120,
        8
    };

    SDL_FRect chromaticSlider =
    {
        220,
        385,
        120,
        8
    };

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
        // UPDATE SETTINGS
        // =========================

        if (draggingGlow)
        {
            settings.glowIntensity =
                (mouseX - glowSlider.x)
                / glowSlider.w;

            if (settings.glowIntensity < 0.2f)
                settings.glowIntensity = 0.2f;

            if (settings.glowIntensity > 2.0f)
                settings.glowIntensity = 2.0f;
        }

        if (draggingParticles)
        {
            settings.particleMultiplier =
                (mouseX - particleSlider.x)
                / particleSlider.w;

            if (settings.particleMultiplier < 0.2f)
                settings.particleMultiplier = 0.2f;

            if (settings.particleMultiplier > 2.0f)
                settings.particleMultiplier = 2.0f;
        }

        if (draggingChromatic)
        {
            settings.chromaticStrength =
                (mouseX - chromaticSlider.x)
                / chromaticSlider.w;

            if (settings.chromaticStrength < 0.0f)
                settings.chromaticStrength = 0.0f;

            if (settings.chromaticStrength > 3.0f)
                settings.chromaticStrength = 3.0f;
        }

        // =========================
        // RECTS
        // =========================

        SDL_FRect display =
        {
            20,
            55,
            360,
            100
        };

        SDL_FRect settingsButton =
        {
            WINDOW_WIDTH - 45,
            8,
            24,
            24
        };

        SDL_FRect crtToggle =
        {
            220,
            300,
            80,
            30
        };

        // =========================
        // EVENTS
        // =========================

        while (SDL_PollEvent(&event))
        {
            if (
                event.type ==
                SDL_EVENT_QUIT
            )
            {
                running = false;
            }

            // TEXT INPUT

            if (
                event.type ==
                SDL_EVENT_TEXT_INPUT
            )
            {
                if (!settingsOpen)
                {
                    AppendToExpression(
                        &calculator,
                        event.text.text
                    );
                }
            }

            // KEYBOARD

            if (
                event.type ==
                SDL_EVENT_KEY_DOWN
            )
            {
                SDL_Keycode key =
                    event.key.key;

                SDL_Scancode scan =
                    event.key.scancode;

                if (
                    key == SDLK_RETURN ||
                    scan == SDL_SCANCODE_KP_ENTER
                )
                {
                    EvaluateExpression(
                        &calculator
                    );
                }

                if (
                    key == SDLK_BACKSPACE
                )
                {
                    RemoveLastCharacter(
                        &calculator
                    );
                }

                if (
                    key == SDLK_ESCAPE
                )
                {
                    ClearExpression(
                        &calculator
                    );
                }
            }

            // MOUSE DOWN

            if (
                event.type ==
                SDL_EVENT_MOUSE_BUTTON_DOWN
            )
            {
                // SETTINGS BUTTON

                if (
                    mouseX >= settingsButton.x &&
                    mouseX <= settingsButton.x + settingsButton.w &&
                    mouseY >= settingsButton.y &&
                    mouseY <= settingsButton.y + settingsButton.h
                )
                {
                    settingsOpen =
                        !settingsOpen;
                }

                // SETTINGS

                if (settingsOpen)
                {
                    // GLOW

                    if (
                        mouseX >= glowSlider.x &&
                        mouseX <= glowSlider.x + glowSlider.w &&
                        mouseY >= glowSlider.y - 10 &&
                        mouseY <= glowSlider.y + 20
                    )
                    {
                        draggingGlow = true;
                    }

                    // PARTICLES

                    if (
                        mouseX >= particleSlider.x &&
                        mouseX <= particleSlider.x + particleSlider.w &&
                        mouseY >= particleSlider.y - 10 &&
                        mouseY <= particleSlider.y + 20
                    )
                    {
                        draggingParticles = true;
                    }

                    // CHROMATIC

                    if (
                        mouseX >= chromaticSlider.x &&
                        mouseX <= chromaticSlider.x + chromaticSlider.w &&
                        mouseY >= chromaticSlider.y - 10 &&
                        mouseY <= chromaticSlider.y + 20
                    )
                    {
                        draggingChromatic = true;
                    }

                    // CRT TOGGLE

                    if (
                        mouseX >= crtToggle.x &&
                        mouseX <= crtToggle.x + crtToggle.w &&
                        mouseY >= crtToggle.y &&
                        mouseY <= crtToggle.y + crtToggle.h
                    )
                    {
                        settings.crtEnabled =
                            !settings.crtEnabled;
                    }
                }

                // CALCULATOR BUTTONS

                if (!settingsOpen)
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

                            SpawnRipple(
                                mouseX,
                                mouseY
                            );

                            SpawnParticles(
                                mouseX,
                                mouseY
                            );

                            const char* value =
                                buttons[i].text;

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

                            else if (
                                strcmp(
                                    value,
                                    "<-"
                                ) == 0
                            )
                            {
                                RemoveLastCharacter(
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
            }

            // MOUSE UP

            if (
                event.type ==
                SDL_EVENT_MOUSE_BUTTON_UP
            )
            {
                draggingGlow = false;
                draggingParticles = false;
                draggingChromatic = false;

                for (int i = 0; i < 20; i++)
                {
                    buttons[i].pressed =
                        false;
                }
            }
        }

        // =========================
        // UPDATE EFFECTS
        // =========================

        UpdateRipples(
            deltaTime
        );

        UpdateParticles(
            deltaTime
        );

        // =========================
        // RENDER TO TEXTURE
        // =========================

        SDL_SetRenderTarget(
            renderer,
            sceneTexture
        );

        SDL_SetRenderDrawColor(
            renderer,
            0,
            0,
            0,
            255
        );

        SDL_RenderClear(renderer);

        // =========================
        // BACKGROUND
        // =========================

        DrawGradientBackground(
            renderer
        );

        // =========================
        // TOP BAR
        // =========================

        SDL_FRect topBar =
        {
            0,
            0,
            WINDOW_WIDTH,
            40
        };

        SDL_SetRenderDrawColor(
            renderer,
            8,
            8,
            18,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &topBar
        );

        SDL_SetRenderDrawColor(
            renderer,
            0,
            220,
            255,
            120
        );

        SDL_RenderLine(
            renderer,
            0,
            39,
            WINDOW_WIDTH,
            39
        );

        // =========================
        // SETTINGS BUTTON
        // =========================

        SDL_SetRenderDrawColor(
            renderer,
            30,
            30,
            50,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &settingsButton
        );

        SDL_SetRenderDrawColor(
            renderer,
            0,
            220,
            255,
            255
        );

        SDL_RenderRect(
            renderer,
            &settingsButton
        );

        // SIMPLE SETTINGS ICON

        float cx =
            settingsButton.x +
            settingsButton.w / 2;

        float cy =
            settingsButton.y +
            settingsButton.h / 2;

        SDL_RenderFillRect(
            renderer,
            &(SDL_FRect)
            {
                cx - 3,
                cy - 3,
                6,
                6
            }
        );

        SDL_RenderFillRect(
            renderer,
            &(SDL_FRect)
            {
                cx - 1,
                cy - 8,
                2,
                4
            }
        );

        SDL_RenderFillRect(
            renderer,
            &(SDL_FRect)
            {
                cx - 1,
                cy + 4,
                2,
                4
            }
        );

        SDL_RenderFillRect(
            renderer,
            &(SDL_FRect)
            {
                cx - 8,
                cy - 1,
                4,
                2
            }
        );

        SDL_RenderFillRect(
            renderer,
            &(SDL_FRect)
            {
                cx + 4,
                cy - 1,
                4,
                2
            }
        );

        // =========================
        // DISPLAY PANEL
        // =========================

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

        DrawGlowPulse(
            renderer,
            display,
            SDL_GetTicks() / 1000.0f
        );

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

        if (!settingsOpen)
        {
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
        }

        // =========================
        // FX
        // =========================

        DrawRipples(renderer);

        DrawParticles(renderer);

        DrawScanlines(
            renderer,
            WINDOW_WIDTH,
            WINDOW_HEIGHT
        );

        // =========================
        // BACK TO SCREEN
        // =========================

        SDL_SetRenderTarget(
            renderer,
            NULL
        );

        // =========================
        // CRT POST PROCESS
        // =========================

        DrawCRTEffect(
            renderer,
            sceneTexture,
            SDL_GetTicks() / 1000.0f
        );

        // =========================
        // SETTINGS PANEL
        // =========================

        if (settingsOpen)
        {
            SDL_SetRenderDrawColor(
                renderer,
                0,
                0,
                0,
                180
            );

            SDL_RenderFillRect(
                renderer,
                &(SDL_FRect)
                {
                    0,
                    40,
                    WINDOW_WIDTH,
                    WINDOW_HEIGHT
                }
            );

            SDL_FRect panel =
            {
                10,
                50,
                380,
                620
            };

            SDL_SetRenderDrawColor(
                renderer,
                10,
                10,
                20,
                245
            );

            SDL_RenderFillRect(
                renderer,
                &panel
            );

            SDL_SetRenderDrawColor(
                renderer,
                0,
                220,
                255,
                255
            );

            SDL_RenderRect(
                renderer,
                &panel
            );

            DrawText(
                renderer,
                font,
                "SETTINGS",
                40,
                90
            );

            DrawText(
                renderer,
                font,
                "Glow Intensity",
                40,
                160
            );

            DrawText(
                renderer,
                font,
                "Particles",
                40,
                230
            );

            DrawText(
                renderer,
                font,
                "CRT Effect",
                40,
                300
            );

            DrawText(
                renderer,
                font,
                "Chromatic FX",
                40,
                370
            );

            // SLIDERS

            SDL_SetRenderDrawColor(
                renderer,
                0,
                220,
                255,
                255
            );

            SDL_RenderFillRect(
                renderer,
                &glowSlider
            );

            SDL_RenderFillRect(
                renderer,
                &particleSlider
            );

            SDL_RenderFillRect(
                renderer,
                &chromaticSlider
            );

            // KNOBS

            SDL_SetRenderDrawColor(
                renderer,
                255,
                255,
                255,
                255
            );

            SDL_RenderFillRect(
                renderer,
                &(SDL_FRect)
                {
                    glowSlider.x +
                    settings.glowIntensity * 50,

                    glowSlider.y - 6,

                    10,
                    20
                }
            );

            SDL_RenderFillRect(
                renderer,
                &(SDL_FRect)
                {
                    particleSlider.x +
                    settings.particleMultiplier * 50,

                    particleSlider.y - 6,

                    10,
                    20
                }
            );

            SDL_RenderFillRect(
                renderer,
                &(SDL_FRect)
                {
                    chromaticSlider.x +
                    settings.chromaticStrength * 30,

                    chromaticSlider.y - 6,

                    10,
                    20
                }
            );

            // CRT TOGGLE

            if (settings.crtEnabled)
            {
                SDL_SetRenderDrawColor(
                    renderer,
                    0,
                    220,
                    120,
                    255
                );
            }
            else
            {
                SDL_SetRenderDrawColor(
                    renderer,
                    120,
                    40,
                    40,
                    255
                );
            }

            SDL_RenderFillRect(
                renderer,
                &crtToggle
            );

            SDL_SetRenderDrawColor(
                renderer,
                255,
                255,
                255,
                255
            );

            SDL_RenderRect(
                renderer,
                &crtToggle
            );

            DrawCenteredText(
                renderer,
                font,
                settings.crtEnabled
                    ? "ON"
                    : "OFF",

                crtToggle
            );
        }

        // =========================
        // PRESENT
        // =========================

        SDL_RenderPresent(renderer);
    }

    // =========================
    // CLEANUP
    // =========================

    TTF_CloseFont(font);

    SDL_DestroyTexture(
        sceneTexture
    );

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    TTF_Quit();

    SDL_Quit();
}