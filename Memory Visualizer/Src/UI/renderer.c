#include <SDL3/SDL.h>

#include "renderer.h"
#include "panel.h"

void RenderFrame(
    SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(
        renderer,
        20,
        20,
        20,
        255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255);

    // Stack
    DrawPanel(
        renderer,
        40,
        40,
        500,
        250);

    // Heap
    DrawPanel(
        renderer,
        580,
        40,
        500,
        250);

    // Pointers
    DrawPanel(
        renderer,
        40,
        330,
        1040,
        150);

    // Arrays
    DrawPanel(
        renderer,
        40,
        520,
        1040,
        150);
}