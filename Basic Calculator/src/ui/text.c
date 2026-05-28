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
    if (!renderer || !font || !text)
    {
        return;
    }

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

void DrawCenteredText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    SDL_FRect rect
)
{
    if (!text || strlen(text) == 0)
    {
        return;
    }

    int textWidth;
    int textHeight;

    TTF_GetStringSize(
        font,
        text,
        0,
        &textWidth,
        &textHeight
    );

    int x =
        rect.x + (rect.w - textWidth) / 2;

    int y =
        rect.y + (rect.h - textHeight) / 2;

    DrawText(
        renderer,
        font,
        text,
        x,
        y
    );
}