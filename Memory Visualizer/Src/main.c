#include "app.h"
#include "memory.h"
#include "pointer.h"

void TestData();

int main()
{
    TestData();

    RunApplication();

    return 0;
}

void TestData()
{
    InitializeMemory();

    AddVariable("Health", 100);
    AddVariable("Score", 500);
    AddVariable("Ammo", 30);

    AllocateHeapBlock(
        "EnemyHealth",
        50);

    AllocateHeapBlock(
        "BossHealth",
        1000);

    CreatePointerToVariable(
        "healthPtr",
        "Health");

    CreateArray(
        "Inventory",
        5);

    SetArrayElement(
        "Inventory",
        0,
        10);

    SetArrayElement(
        "Inventory",
        1,
        20);

    SetArrayElement(
        "Inventory",
        2,
        30);

    SetArrayElement(
        "Inventory",
        3,
        40);

    SetArrayElement(
        "Inventory",
        4,
        50);
}