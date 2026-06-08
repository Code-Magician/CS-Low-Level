#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "pointer.h"
#include "array.h"
#include "linkedList.h"

Variable variables[MAX_VARIABLES];
HeapBlock heapBlocks[MAX_HEAP_BLOCKS];

int variableCount = 0;
int heapBlockCount = 0;

void InitializeMemory()
{
    variableCount = 0;
    heapBlockCount = 0;

    pointerCount = 0;
    arrayCount = 0;
    linkedListCount = 0;
}

void AddVariable(const char* name, int value)
{
    if (variableCount >= MAX_VARIABLES)
    {
        printf("Memory Full!\n");
        return;
    }

    strcpy_s(
        variables[variableCount].name,
        sizeof(variables[variableCount].name),
        name);

    variables[variableCount].value = value;
    variables[variableCount].address =
        &variables[variableCount].value;

    variableCount++;
}

void DisplayVariables()
{
    printf("\nSTACK MEMORY\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < variableCount; i++)
    {
        printf("%-15s %-10d %p\n",
            variables[i].name,
            variables[i].value,
            variables[i].address);
    }
}

void AllocateHeapBlock(const char* name, int value)
{
    if (heapBlockCount >= MAX_HEAP_BLOCKS)
    {
        printf("Heap Full!\n");
        return;
    }

    strcpy_s(
        heapBlocks[heapBlockCount].name,
        sizeof(heapBlocks[heapBlockCount].name),
        name);

    heapBlocks[heapBlockCount].ptr =
        (int*)malloc(sizeof(int));

    if (heapBlocks[heapBlockCount].ptr == NULL)
    {
        printf("Allocation Failed!\n");
        return;
    }

    *heapBlocks[heapBlockCount].ptr = value;
    heapBlocks[heapBlockCount].isFreed = 0;

    heapBlockCount++;
}

void DisplayHeapBlocks()
{
    printf("\nHEAP MEMORY\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < heapBlockCount; i++)
    {
        if (heapBlocks[i].isFreed)
        {
            printf("%-15s FREED\n",
                heapBlocks[i].name);
        }
        else
        {
            printf("%-15s %-10d %p\n",
                heapBlocks[i].name,
                *heapBlocks[i].ptr,
                heapBlocks[i].ptr);
        }
    }
}

void FreeHeapBlock(const char* name)
{
    for (int i = 0; i < heapBlockCount; i++)
    {
        if (strcmp(name, heapBlocks[i].name) == 0)
        {
            if (heapBlocks[i].isFreed)
            {
                printf("Already Freed\n");
                return;
            }

            free(heapBlocks[i].ptr);

            heapBlocks[i].ptr = NULL;
            heapBlocks[i].isFreed = 1;

            return;
        }
    }
}

void DisplayMemory()
{
    DisplayVariables();
    DisplayHeapBlocks();
    DisplayPointers();
}

void DrawMemoryMap()
{
    printf("\n=============== STACK ===============\n\n");

    for (int i = 0; i < variableCount; i++)
    {
        printf("+-----------------------------+\n");
        printf("| %-27s |\n", variables[i].name);
        printf("| Value: %-20d |\n", variables[i].value);
        printf("| Addr : %-20p |\n", variables[i].address);
        printf("+-----------------------------+\n\n");
    }

    printf("=============== HEAP ================\n\n");

    for (int i = 0; i < heapBlockCount; i++)
    {
        printf("+-----------------------------+\n");

        if (heapBlocks[i].isFreed)
        {
            printf("| %-27s |\n", heapBlocks[i].name);
            printf("| %-27s |\n", "FREED");
        }
        else
        {
            printf("| %-27s |\n", heapBlocks[i].name);
            printf("| Value: %-20d |\n", *heapBlocks[i].ptr);
            printf("| Addr : %-20p |\n", heapBlocks[i].ptr);
        }

        printf("+-----------------------------+\n\n");
    }
}

void CheckMemoryLeaks()
{
    int leaksFound = 0;

    printf("\nMEMORY LEAK REPORT\n");

    for (int i = 0; i < heapBlockCount; i++)
    {
        if (!heapBlocks[i].isFreed)
        {
            printf("LEAK: %s at %p\n",
                heapBlocks[i].name,
                heapBlocks[i].ptr);

            leaksFound = 1;
        }
    }

    if (!leaksFound)
    {
        printf("No leaks detected.\n");
    }
}