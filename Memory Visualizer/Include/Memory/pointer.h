#ifndef POINTER_H
#define POINTER_H

#define MAX_POINTERS 100

typedef struct
{
    char name[32];
    char targetVariableName[32];
    void* targetAddress;
} PointerInfo;

extern PointerInfo pointers[MAX_POINTERS];
extern int pointerCount;

void CreatePointerToVariable(
    const char* pointerName,
    const char* variableName);

void DisplayPointers();

void DereferencePointer(
    const char* pointerName);

#endif