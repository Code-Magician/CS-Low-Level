#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void DrawText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    int x,
    int y
);

void DrawCenteredText(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    SDL_FRect rect
);

#endif