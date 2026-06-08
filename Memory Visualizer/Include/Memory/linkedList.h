#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define MAX_LINKED_LISTS 20

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    char name[32];
    Node* head;
} LinkedList;

extern LinkedList linkedLists[MAX_LINKED_LISTS];
extern int linkedListCount;

void CreateLinkedList(
    const char* name);

void AddNode(
    const char* listName,
    int value);

void DisplayLinkedLists();

void DeleteLinkedList(
    const char* listName);

#endif