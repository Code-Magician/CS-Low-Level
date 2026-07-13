#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

int InitializeText();

void ShutdownText();

void DrawText(
    SDL_Renderer* renderer,
    const char* text,
    float x,
    float y);

#endif