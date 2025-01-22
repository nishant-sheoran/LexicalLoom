#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define INITIAL_STACK_SIZE 100

// Dynamic stack structure for values and operators
typedef struct {
    double *values;
    char *operators;
    int valuesTop;
    int operatorsTop;
    int capacity;
} CalculatorStack;

// Function prototypes
CalculatorStack *createStack(int capacity);
void freeStack(CalculatorStack *stack);
void pushValue(CalculatorStack *stack, double value);
double popValue(CalculatorStack *stack);
void pushOperator(CalculatorStack *stack, char op);
char popOperator(CalculatorStack *stack);
int precedence(char op);
double applyOperator(double a, double b, char op);
double evaluateExpression(const char *expr, int precision);
void validateExpression(const char *expr);

// Create a dynamic stack
CalculatorStack *createStack(int capacity) {
    CalculatorStack *stack = (CalculatorStack *)malloc(sizeof(CalculatorStack));
    stack->values = (double *)malloc(capacity * sizeof(double));
    stack->operators = (char *)malloc(capacity * sizeof(char));
    stack->valuesTop = -1;
    stack->operatorsTop = -1;
    stack->capacity = capacity;
    return stack;
}

// Free the dynamic stack
void freeStack(CalculatorStack *stack) {
    free(stack->values);
    free(stack->operators);
    free(stack);
}

// Push a value onto the stack
void pushValue(CalculatorStack *stack, double value) {
    if (stack->valuesTop == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->values = (double *)realloc(stack->values, stack->capacity * sizeof(double));
    }
    stack->values[++stack->valuesTop] = value;
}

// Pop a value from the stack
double popValue(CalculatorStack *stack) {
    return stack->values[stack->valuesTop--];
}

// Push an operator onto the stack
void pushOperator(CalculatorStack *stack, char op) {
    if (stack->operatorsTop == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->operators = (char *)realloc(stack->operators, stack->capacity * sizeof(char));
    }
    stack->operators[++stack->operatorsTop] = op;
}

// Pop an operator from the stack
char popOperator(CalculatorStack *stack) {
    return stack->operators[stack->operatorsTop--];
}

// Determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Apply an operator to two operands
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero is not allowed.\n");
                return NAN;
            }
            return a / b;
        case '^': return pow(a, b);
        default:
            printf("Error: Invalid operator.\n");
            return NAN;
    }
}

// Validate the expression for mismatched parentheses and invalid characters
void validateExpression(const char *expr) {
    int openParentheses = 0;
    for (int i = 0; i < strlen(expr); i++) {
        if (expr[i] == '(') openParentheses++;
        if (expr[i] == ')') openParentheses--;
        if (openParentheses < 0) {
            printf("Error: Mismatched parentheses.\n");
            exit(1);
        }
        if (!isdigit(expr[i]) && !isspace(expr[i]) && expr[i] != '.' && expr[i] != '(' && expr[i] != ')' && !strchr("+-*/^", expr[i])) {
            printf("Error: Invalid character '%c' in expression.\n", expr[i]);
            exit(1);
        }
    }
    if (openParentheses != 0) {
        printf("Error: Mismatched parentheses.\n");
        exit(1);
    }
}

// Evaluate the expression
double evaluateExpression(const char *expr, int precision) {
    CalculatorStack *stack = createStack(INITIAL_STACK_SIZE);

    for (int i = 0; i < strlen(expr); i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i]) || expr[i] == '.') {
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
            pushValue(stack, value);
            i--;
        } else if (expr[i] == '(') {
            pushOperator(stack, expr[i]);
        } else if (expr[i] == ')') {
            while (stack->operatorsTop >= 0 && stack->operators[stack->operatorsTop] != '(') {
                double b = popValue(stack);
                double a = popValue(stack);
                char op = popOperator(stack);
                pushValue(stack, applyOperator(a, b, op));
            }
            popOperator(stack);
        } else {
            while (stack->operatorsTop >= 0 && precedence(stack->operators[stack->operatorsTop]) >= precedence(expr[i])) {
                double b = popValue(stack);
                double a = popValue(stack);
                char op = popOperator(stack);
                pushValue(stack, applyOperator(a, b, op));
            }
            pushOperator(stack, expr[i]);
        }
    }

    while (stack->operatorsTop >= 0) {
        double b = popValue(stack);
        double a = popValue(stack);
        char op = popOperator(stack);
        pushValue(stack, applyOperator(a, b, op));
    }

    double result = popValue(stack);
    freeStack(stack);
    return round(result * pow(10, precision)) / pow(10, precision);
}

int main() {
    char expression[256];
    int precision;

    printf("Welcome to SmartCalc!\n");
    printf("Enter the desired precision for results: ");
    scanf("%d", &precision);
    getchar(); // Consume newline after precision input

    printf("\nEnter mathematical expressions (Ctrl+D to exit):\n");

    while (fgets(expression, sizeof(expression), stdin)) {
        size_t len = strlen(expression);
        if (expression[len - 1] == '\n') {
            expression[len - 1] = '\0';
        }

        validateExpression(expression);

        double result = evaluateExpression(expression, precision);
        if (!isnan(result)) {
            printf("Result: %.*lf\n", precision, result);
        }

        printf("\nEnter another expression: ");
    }

    printf("\nThank you for using SmartCalc!\n");
    return 0;
}
