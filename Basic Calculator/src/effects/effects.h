#ifndef EFFECTS_H
#define EFFECTS_H

#include <SDL3/SDL.h>

void DrawGradientBackground(
    SDL_Renderer* renderer
);

void DrawScanlines(
    SDL_Renderer* renderer,
    int screenWidth,
    int screenHeight
);

void DrawGlowPulse(
    SDL_Renderer* renderer,
    SDL_FRect rect,
    float time
);

#endif