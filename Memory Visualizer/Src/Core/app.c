#include <SDL3/SDL.h>

#include "app.h"
#include "renderer.h"
#include "text.h"
#include "memory.h"
#include "array.h"
#include "pointer.h"
#include "linkedList.h"
#include "Button.h"

void RunApplication()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return;
    }

    SDL_Window* window =
        SDL_CreateWindow(
            "Memory Visualizer",
            1280,
            1080,
            0);

    if (!window)
    {
        SDL_Quit();
        return;
    }

    if (!InitializeText())
    {
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, NULL);

    int running = 1;

    while (running)
    {
        SDL_Event event;

        Button addVariableButton =
        {
            {1100, 40, 150, 40},
            "Add Variable",
            0
        };

        Button addHeapButton =
        {
            {1100, 90, 150, 40},
            "Add Heap",
            0
        };

        Button addPointerButton =
        {
            {1100, 140, 150, 40},
            "Add Pointer",
            0
        };

        Button addArrayButton =
        {
            {1100, 190, 150, 40},
            "Add Array",
            0
        };

        while (SDL_PollEvent(&event))
        {
            float mouseX;
            float mouseY;

            SDL_GetMouseState(
                &mouseX,
                &mouseY);

            addVariableButton.isHovered =
                IsButtonClicked(
                    &addVariableButton,
                    mouseX,
                    mouseY);

            addHeapButton.isHovered =
                IsButtonClicked(
                    &addHeapButton,
                    mouseX,
                    mouseY);

            addPointerButton.isHovered =
                IsButtonClicked(
                    &addPointerButton,
                    mouseX,
                    mouseY);

            addArrayButton.isHovered =
                IsButtonClicked(
                    &addArrayButton,
                    mouseX,
                    mouseY);

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (IsButtonClicked(
                    &addVariableButton,
                    mouseX,
                    mouseY))
                {
                    AddVariable(
                        "Health",
                        rand() % 100);
                }

                if (IsButtonClicked(
                    &addHeapButton,
                    mouseX,
                    mouseY))
                {
                    AllocateHeapBlock(
                        "Enemy",
                        rand() % 100);
                }

                if (IsButtonClicked(
                    &addArrayButton,
                    mouseX,
                    mouseY))
                {
                    CreateArray(
                        "Inventory",
                        5);
                }
            }

            if (event.type == SDL_EVENT_QUIT)
            {
                running = 0;
            }
        }

        RenderFrame(renderer);

        DrawButton(
            renderer,
            &addVariableButton);

        DrawButton(
            renderer,
            &addHeapButton);

        DrawButton(
            renderer,
            &addPointerButton);

        DrawButton(
            renderer,
            &addArrayButton);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    ShutdownText();

    SDL_Quit();
}