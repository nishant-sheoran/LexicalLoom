#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char op[5];
    char arg1[10];
    char arg2[10];
    char result[10];
} Quad;

typedef struct {
    char op[5];
    char arg1[10];
    char arg2[10];
} Triple;

Quad quads[MAX];
Triple triples[MAX];
int triple_index[MAX];  // for indirect triples

char stack[MAX][10];
int top = -1;
int tempCount = 1;
int quadCount = 0;

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void push(char *s) {
    strcpy(stack[++top], s);
}

char* pop() {
    return stack[top--];
}

void generate_quad(char *op, char *arg1, char *arg2) {
    char temp[10];
    sprintf(temp, "t%d", tempCount++);
    strcpy(quads[quadCount].op, op);
    strcpy(quads[quadCount].arg1, arg1);
    strcpy(quads[quadCount].arg2, arg2);
    strcpy(quads[quadCount].result, temp);
    push(temp);
    quadCount++;
}

void print_quadruples() {
    printf("\nQuadruples:\n%-10s%-10s%-10s%-10s\n", "Op", "Arg1", "Arg2", "Result");
    for (int i = 0; i < quadCount; i++) {
        printf("%-10s%-10s%-10s%-10s\n", quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result);
    }
}

void print_triples() {
    printf("\nTriples:\n%-10s%-10s%-10s%-10s\n", "Index", "Op", "Arg1", "Arg2");
    for (int i = 0; i < quadCount; i++) {
        printf("%-10d%-10s%-10s%-10s\n", i, quads[i].op,
            strstr(quads[i].arg1, "t") ? quads[i].arg1 : quads[i].arg1,
            strstr(quads[i].arg2, "t") ? quads[i].arg2 : quads[i].arg2);
        strcpy(triples[i].op, quads[i].op);
        strcpy(triples[i].arg1, quads[i].arg1);
        strcpy(triples[i].arg2, quads[i].arg2);
    }
}

void print_indirect_triples() {
    printf("\nIndirect Triples:\n%-10s%-10s%-10s%-10s\n", "Pointer", "Op", "Arg1", "Arg2");
    for (int i = 0; i < quadCount; i++) {
        triple_index[i] = i;
        printf("%-10d%-10s%-10s%-10s\n", i, triples[i].op, triples[i].arg1, triples[i].arg2);
    }
}

int main() {
    char input[100], *token;
    char lhs[10], expr[100], postfix[MAX][10];
    int postIndex = 0;
    char opStack[MAX][10];
    int opTop = -1;

    printf("Enter expression (e.g., a = b + c * d): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // remove newline

    token = strtok(input, " ");
    strcpy(lhs, token); // left-hand side variable
    token = strtok(NULL, " "); // skip '='

    // Convert to postfix
    while ((token = strtok(NULL, " ")) != NULL) {
        if (isalnum(token[0])) {
            strcpy(postfix[postIndex++], token);
        } else if (strchr("+-*/", token[0])) {
            while (opTop >= 0 && precedence(opStack[opTop][0]) >= precedence(token[0])) {
                strcpy(postfix[postIndex++], opStack[opTop--]);
            }
            strcpy(opStack[++opTop], token);
        }
    }
    while (opTop >= 0) {
        strcpy(postfix[postIndex++], opStack[opTop--]);
    }

    // Generate Quadruples
    for (int i = 0; i < postIndex; i++) {
        if (isalnum(postfix[i][0])) {
            push(postfix[i]);
        } else {
            char *op2 = pop();
            char *op1 = pop();
            generate_quad(postfix[i], op1, op2);
        }
    }

    // Final assignment (a = tN)
    strcpy(quads[quadCount].op, "=");
    strcpy(quads[quadCount].arg1, stack[top]);
    strcpy(quads[quadCount].arg2, "-");
    strcpy(quads[quadCount].result, lhs);
    quadCount++;

    // Print All
    print_quadruples();
    print_triples();
    print_indirect_triples();

    return 0;
}