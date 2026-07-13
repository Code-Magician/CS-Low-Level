#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>

typedef struct
{
    SDL_FRect rect;

    const char* text;

    int isHovered;
} Button;

void DrawButton(
    SDL_Renderer* renderer,
    Button* button);

int IsButtonClicked(
    Button* button,
    float mouseX,
    float mouseY);

#endif