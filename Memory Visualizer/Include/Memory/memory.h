#ifndef MEMORY_H
#define MEMORY_H

#define MAX_VARIABLES 100
#define MAX_HEAP_BLOCKS 100

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

extern Variable variables[MAX_VARIABLES];
extern HeapBlock heapBlocks[MAX_HEAP_BLOCKS];

extern int variableCount;
extern int heapBlockCount;

void InitializeMemory();

void AddVariable(const char* name, int value);
void DisplayVariables();

void AllocateHeapBlock(const char* name, int value);
void DisplayHeapBlocks();

void FreeHeapBlock(const char* name);

void DisplayMemory();
void DrawMemoryMap();

void CheckMemoryLeaks();

#endif