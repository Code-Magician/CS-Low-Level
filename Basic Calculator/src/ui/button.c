#include "button.h"

static float Lerp(
    float a,
    float b,
    float t
)
{
    return a + (b - a) * t;
}

void DrawRoundedRect(
    SDL_Renderer* renderer,
    SDL_FRect rect,
    int radius
)
{
    // Center Rectangle
    SDL_FRect center =
    {
        rect.x + radius,
        rect.y,
        rect.w - radius * 2,
        rect.h
    };

    SDL_RenderFillRect(renderer, &center);

    // Left Rectangle
    SDL_FRect left =
    {
        rect.x,
        rect.y + radius,
        radius,
        rect.h - radius * 2
    };

    SDL_RenderFillRect(renderer, &left);

    // Right Rectangle
    SDL_FRect right =
    {
        rect.x + rect.w - radius,
        rect.y + radius,
        radius,
        rect.h - radius * 2
    };

    SDL_RenderFillRect(renderer, &right);

    // Draw Corner Circles
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;

            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderPoint(
                    renderer,
                    rect.x + radius + dx,
                    rect.y + radius + dy
                );

                SDL_RenderPoint(
                    renderer,
                    rect.x + rect.w - radius + dx,
                    rect.y + radius + dy
                );

                SDL_RenderPoint(
                    renderer,
                    rect.x + radius + dx,
                    rect.y + rect.h - radius + dy
                );

                SDL_RenderPoint(
                    renderer,
                    rect.x + rect.w - radius + dx,
                    rect.y + rect.h - radius + dy
                );
            }
        }
    }
}

void UpdateButtonAnimation(
    Button* button,
    float deltaTime
)
{
    float targetScale = 1.0f;

    if (button->hovered)
    {
        targetScale = 1.08f;
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

    // Shadow
    SDL_SetRenderDrawColor(
        renderer,
        0,
        0,
        0,
        80
    );

    SDL_FRect shadow =
    {
        rect.x + 4,
        rect.y + 4,
        rect.w,
        rect.h
    };

    DrawRoundedRect(
        renderer,
        shadow,
        16
    );

    // Button
    SDL_SetRenderDrawColor(
        renderer,
        currentColor.r,
        currentColor.g,
        currentColor.b,
        currentColor.a
    );

    DrawRoundedRect(
        renderer,
        rect,
        16
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