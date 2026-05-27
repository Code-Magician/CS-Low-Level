#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef struct
{
    char expression[256];

    double firstNumber;

    char currentOperator;

} CalculatorState;

void AppendToExpression(
    CalculatorState* calculator,
    const char* value
);

void EvaluateExpression(
    CalculatorState* calculator
);

#endif