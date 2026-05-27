#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct
{
    float x;
    float y;

    float width;
    float height;

    SDL_Color color;
    SDL_Color hoverColor;

    const char* text;

    bool hovered;

} Button;

void DrawButton(SDL_Renderer* renderer, Button* button);

bool IsPointInsideButton(
    Button* button,
    float mouseX,
    float mouseY
);

#endif