#ifndef MEMORY_H
#define MEMORY_H

#define MAX_VARIABLES 100
#define MAX_HEAP_BLOCKS 100
#define MAX_POINTERS 100
#define MAX_ARRAYS 20
#define MAX_ARRAY_SIZE 20
#define MAX_LINKED_LISTS 20

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    char name[32];
    int values[MAX_ARRAY_SIZE];
    int size;
} ArrayInfo;

typedef struct
{
    char name[32];
    Node* head;
} LinkedList;

typedef struct
{
    char name[32];
    int value;
    void* address;
} Variable;

typedef struct
{
    char name[32];
    int* ptr;
    int isFreed;
} HeapBlock;

typedef struct
{
    char name[32];
    char targetVariableName[32];
    void* targetAddress;
} PointerInfo;

void InitializeMemory();

void AddVariable(const char* name, int value);
void DisplayVariables();

void AllocateHeapBlock(const char* name, int value);
void DisplayHeapBlocks();
void FreeHeapBlock(const char* name);

void CreatePointerToVariable(const char* pointerName, const char* variableName);
void DisplayPointers();
void DereferencePointer(const char* pointerName);

void CreateArray(const char* name, int size);
void SetArrayElement(const char* name, int index, int value);
void DisplayArrays();

void CreateLinkedList(const char* name);
void AddNode(const char* listName, int value);
void DisplayLinkedLists();
void DeleteLinkedList(const char* listName);

void DisplayMemory();

void DrawMemoryMap();

void CheckMemoryLeaks();

#endif