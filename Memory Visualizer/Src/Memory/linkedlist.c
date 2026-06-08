#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

LinkedList linkedLists[MAX_LINKED_LISTS];
int linkedListCount = 0;

void CreateLinkedList(const char* name)
{
    if (linkedListCount >= MAX_LINKED_LISTS)
        return;

    strcpy_s(
        linkedLists[linkedListCount].name,
        sizeof(linkedLists[linkedListCount].name),
        name);

    linkedLists[linkedListCount].head = NULL;

    linkedListCount++;
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

            return;
        }
    }
}

void DisplayLinkedLists()
{
    printf("\nLINKED LISTS\n");

    for (int i = 0; i < linkedListCount; i++)
    {
        printf("\n%s\n\n",
            linkedLists[i].name);

        Node* current =
            linkedLists[i].head;

        printf("HEAD -> ");

        while (current != NULL)
        {
            printf("[%d | %p]",
                current->value,
                current->next);

            if (current->next != NULL)
                printf(" ---> ");

            current = current->next;
        }

        printf(" ---> NULL\n");
    }
}

void DeleteLinkedList(const char* listName)
{
    for (int i = 0; i < linkedListCount; i++)
    {
        if (strcmp(
            linkedLists[i].name,
            listName) == 0)
        {
            Node* current =
                linkedLists[i].head;

            while (current != NULL)
            {
                Node* temp = current;
                current = current->next;
                free(temp);
            }

            linkedLists[i].head = NULL;
            return;
        }
    }
}