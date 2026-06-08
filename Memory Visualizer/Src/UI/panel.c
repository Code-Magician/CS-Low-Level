#include "panel.h"

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