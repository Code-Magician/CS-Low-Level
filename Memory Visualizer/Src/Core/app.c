#include <SDL3/SDL.h>

#include "app.h"
#include "renderer.h"

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
            720,
            0);

    if (!window)
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

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = 0;
            }
        }

        RenderFrame(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}