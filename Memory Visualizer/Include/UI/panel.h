#ifndef PANEL_H
#define PANEL_H

#include <SDL3/SDL.h>

void DrawPanel(
    SDL_Renderer* renderer,
    float x,
    float y,
    float width,
    float height);

void DrawMemoryBlock(
    SDL_Renderer* renderer,
    float x,
    float y,
    float width,
    float height,
    const char* name,
    int value);

#endif