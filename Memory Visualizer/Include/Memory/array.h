#ifndef ARRAY_H
#define ARRAY_H

#define MAX_ARRAYS 20
#define MAX_ARRAY_SIZE 20

typedef struct
{
    char name[32];
    int values[MAX_ARRAY_SIZE];
    int size;
} ArrayInfo;

extern ArrayInfo arrays[MAX_ARRAYS];
extern int arrayCount;

void CreateArray(
    const char* name,
    int size);

void SetArrayElement(
    const char* name,
    int index,
    int value);

void DisplayArrays();

#endif