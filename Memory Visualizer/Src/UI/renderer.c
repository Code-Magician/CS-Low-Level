#include <SDL3/SDL.h>
#include<stdio.h>

#include "panel.h"
#include "renderer.h"
#include "text.h"
#include "memory.h"
#include "pointer.h"
#include "array.h"

void RenderFrame(
    SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(
        renderer,
        20,
        20,
        20,
        255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(
        renderer,
        255,
        255,
        255,
        255);

    // Stack
    DrawPanel(
        renderer,
        40,
        40,
        500,
        400);

    DrawText(
        renderer,
        "STACK",
        60,
        55);

    char buffer[128];

    float startY = 90.0f;
    float startX = 60.0f;

    for (int i = 0; i < variableCount; i++)
    {
        DrawMemoryBlock(
            renderer,
            startX,
            startY,
            180,
            80,
            variables[i].name,
            variables[i].value);

        startY += 90.0f;

        if (startY > 300.0f)
        {
            startY = 90.0f;
            startX += 220.0f;
        }
    }

    // Heap
    DrawPanel(
        renderer,
        580,
        40,
        500,
        400);

    DrawText(
        renderer,
        "HEAP",
        600,
        55);

    startY = 100;

    for (int i = 0; i < heapBlockCount; i++)
    {
        if (heapBlocks[i].isFreed)
        {
            sprintf_s(
                buffer,
                sizeof(buffer),
                "%s : FREED",
                heapBlocks[i].name);
        }
        else
        {
            sprintf_s(
                buffer,
                sizeof(buffer),
                "%s : %d",
                heapBlocks[i].name,
                *heapBlocks[i].ptr);
        }

        DrawText(
            renderer,
            buffer,
            600,
            startY);

        startY += 30;
    }

    startY = 520;
    // Pointers
    DrawPanel(
        renderer,
        40,
        460,
        1040,
        150);

    DrawText(
        renderer,
        "POINTERS",
        60,
        475);

    for (int i = 0; i < pointerCount; i++)
    {
        sprintf_s(
            buffer,
            sizeof(buffer),
            "%s -> %s",
            pointers[i].name,
            pointers[i].targetVariableName);

        DrawText(
            renderer,
            buffer,
            60,
            startY);

        startY += 30;
    }

    // Arrays
    DrawPanel(
        renderer,
        40,
        650,
        1040,
        180);

    DrawText(
        renderer,
        "POINTERS",
        60,
        475);

    startY = 710.0f;

    for (int i = 0; i < arrayCount; i++)
    {
        DrawText(
            renderer,
            arrays[i].name,
            60,
            startY);

        float cellX = 200.0f;

        for (int j = 0; j < arrays[i].size; j++)
        {
            SDL_FRect cell =
            {
                cellX,
                startY - 5,
                60,
                40
            };

            SDL_RenderRect(
                renderer,
                &cell);

            char buffer[32];

            sprintf_s(
                buffer,
                sizeof(buffer),
                "%d",
                arrays[i].values[j]);

            DrawText(
                renderer,
                buffer,
                cellX + 15,
                startY + 5);

            sprintf_s(
                buffer,
                sizeof(buffer),
                "%d",
                j);

            DrawText(
                renderer,
                buffer,
                cellX + 20,
                startY + 45);

            cellX += 70;
        }

        startY += 70;
    }
}