#include <stdio.h>
#include "ui.h"

void DrawUI()
{
    printf("=========================================\n");
    printf("          MEMORY VISUALIZER\n");
    printf("=========================================\n\n");

    printf("STACK\n");
    printf("-----------------\n");
    printf("[ Empty ]\n\n");

    printf("HEAP\n");
    printf("-----------------\n");
    printf("[ Empty ]\n\n");

    printf("1. Add Variable\n");
    printf("2. Allocate Heap Memory\n");
    printf("3. Exit\n");
}