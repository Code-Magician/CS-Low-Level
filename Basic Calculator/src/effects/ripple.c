#include "ripple.h"

#include <math.h>

static Ripple ripples[MAX_RIPPLES];

void InitializeRipples()
{
    for (int i = 0; i < MAX_RIPPLES; i++)
    {
        ripples[i].active = 0;
    }
}

void SpawnRipple(
    float x,
    float y
)
{
    for (int i = 0; i < MAX_RIPPLES; i++)
    {
        if (!ripples[i].active)
        {
            ripples[i].x = x;
            ripples[i].y = y;

            ripples[i].radius = 10;

            ripples[i].life = 1.0f;

            ripples[i].active = 1;

            break;
        }
    }
}

void UpdateRipples(
    float deltaTime
)
{
    for (int i = 0; i < MAX_RIPPLES; i++)
    {
        if (!ripples[i].active)
        {
            continue;
        }

        ripples[i].radius +=
            120.0f * deltaTime;     

        ripples[i].life -=
            1.4f * deltaTime;

        if (ripples[i].life <= 0)
        {
            ripples[i].active = 0;
        }
    }
}

static void DrawCircle(
    SDL_Renderer* renderer,
    int centerX,
    int centerY,
    int radius
)
{
    for (int angle = 0; angle < 360; angle += 1)
    {
        float rad =
            angle * 3.14159f / 180.0f;

        int x =
            centerX + cosf(rad) * radius;

        int y =
            centerY + sinf(rad) * radius;

        SDL_RenderPoint(
            renderer,
            x,
            y
        );
    }
}

void DrawRipples(
    SDL_Renderer* renderer
)
{
    for (int i = 0; i < MAX_RIPPLES; i++)
    {
        if (!ripples[i].active)
        {
            continue;
        }

        Uint8 alpha =
            ripples[i].life * 180;

        // MULTIPLE RINGS
        for (int t = 0; t < 4; t++)
        {
            SDL_SetRenderDrawColor(
                renderer,
                0,
                220,
                255,
                alpha / (t + 1)
            );

            DrawCircle(
                renderer,
                ripples[i].x,
                ripples[i].y,
                ripples[i].radius + t
            );
        }
    }
}