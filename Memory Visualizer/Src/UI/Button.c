#include "button.h"
#include "text.h"

void DrawButton(
    SDL_Renderer* renderer,
    Button* button)
{
    if (button->isHovered)
    {
        SDL_SetRenderDrawColor(
            renderer,
            80,
            120,
            255,
            255);
    }
    else
    {
        SDL_SetRenderDrawColor(
            renderer,
            50,
            50,
            50,
            255);
    }

    SDL_RenderFillRect(
        renderer,
        &button->rect);

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255);

    SDL_RenderRect(
        renderer,
        &button->rect);

    DrawText(
        renderer,
        button->text,
        button->rect.x + 10,
        button->rect.y + 10);
}

int IsButtonClicked(
    Button* button,
    float mouseX,
    float mouseY)
{
    return
        mouseX >= button->rect.x &&
        mouseX <= button->rect.x + button->rect.w &&
        mouseY >= button->rect.y &&
        mouseY <= button->rect.y + button->rect.h;
}