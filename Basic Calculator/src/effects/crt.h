#ifndef CRT_H
#define CRT_H

#include <SDL3/SDL.h>

void DrawCRTEffect(
    SDL_Renderer* renderer,
    SDL_Texture* sceneTexture,
    float time
);

#endif