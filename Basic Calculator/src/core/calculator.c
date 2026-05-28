#include "calculator.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <float.h>

#define MAX_EXPRESSION_LENGTH 256

static int IsValidCharacter(char c)
{
    return
        (c >= '0' && c <= '9') ||
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/' ||
        c == '.' ||
        c == '(' ||
        c == ')';
}

static int IsOperator(char c)
{
    return
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/';
}

static int HasUnclosedParentheses(
    const char* expr
)
{
    int count = 0;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (expr[i] == '(')
            count++;

        if (expr[i] == ')')
            count--;
    }

    return count > 0;
}

static int IsSafeToAppend(
    const char* expression,
    char newChar
)
{
    int length = strlen(expression);

    // Prevent Overflow
    if (length >= MAX_EXPRESSION_LENGTH - 1)
    {
        return 0;
    }

    // First Character Rules
    if (length == 0)
    {
        if (
            newChar == '*' ||
            newChar == '/' ||
            newChar == ')' ||
            newChar == '.'
        )
        {
            return 0;
        }

        return 1;
    }

    char last =
        expression[length - 1];

    // Prevent Double Operators
    if (
        IsOperator(last) &&
        IsOperator(newChar)
    )
    {
        return 0;
    }

    // Prevent Empty Parentheses
    if (
        last == '(' &&
        newChar == ')'
    )
    {
        return 0;
    }

    // Prevent Invalid Operator After (
    if (
        last == '(' &&
        (
            newChar == '*' ||
            newChar == '/' ||
            newChar == '+'
        )
    )
    {
        return 0;
    }

    // Prevent ) After Operator
    if (
        IsOperator(last) &&
        newChar == ')'
    )
    {
        return 0;
    }

    // Prevent Multiple Decimals
    if (newChar == '.')
    {
        for (
            int i = length - 1;
            i >= 0;
            i--
        )
        {
            if (expression[i] == '.')
            {
                return 0;
            }

            if (
                IsOperator(expression[i]) ||
                expression[i] == '(' ||
                expression[i] == ')'
            )
            {
                break;
            }
        }
    }

    // Prevent Closing Without Opening
    if (newChar == ')')
    {
        if (!HasUnclosedParentheses(expression))
        {
            return 0;
        }
    }

    return 1;
}

void AppendToExpression(
    CalculatorState* calculator,
    const char* value
)
{
    for (int i = 0; value[i] != '\0'; i++)
    {
        char c = value[i];

        // Invalid Character
        if (!IsValidCharacter(c))
        {
            continue;
        }

        // Unsafe Input
        if (
            !IsSafeToAppend(
                calculator->expression,
                c
            )
        )
        {
            continue;
        }

        int length =
            strlen(calculator->expression);

        calculator->expression[length] = c;

        calculator->expression[length + 1] = '\0';
    }
}

void RemoveLastCharacter(
    CalculatorState* calculator
)
{
    int length =
        strlen(calculator->expression);

    if (length > 0)
    {
        calculator->expression[length - 1] = '\0';
    }
}

void ClearExpression(
    CalculatorState* calculator
)
{
    calculator->expression[0] = '\0';
}

static int Precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

static double ApplyOperator(
    double a,
    double b,
    char op,
    int* error
)
{
    // Division By Zero
    if (
        op == '/' &&
        fabs(b) < 0.0000001
    )
    {
        *error = 1;
        return 0;
    }

    double result = 0;

    switch (op)
    {
        case '+':
            result = a + b;
            break;

        case '-':
            result = a - b;
            break;

        case '*':
            result = a * b;
            break;

        case '/':
            result = a / b;
            break;
    }

    // Infinity / NaN Check
    if (
        isnan(result) ||
        isinf(result)
    )
    {
        *error = 2;
        return 0;
    }

    // Overflow Check
    if (
        fabs(result) > DBL_MAX
    )
    {
        *error = 3;
        return 0;
    }

    return result;
}

void EvaluateExpression(
    CalculatorState* calculator
)
{
    double values[256];

    char operators[256];

    int valueTop = -1;
    int operatorTop = -1;

    int error = 0;

    char* expr =
        calculator->expression;

    int i = 0;

    while (expr[i] != '\0')
    {
        // Number
        if (
            isdigit(expr[i]) ||
            expr[i] == '.'
        )
        {
            char number[64];

            int j = 0;

            while (
                isdigit(expr[i]) ||
                expr[i] == '.'
            )
            {
                number[j++] = expr[i++];
            }

            number[j] = '\0';

            values[++valueTop] =
                atof(number);

            continue;
        }

        // Left Parenthesis
        if (expr[i] == '(')
        {
            operators[++operatorTop] =
                expr[i];
        }

        // Right Parenthesis
        else if (expr[i] == ')')
        {
            while (
                operatorTop >= 0 &&
                operators[operatorTop] != '('
            )
            {
                if (valueTop < 1)
                {
                    strcpy(
                        calculator->expression,
                        "SYNTAX ERROR"
                    );

                    return;
                }

                double b =
                    values[valueTop--];

                double a =
                    values[valueTop--];

                char op =
                    operators[operatorTop--];

                double result =
                    ApplyOperator(
                        a,
                        b,
                        op,
                        &error
                    );

                if (error == 1)
                {
                    strcpy(
                        calculator->expression,
                        "DIV BY ZERO"
                    );

                    return;
                }

                if (error == 2)
                {
                    strcpy(
                        calculator->expression,
                        "INVALID"
                    );

                    return;
                }

                if (error == 3)
                {
                    strcpy(
                        calculator->expression,
                        "OVERFLOW"
                    );

                    return;
                }

                values[++valueTop] =
                    result;
            }

            operatorTop--;
        }

        // Operator
        else
        {
            while (
                operatorTop >= 0 &&
                Precedence(
                    operators[operatorTop]
                ) >= Precedence(expr[i])
            )
            {
                if (valueTop < 1)
                {
                    strcpy(
                        calculator->expression,
                        "SYNTAX ERROR"
                    );

                    return;
                }

                double b =
                    values[valueTop--];

                double a =
                    values[valueTop--];

                char op =
                    operators[operatorTop--];

                double result =
                    ApplyOperator(
                        a,
                        b,
                        op,
                        &error
                    );

                if (error == 1)
                {
                    strcpy(
                        calculator->expression,
                        "DIV BY ZERO"
                    );

                    return;
                }

                if (error == 2)
                {
                    strcpy(
                        calculator->expression,
                        "INVALID"
                    );

                    return;
                }

                if (error == 3)
                {
                    strcpy(
                        calculator->expression,
                        "OVERFLOW"
                    );

                    return;
                }

                values[++valueTop] =
                    result;
            }

            operators[++operatorTop] =
                expr[i];
        }

        i++;
    }

    while (operatorTop >= 0)
    {
        if (valueTop < 1)
        {
            strcpy(
                calculator->expression,
                "SYNTAX ERROR"
            );

            return;
        }

        double b =
            values[valueTop--];

        double a =
            values[valueTop--];

        char op =
            operators[operatorTop--];

        double result =
            ApplyOperator(
                a,
                b,
                op,
                &error
            );

        if (error == 1)
        {
            strcpy(
                calculator->expression,
                "DIV BY ZERO"
            );

            return;
        }

        if (error == 2)
        {
            strcpy(
                calculator->expression,
                "INVALID"
            );

            return;
        }

        if (error == 3)
        {
            strcpy(
                calculator->expression,
                "OVERFLOW"
            );

            return;
        }

        values[++valueTop] =
            result;
    }

    sprintf(
        calculator->expression,
        "%.6g",
        values[valueTop]
    );
}