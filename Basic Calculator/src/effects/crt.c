#include "crt.h"

#include <math.h>

void DrawCRTEffect(
    SDL_Renderer* renderer,
    SDL_Texture* sceneTexture,
    float time
)
{
    // =========================
    // SCREEN WARP
    // =========================

    float wobble =
        sinf(time * 2.0f) * 2.0f;

    SDL_FRect screenRect =
    {
        -4 + wobble,
        -2,
        408,
        704
    };

    // =========================
    // RED CHANNEL
    // =========================

    SDL_SetTextureColorMod(
        sceneTexture,
        255,
        40,
        40
    );

    SDL_SetTextureAlphaMod(
        sceneTexture,
        90
    );

    SDL_FRect redOffset =
    {
        screenRect.x - 2,
        screenRect.y,
        screenRect.w,
        screenRect.h
    };

    SDL_RenderTexture(
        renderer,
        sceneTexture,
        NULL,
        &redOffset
    );

    // =========================
    // BLUE CHANNEL
    // =========================

    SDL_SetTextureColorMod(
        sceneTexture,
        40,
        120,
        255
    );

    SDL_FRect blueOffset =
    {
        screenRect.x + 2,
        screenRect.y,
        screenRect.w,
        screenRect.h
    };

    SDL_RenderTexture(
        renderer,
        sceneTexture,
        NULL,
        &blueOffset
    );

    // =========================
    // MAIN IMAGE
    // =========================

    SDL_SetTextureColorMod(
        sceneTexture,
        255,
        255,
        255
    );

    SDL_SetTextureAlphaMod(
        sceneTexture,
        255
    );

    SDL_RenderTexture(
        renderer,
        sceneTexture,
        NULL,
        &screenRect
    );

    // =========================
    // CRT DARK EDGES
    // =========================

    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        0,
        120
    );

    for (int i = 0; i < 25; i++)
    {
        SDL_RenderRect(
            renderer,
            &(SDL_FRect)
            {
                i,
                i,
                400 - i * 2,
                700 - i * 2
            }
        );
    }

    // =========================
    // VHS FLICKER
    // =========================

    int flicker =
        rand() % 12;

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        flicker
    );

    SDL_RenderFillRect(
        renderer,
        &(SDL_FRect)
        {
            0,
            0,
            400,
            700
        }
    );

    // =========================
    // GLITCH LINES
    // =========================

    for (int i = 0; i < 6; i++)
    {
        float y =
            rand() % 700;

        float offset =
            (rand() % 8) - 4;

        SDL_FRect src =
        {
            0,
            y,
            400,
            2
        };

        SDL_FRect dst =
        {
            offset,
            y,
            400,
            2
        };

        SDL_RenderTexture(
            renderer,
            sceneTexture,
            &src,
            &dst
        );
    }
}