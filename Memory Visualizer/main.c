#include <stdio.h>
#include<stdlib.h>
#include "memory.h"

int main()
{
    int choice;

    InitializeMemory();

    while (1)
    {
        printf("\n=== MEMORY VISUALIZER ===\n");

        printf("1. Add Stack Variable\n");
        printf("2. Add Heap Memory\n");
        printf("3. Add Pointer To Variable\n");

        printf("4. Add Array\n");
        printf("5. Set Array Element\n");

        printf("6. Display Memory Table\n");
        printf("7. Display Memory Map\n");
        printf("8. Display Arrays\n");

        printf("9. Dereference Pointer\n");

        printf("10. Free Heap Memory\n");
        printf("11. Check Memory Leaks\n");

        printf("12. Create Linked List\n");
        printf("13. Add To Linked List\n");
        printf("14. Display LinkedList\n");

        printf("15. Exit\n");

        printf("Choice: ");

        scanf_s("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char name[32];
            int value;

            printf("Variable Name: ");
            scanf_s("%31s", name, (unsigned)_countof(name));

            printf("Value: ");
            scanf_s("%d", &value);

            AddVariable(name, value);
            break;
        }

        case 2:
        {
            char name[32];
            int value;

            printf("Block Name: ");
            scanf_s("%31s", name, (unsigned)_countof(name));

            printf("Value: ");
            scanf_s("%d", &value);

            AllocateHeapBlock(name, value);
            break;
        }

        case 3:
        {
            char pointerName[32];
            char variableName[32];

            printf("Pointer Name: ");
            scanf_s("%31s",
                pointerName,
                (unsigned)_countof(pointerName));

            printf("Variable To Point At: ");
            scanf_s("%31s",
                variableName,
                (unsigned)_countof(variableName));

            CreatePointerToVariable(
                pointerName,
                variableName);

            break;
        }

        case 4:
        {
            char arrayName[32];
            int size;

            printf("Array Name: ");
            scanf_s("%31s",
                arrayName,
                (unsigned)_countof(arrayName));

            printf("Array Size: ");
            scanf_s("%d", &size);

            CreateArray(arrayName, size);

            break;
        }

        case 5:
        {
            char arrayName[32];
            int index;
            int value;

            printf("Array Name: ");
            scanf_s("%31s",
                arrayName,
                (unsigned)_countof(arrayName));

            printf("Index: ");
            scanf_s("%d", &index);

            printf("Value: ");
            scanf_s("%d", &value);

            SetArrayElement(
                arrayName,
                index,
                value);

            break;
        }

        case 6:
            DisplayMemory();
            break;

        case 7:
            DrawMemoryMap();
            break;

        case 8:
            DisplayArrays();
            break;

        case 9:
        {
            char pointerName[32];

            printf("Pointer Name: ");

            scanf_s(
                "%31s",
                pointerName,
                (unsigned)_countof(pointerName));

            DereferencePointer(pointerName);

            break;
        }

        case 10:
        {
            char name[32];

            printf("Block Name: ");

            scanf_s("%31s",
                name,
                (unsigned)_countof(name));

            FreeHeapBlock(name);

            break;
        }

        case 11:
            CheckMemoryLeaks();
            break;

        case 12:
        {
            char linkedListName[32];

            printf("Linked List Name: ");

            scanf_s(
                "%31s",
                linkedListName,
                (unsigned)_countof(linkedListName));

            CreateLinkedList(linkedListName);
            break;
        }

        case 13:
        {
            char linkedListName[32];
            int value;

            printf("Linked List Name: ");
            scanf_s("%31s",
                linkedListName,
                (unsigned)_countof(linkedListName));

            printf("Value: ");
            scanf_s("%d", &value);

            AddNode(linkedListName, value);

            break;
        }

        case 14:
            DisplayLinkedLists();
            break;

        case 15:
            return 0;

        default:
            printf("Invalid Choice\n");
        }
    }
}