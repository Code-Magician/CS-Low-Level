#ifndef PARTICLES_H
#define PARTICLES_H

#include <SDL3/SDL.h>

#define MAX_PARTICLES 512

typedef struct
{
    float x;
    float y;

    float prevX;
    float prevY;

    float vx;
    float vy;

    float life;

    float thickness;

    int active;

} Particle;

void InitializeParticles();

void SpawnParticles(
    float x,
    float y
);

void UpdateParticles(
    float deltaTime
);

void DrawParticles(
    SDL_Renderer* renderer
);

#endif