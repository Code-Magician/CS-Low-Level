#include <stdio.h>

#include "panel.h"
#include "text.h"

void DrawPanel(
    SDL_Renderer* renderer,
    float x,
    float y,
    float width,
    float height)
{
    SDL_FRect rect =
    {
        x,
        y,
        width,
        height
    };

    SDL_RenderRect(
        renderer,
        &rect);
}

void DrawMemoryBlock(
    SDL_Renderer* renderer,
    float x,
    float y,
    float width,
    float height,
    const char* name,
    int value)
{
    SDL_FRect rect =
    {
        x,
        y,
        width,
        height
    };

    SDL_SetRenderDrawColor(
        renderer,
        30,
        80,
        120,
        255);

    SDL_RenderFillRect(
        renderer,
        &rect);

    SDL_SetRenderDrawColor(
        renderer,
        0,
        200,
        255,
        255);

    SDL_RenderRect(
        renderer,
        &rect);

    char buffer[64];

    DrawText(
        renderer,
        name,
        x + 10,
        y + 10);

    sprintf_s(
        buffer,
        sizeof(buffer),
        "Value: %d",
        value);

    DrawText(
        renderer,
        buffer,
        x + 10,
        y + 40);
}