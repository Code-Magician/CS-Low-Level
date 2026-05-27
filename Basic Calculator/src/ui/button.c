#include "button.h"

void DrawButton(SDL_Renderer* renderer, Button* button)
{
    SDL_FRect rect =
    {
        button->x,
        button->y,
        button->width,
        button->height
    };

    SDL_Color currentColor =
        button->hovered
        ? button->hoverColor
        : button->color;

    SDL_SetRenderDrawColor(
        renderer,
        currentColor.r,
        currentColor.g,
        currentColor.b,
        currentColor.a
    );

    SDL_RenderFillRect(renderer, &rect);
}

bool IsPointInsideButton(
    Button* button,
    float mouseX,
    float mouseY
)
{
    return
        mouseX >= button->x &&
        mouseX <= button->x + button->width &&
        mouseY >= button->y &&
        mouseY <= button->y + button->height;
}