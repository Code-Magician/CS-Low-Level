#include "particles.h"

#include <stdlib.h>
#include <math.h>

static Particle particles[MAX_PARTICLES];

void InitializeParticles()
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].active = 0;
    }
}

void SpawnParticles(
    float x,
    float y
)
{
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < MAX_PARTICLES; j++)
        {
            if (!particles[j].active)
            {
                float angle =
                    ((float)rand() / RAND_MAX)
                    * 6.28318f;

                float speed =
                    300.0f +
                    ((float)rand() / RAND_MAX)
                    * 500.0f;

                particles[j].x = x;
                particles[j].y = y;

                particles[j].prevX = x;
                particles[j].prevY = y;

                particles[j].vx =
                    cosf(angle) * speed;

                particles[j].vy =
                    sinf(angle) * speed;

                particles[j].life = 1.0f;

                particles[j].thickness =
                    1 + rand() % 3;

                particles[j].active = 1;

                break;
            }
        }
    }
}

void UpdateParticles(
    float deltaTime
)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particles[i].active)
        {
            continue;
        }

        particles[i].prevX =
            particles[i].x;

        particles[i].prevY =
            particles[i].y;

        // MOVEMENT
        particles[i].x +=
            particles[i].vx * deltaTime;

        particles[i].y +=
            particles[i].vy * deltaTime;

        // LIGHT DRAG
        particles[i].vx *= 0.995f;
        particles[i].vy *= 0.995f;

        // FADE
        particles[i].life -=
            1.6f * deltaTime;

        if (particles[i].life <= 0)
        {
            particles[i].active = 0;
        }
    }
}

void DrawParticles(
    SDL_Renderer* renderer
)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particles[i].active)
        {
            continue;
        }

        Uint8 alpha =
            particles[i].life * 255;

        // =========================
        // OUTER GLOW
        // =========================

        SDL_SetRenderDrawColor(
            renderer,
            0,
            180,
            255,
            alpha / 5
        );

        for (int g = 0; g < 4; g++)
        {
            SDL_RenderLine(
                renderer,

                particles[i].prevX - g,
                particles[i].prevY - g,

                particles[i].x + g,
                particles[i].y + g
            );
        }

        // =========================
        // CORE STREAK
        // =========================

        SDL_SetRenderDrawColor(
            renderer,
            0,
            255,
            255,
            alpha
        );

        for (
            int t = 0;
            t < particles[i].thickness;
            t++
        )
        {
            SDL_RenderLine(
                renderer,

                particles[i].prevX,
                particles[i].prevY,

                particles[i].x,
                particles[i].y + t
            );
        }
    }
}