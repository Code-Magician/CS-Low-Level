#include "effects.h"

#include <math.h>

void DrawGradientBackground(
    SDL_Renderer* renderer
)
{
    for (int y = 0; y < 700; y++)
    {
        float t =
            (float)y / 700.0f;

        Uint8 r =
            8 + t * 10;

        Uint8 g =
            8 + t * 20;

        Uint8 b =
            18 + t * 40;

        SDL_SetRenderDrawColor(
            renderer,
            r,
            g,
            b,
            255
        );

        SDL_RenderLine(
            renderer,
            0,
            y,
            400,
            y
        );
    }
}

void DrawScanlines(
    SDL_Renderer* renderer,
    int screenWidth,
    int screenHeight
)
{
    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        0,
        30
    );

    for (int y = 0; y < screenHeight; y += 4)
    {
        SDL_RenderLine(
            renderer,
            0,
            y,
            screenWidth,
            y
        );
    }
}

void DrawGlowPulse(
    SDL_Renderer* renderer,
    SDL_FRect rect,
    float time
)
{
    float pulse =
        (sinf(time * 3.0f) + 1.0f) * 0.5f;

    int glowSize =
        6 + pulse * 6;

    Uint8 alpha =
        40 + pulse * 40;

    SDL_SetRenderDrawColor(
        renderer,
        0,
        220,
        255,
        alpha
    );

    for (int i = 0; i < glowSize; i++)
    {
        SDL_FRect glow =
        {
            rect.x - i,
            rect.y - i,
            rect.w + i * 2,
            rect.h + i * 2
        };

        SDL_RenderRect(
            renderer,
            &glow
        );
    }
}