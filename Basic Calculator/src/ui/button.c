#include "button.h"

#include "../utils/colors.h"

static float Lerp(
    float a,
    float b,
    float t
)
{
    return a + (b - a) * t;
}

void UpdateButtonAnimation(
    Button* button,
    float deltaTime
)
{
    float targetScale = 1.0f;

    if (button->hovered)
    {
        targetScale = 1.05f;
    }

    if (button->pressed)
    {
        targetScale = 0.95f;
    }

    button->scale =
        Lerp(
            button->scale,
            targetScale,
            10.0f * deltaTime
        );
}

void DrawButton(
    SDL_Renderer* renderer,
    Button* button
)
{
    SDL_Color currentColor =
        button->hovered
        ? button->hoverColor
        : button->color;

    float scaledWidth =
        button->width * button->scale;

    float scaledHeight =
        button->height * button->scale;

    float offsetX =
        (button->width - scaledWidth) / 2;

    float offsetY =
        (button->height - scaledHeight) / 2;

    SDL_FRect rect =
    {
        button->x + offsetX,
        button->y + offsetY,
        scaledWidth,
        scaledHeight
    };

    // =========================
    // OUTER GLOW
    // =========================

    SDL_SetRenderDrawColor(
        renderer,
        currentColor.r,
        currentColor.g,
        currentColor.b,
        40
    );

    for (int i = 0; i < 6; i++)
    {
        SDL_FRect glow =
        {
            rect.x - i,
            rect.y - i,
            rect.w + i * 2,
            rect.h + i * 2
        };

        SDL_RenderRect(
            renderer,
            &glow
        );
    }

    // =========================
    // MAIN BUTTON BODY
    // =========================

    SDL_SetRenderDrawColor(
        renderer,
        currentColor.r,
        currentColor.g,
        currentColor.b,
        255
    );

    SDL_RenderFillRect(
        renderer,
        &rect
    );

    // =========================
    // INNER PANEL
    // =========================

    SDL_SetRenderDrawColor(
        renderer,
        10,
        10,
        18,
        255
    );

    SDL_FRect inner =
    {
        rect.x + 4,
        rect.y + 4,
        rect.w - 8,
        rect.h - 8
    };

    SDL_RenderFillRect(
        renderer,
        &inner
    );

    // =========================
    // TOP HIGHLIGHT
    // =========================

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        60
    );

    SDL_FRect highlight =
    {
        rect.x + 2,
        rect.y + 2,
        rect.w - 4,
        4
    };

    SDL_RenderFillRect(
        renderer,
        &highlight
    );

    // =========================
    // BORDER
    // =========================

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        80
    );

    SDL_RenderRect(
        renderer,
        &rect
    );
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