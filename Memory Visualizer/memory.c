#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "memory.h"

Variable variables[MAX_VARIABLES];
HeapBlock heapBlocks[MAX_HEAP_BLOCKS];
PointerInfo pointers[MAX_POINTERS];
ArrayInfo arrays[MAX_ARRAYS];
LinkedList linkedLists[MAX_LINKED_LISTS];

int variableCount = 0;
int heapBlockCount = 0;
int pointerCount = 0;
int arrayCount = 0;
int linkedListCount = 0;

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
    printf("%-15s %-10s %-15s\n",
        "Name",
        "Value",
        "Address");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < variableCount; i++)
    {
        printf("%-15s %-10d %p\n",
            variables[i].name,
            variables[i].value,
            variables[i].address);
    }

    printf("--------------------------------------------------\n");
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
    printf("%-15s %-10s %-15s\n",
        "Name",
        "Value",
        "Address");
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

    printf("--------------------------------------------------\n");
}

void FreeHeapBlock(const char* name)
{
    for (int i = 0; i < heapBlockCount; i++)
    {
        if (strcmp(name, heapBlocks[i].name) == 0)
        {
            if (heapBlocks[i].isFreed)
            {
                printf("Block already freed!\n");
                return;
            }

            free(heapBlocks[i].ptr);

            heapBlocks[i].ptr = NULL;
            heapBlocks[i].isFreed = 1;

            printf("Memory freed successfully.\n");
            return;
        }
    }

    printf("Block not found!\n");
}

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

            printf("Pointer created successfully.\n");

            return;
        }
    }

    printf("Variable not found.\n");
}

void DisplayPointers()
{
    printf("\n%-15s %-15s %-15s\n", 
        "POINTER NAME", 
        "VARIABLE NAME",
        "ADDRESS");
    printf("--------------------------------------------\n");

    for (int i = 0; i < pointerCount; i++)
    {
        printf("%-15s %-15s %p\n",
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
            int value =
                *(int*)pointers[i].targetAddress;

            printf("\n");
            printf("%s -> %s\n",
                pointers[i].name,
                pointers[i].targetVariableName);

            printf("\n");

            printf("Value Through Pointer = %d\n",
                value);

            return;
        }
    }

    printf("Pointer not found.\n");
}

void CreateArray(const char* name, int size)
{
    if (arrayCount >= MAX_ARRAYS)
    {
        printf("Maximum arrays reached.\n");
        return;
    }

    if (size <= 0 || size > MAX_ARRAY_SIZE)
    {
        printf("Invalid size.\n");
        return;
    }

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

    printf("Array created.\n");
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
            if (index < 0 ||
                index >= arrays[i].size)
            {
                printf("Invalid index.\n");
                return;
            }

            arrays[i].values[index] = value;

            return;
        }
    }

    printf("Array not found.\n");
}

void DisplayArrays()
{
    printf("\nARRAYS\n");
    printf("---------------------------------\n");

    for (int i = 0; i < arrayCount; i++)
    {
        printf("\n%s\n\n",
            arrays[i].name);

        for (int j = 0; j < arrays[i].size; j++)
        {
            printf("+-----");
        }

        printf("+\n");

        for (int j = 0; j < arrays[i].size; j++)
        {
            printf("| %-3d ",
                arrays[i].values[j]);
        }

        printf("|\n");

        for (int j = 0; j < arrays[i].size; j++)
        {
            printf("+-----");
        }

        printf("+\n");

        for (int j = 0; j < arrays[i].size; j++)
        {
            printf("%p ",
                &arrays[i].values[j]);
        }

        printf("\n");
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
    printf("\n");
    printf("=============== STACK ===============\n\n");

    for (int i = 0; i < variableCount; i++)
    {
        printf("+-----------------------------+\n");
        printf("| %-27s |\n",
            variables[i].name);

        printf("| Value: %-20d |\n",
            variables[i].value);

        printf("| Addr : %-20p |\n",
            variables[i].address);

        printf("+-----------------------------+\n\n");
    }

    printf("=============== HEAP ================\n\n");

    for (int i = 0; i < heapBlockCount; i++)
    {
        printf("+-----------------------------+\n");
        
        if (heapBlocks[i].isFreed)
        {
            printf("| %-27s |\n",
                heapBlocks[i].name);
            printf("| %-27s |\n",
                "FREED");
        }
        else
        {
            printf("| %-27s |\n",
                heapBlocks[i].name);

            printf("| Value: %-20d |\n",
                *heapBlocks[i].ptr);

            printf("| Addr : %-20p |\n",
                heapBlocks[i].ptr);
        }

        printf("+-----------------------------+\n\n");
    }
}

void CheckMemoryLeaks()
{
    int leaksFound = 0;

    printf("\nMEMORY LEAK REPORT\n");
    printf("---------------------------------\n");

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

    printf("---------------------------------\n");
}

void CreateLinkedList(
    const char* name)
{
    if (linkedListCount >= MAX_LINKED_LISTS)
    {
        printf("Maximum linked lists reached.\n");
        return;
    }

    strcpy_s(
        linkedLists[linkedListCount].name,
        sizeof(linkedLists[linkedListCount].name),
        name);

    linkedLists[linkedListCount].head = NULL;

    linkedListCount++;

    printf("Linked list created.\n");
}

void AddNode(
    const char* listName,
    int value)
{
    for (int i = 0; i < linkedListCount; i++)
    {
        if (strcmp(
            linkedLists[i].name,
            listName) == 0)
        {
            Node* newNode =
                (Node*)malloc(sizeof(Node));

            if (newNode == NULL)
            {
                printf("Allocation failed.\n");
                return;
            }

            newNode->value = value;
            newNode->next = NULL;

            if (linkedLists[i].head == NULL)
            {
                linkedLists[i].head = newNode;
            }
            else
            {
                Node* current =
                    linkedLists[i].head;

                while (current->next != NULL)
                {
                    current = current->next;
                }

                current->next = newNode;
            }

            printf("Node added.\n");

            return;
        }
    }

    printf("List not found.\n");
}

void DisplayLinkedLists()
{
    printf("\nLINKED LISTS\n");
    printf("--------------------------------------\n");

    for (int i = 0; i < linkedListCount; i++)
    {
        printf("\n%s\n\n",
            linkedLists[i].name);

        Node* current =
            linkedLists[i].head;

        if (current == NULL)
        {
            printf("EMPTY\n");
            continue;
        }

        printf("HEAD -> ");

        while (current != NULL)
        {
            printf("[%d | %p]",
                current->value,
                current->next);

            if (current->next != NULL)
            {
                printf(" ---> ");
            }

            current = current->next;
        }

        printf(" ---> NULL\n");
    }
}

