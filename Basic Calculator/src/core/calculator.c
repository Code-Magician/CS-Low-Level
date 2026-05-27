#include "calculator.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void AppendToExpression(
    CalculatorState* calculator,
    const char* value
)
{
    strcat(calculator->expression, value);
}

void EvaluateExpression(
    CalculatorState* calculator
)
{
    char* operatorPos =
        strpbrk(
            calculator->expression,
            "+-*/"
        );

    if (!operatorPos)
        return;

    char operatorChar = *operatorPos;

    double first =
        atof(calculator->expression);

    double second =
        atof(operatorPos + 1);

    double result = 0;

    switch (operatorChar)
    {
        case '+':
            result = first + second;
            break;

        case '-':
            result = first - second;
            break;

        case '*':
            result = first * second;
            break;

        case '/':
            result = first / second;
            break;
    }

    sprintf(
        calculator->expression,
        "%.2f",
        result
    );
}