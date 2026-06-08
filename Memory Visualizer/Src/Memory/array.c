#include <stdio.h>
#include <string.h>

#include "array.h"

ArrayInfo arrays[MAX_ARRAYS];
int arrayCount = 0;

void CreateArray(const char* name, int size)
{
    if (arrayCount >= MAX_ARRAYS)
        return;

    strcpy_s(
        arrays[arrayCount].name,
        sizeof(arrays[arrayCount].name),
        name);

    arrays[arrayCount].size = size;

    for (int i = 0; i < size; i++)
    {
        arrays[arrayCount].values[i] = 0;
    }

    arrayCount++;
}

void SetArrayElement(
    const char* name,
    int index,
    int value)
{
    for (int i = 0; i < arrayCount; i++)
    {
        if (strcmp(name, arrays[i].name) == 0)
        {
            arrays[i].values[index] = value;
            return;
        }
    }
}

void DisplayArrays()
{
    for (int i = 0; i < arrayCount; i++)
    {
        printf("\n%s\n\n",
            arrays[i].name);

        for (int j = 0; j < arrays[i].size; j++)
            printf("+-----");

        printf("+\n");

        for (int j = 0; j < arrays[i].size; j++)
            printf("| %-3d ",
                arrays[i].values[j]);

        printf("|\n");

        for (int j = 0; j < arrays[i].size; j++)
            printf("+-----");

        printf("+\n");
    }
}