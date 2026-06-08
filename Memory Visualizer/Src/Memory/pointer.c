#include <stdio.h>
#include <string.h>

#include "pointer.h"
#include "memory.h"

PointerInfo pointers[MAX_POINTERS];
int pointerCount = 0;

void CreatePointerToVariable(
    const char* pointerName,
    const char* variableName)
{
    for (int i = 0; i < variableCount; i++)
    {
        if (strcmp(variableName,
            variables[i].name) == 0)
        {
            strcpy_s(
                pointers[pointerCount].name,
                sizeof(pointers[pointerCount].name),
                pointerName);

            strcpy_s(
                pointers[pointerCount].targetVariableName,
                sizeof(pointers[pointerCount].targetVariableName),
                variableName);

            pointers[pointerCount].targetAddress =
                &variables[i].value;

            pointerCount++;

            return;
        }
    }
}

void DisplayPointers()
{
    printf("\nPOINTERS\n");
    printf("--------------------------------------------\n");

    for (int i = 0; i < pointerCount; i++)
    {
        printf("%s -> %s (%p)\n",
            pointers[i].name,
            pointers[i].targetVariableName,
            pointers[i].targetAddress);
    }
}

void DereferencePointer(const char* pointerName)
{
    for (int i = 0; i < pointerCount; i++)
    {
        if (strcmp(pointerName,
            pointers[i].name) == 0)
        {
            printf("%s -> %s\n",
                pointers[i].name,
                pointers[i].targetVariableName);

            printf("Value Through Pointer = %d\n",
                *(int*)pointers[i].targetAddress);

            return;
        }
    }
}