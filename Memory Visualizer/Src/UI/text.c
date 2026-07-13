#include "text.h"

static TTF_Font* gFont = NULL;

int InitializeText()
{
    if (!TTF_Init())
    {
        SDL_Log(
            "TTF Init Failed: %s",
            SDL_GetError());

        return 0;
    }

    gFont =
        TTF_OpenFont(
            "assets/fonts/JosefinSans-Regular.ttf",
            24);

    if (!gFont)
    {
        SDL_Log(
            "Failed To Load Font: %s",
            SDL_GetError());

        return 0;
    }

    return 1;
}

void DrawText(
    SDL_Renderer* renderer,
    const char* text,
    float x,
    float y)
{
    SDL_Color color =
    {
        255,
        255,
        255,
        255
    };

    SDL_Surface* surface =
        TTF_RenderText_Blended(
            gFont,
            text,
            0,
            color);

    if (!surface)
    {
        return;
    }

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(
            renderer,
            surface);

    SDL_FRect dst =
    {
        x,
        y,
        (float)surface->w,
        (float)surface->h
    };

    SDL_RenderTexture(
        renderer,
        texture,
        NULL,
        &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void ShutdownText()
{
    if (gFont)
    {
        TTF_CloseFont(gFont);
        gFont = NULL;
    }

    TTF_Quit();
}