#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef struct
{
    char expression[256];

} CalculatorState;

void AppendToExpression(
    CalculatorState* calculator,
    const char* value
);

void RemoveLastCharacter(
    CalculatorState* calculator
);

void ClearExpression(
    CalculatorState* calculator
);

void EvaluateExpression(
    CalculatorState* calculator
);

#endif