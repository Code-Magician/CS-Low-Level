#include "text.h"

#include <string.h>
#include <math.h>

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

    SDL_FRect dst =
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
        &dst
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

void DrawResponsiveDisplayText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    SDL_FRect rect,
    float time
)
{
    if (!text || strlen(text) == 0)
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

    float textWidth =
        (float)surface->w;

    float textHeight =
        (float)surface->h;

    // =========================
    // AUTO SCALE
    // =========================

    float scale = 1.0f;

    float maxWidth =
        rect.w - 40;

    if (textWidth > maxWidth)
    {
        scale =
            maxWidth / textWidth;
    }

    // Prevent too tiny text
    if (scale < 0.45f)
    {
        scale = 0.45f;
    }

    float scaledWidth =
        textWidth * scale;

    float scaledHeight =
        textHeight * scale;

    // =========================
    // HORIZONTAL SCROLL
    // =========================

    float overflow =
        scaledWidth - maxWidth;

    float scrollX = 0;

    if (overflow > 0)
    {
        scrollX = overflow;
    }

    // =========================
    // RIGHT ALIGN
    // =========================

    float x =
        rect.x +
        rect.w -
        scaledWidth -
        20 -
        scrollX;

    float y =
        rect.y +
        (rect.h - scaledHeight) / 2;

    // =========================
    // CLIPPING
    // =========================

    SDL_SetRenderClipRect(
        renderer,
        &(SDL_Rect)
        {
            (int)rect.x,
            (int)rect.y,
            (int)rect.w,
            (int)rect.h
        }
    );

    SDL_FRect dst =
    {
        x,
        y,
        scaledWidth,
        scaledHeight
    };

    SDL_RenderTexture(
        renderer,
        texture,
        NULL,
        &dst
    );

    // =========================
    // BLINKING CURSOR
    // =========================

    int showCursor =
        ((int)(time * 2) % 2) == 0;

    if (showCursor)
    {
        SDL_SetRenderDrawColor(
            renderer,
            255,
            255,
            255,
            255
        );

        SDL_FRect cursor =
        {
            x + scaledWidth + 5,
            y + 5,
            3,
            scaledHeight - 10
        };

        SDL_RenderFillRect(
            renderer,
            &cursor
        );
    }

    SDL_SetRenderClipRect(
        renderer,
        NULL
    );

    SDL_DestroyTexture(texture);

    SDL_DestroySurface(surface);
}