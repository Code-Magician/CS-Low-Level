#include "text.h"

#include <string.h>

void DrawText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    int x,
    int y
)
{
    // Safety Checks
    if (!renderer || !font || !text)
    {
        return;
    }

    // Prevent Empty Text Crash
    if (strlen(text) == 0)
    {
        return;
    }

    SDL_Color color =
    {
        255,
        255,
        255,
        255
    };

    SDL_Surface* surface =
        TTF_RenderText_Solid(
            font,
            text,
            0,
            color
        );

    if (!surface)
    {
        SDL_Log(
            "Failed To Create Text Surface: %s",
            SDL_GetError()
        );

        return;
    }

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(
            renderer,
            surface
        );

    if (!texture)
    {
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect rect =
    {
        (float)x,
        (float)y,
        (float)surface->w,
        (float)surface->h
    };

    SDL_RenderTexture(
        renderer,
        texture,
        NULL,
        &rect
    );

    SDL_DestroyTexture(texture);

    SDL_DestroySurface(surface);
}