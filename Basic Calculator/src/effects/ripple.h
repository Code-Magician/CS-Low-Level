#ifndef RIPPLE_H
#define RIPPLE_H

#include <SDL3/SDL.h>

#define MAX_RIPPLES 64

typedef struct
{
    float x;
    float y;

    float radius;

    float life;

    int active;

} Ripple;

void InitializeRipples();

void SpawnRipple(
    float x,
    float y
);

void UpdateRipples(
    float deltaTime
);

void DrawRipples(
    SDL_Renderer* renderer
);

#endif