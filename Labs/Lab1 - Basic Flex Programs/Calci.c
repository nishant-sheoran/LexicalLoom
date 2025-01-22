#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Function to apply an operator to two operands
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero, learn some maths first dumbo!\n");
                exit(1);  // Exit the program due to division by zero
            }
            return a / b;
        case '^': return pow(a, b);
        default:
            printf("Error: Invalid operator stop torturing my calci\n");
            exit(1);  // Exit the program due to invalid operator
    }
}

// Function to determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to evaluate the expression
double evaluateExpression(const char *expr) {
    double values[100]; // Stack for numbers
    char operators[100]; // Stack for operators
    int valuesTop = -1, operatorsTop = -1; // Stack pointers

    int i; // Declare the loop variable outside the for loop cuz this compiler is the worst and throws wild errors
    for (i = 0; i < strlen(expr); i++) {
        if (isspace(expr[i])) continue; // Ignore spaces

        if (isdigit(expr[i]) || expr[i] == '.') {
            // Parse a number (including decimals)
            double value = 0;
            int isDecimal = 0;
            double decimalDivisor = 1;

            while (i < strlen(expr) && (isdigit(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    isDecimal = 1;
                } else if (isDecimal) {
                    decimalDivisor *= 10;
                    value += (expr[i] - '0') / decimalDivisor;
                } else {
                    value = value * 10 + (expr[i] - '0');
                }
                i++;
            }
            values[++valuesTop] = value;
            i--; // Adjust index to process correctly
        } else if (expr[i] == '(') {
            operators[++operatorsTop] = expr[i]; // Push '(' onto the operators stack, its important if you are giving expressions to the calci although why are you doing that in the first place !!!!!
        } else if (expr[i] == ')') {
            // Solve the expression inside parentheses
            while (operatorsTop >= 0 && operators[operatorsTop] != '(') {
                double b = values[valuesTop--];
                double a = values[valuesTop--];
                char op = operators[operatorsTop--];
                values[++valuesTop] = applyOperator(a, b, op);
            }
            operatorsTop--; // Remove '(' from the stack, ofc !
        } else {
            // Handle operators
            while (operatorsTop >= 0 && precedence(operators[operatorsTop]) >= precedence(expr[i])) {
                double b = values[valuesTop--];
                double a = values[valuesTop--];
                char op = operators[operatorsTop--];
                values[++valuesTop] = applyOperator(a, b, op);
            }
            operators[++operatorsTop] = expr[i];
        }
    }

    // Perform the remaining operations
    while (operatorsTop >= 0) {
        double b = values[valuesTop--];
        double a = values[valuesTop--];
        char op = operators[operatorsTop--];
        values[++valuesTop] = applyOperator(a, b, op);
    }

    return values[valuesTop];
}

int main() {
    char expression[256];

    printf("Simple Calculator (Enter Ctrl+D to exit)\n");
    printf("Enter an expression: ");

    while (fgets(expression, sizeof(expression), stdin)) {
        // Remove trailing newline character
        size_t len = strlen(expression);
        if (expression[len - 1] == '\n') {
            expression[len - 1] = '\0';
        }

        // Evaluate the expression
        double result = evaluateExpression(expression);
        printf("Result: %.2lf\n", result);

        printf("Enter another expression: ");
    }

    return 0;
}