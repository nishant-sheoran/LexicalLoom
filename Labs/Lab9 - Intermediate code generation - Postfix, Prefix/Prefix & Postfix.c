#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Tree node
typedef struct Node {
    char data[10];
    struct Node *left, *right;
} Node;

// Stacks
char opStack[MAX];
int opTop = -1;

Node* nodeStack[MAX];
int nodeTop = -1;

// Operator precedence
int precedence(char op) {
    switch (op) {
        case '^': return 3;  // Highest precedence
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Check if operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

// Stack operations
void pushOp(char op) { opStack[++opTop] = op; }
char popOp() { return opStack[opTop--]; }
char peekOp() { return opStack[opTop]; }
int isEmptyOp() { return opTop == -1; }

void pushNode(Node* node) { nodeStack[++nodeTop] = node; }
Node* popNode() { return nodeStack[nodeTop--]; }

// Create new node
Node* createNode(char* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->data, data);
    node->left = node->right = NULL;
    return node;
}

// Infix to expression tree conversion
void infixToTree(const char* expr) {
    int i = 0;
    while (expr[i]) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isalnum(expr[i])) {
            char operand[10];
            int j = 0;
            while (isalnum(expr[i])) {
                operand[j++] = expr[i++];
            }
            operand[j] = '\0';
            pushNode(createNode(operand));
        }
        else if (expr[i] == '(') {
            pushOp(expr[i]);
            i++;
        }
        else if (expr[i] == ')') {
            while (!isEmptyOp() && peekOp() != '(') {
                char op[2] = { popOp(), '\0' };
                Node* right = popNode();
                Node* left = popNode();
                Node* opNode = createNode(op);
                opNode->left = left;
                opNode->right = right;
                pushNode(opNode);
            }
            if (!isEmptyOp() && peekOp() == '(')
                popOp(); // Pop '('
            else {
                printf("Mismatched parentheses!\n");
                exit(1);
            }
            i++;
        }
        else if (isOperator(expr[i])) {
            while (!isEmptyOp() && (
                (precedence(peekOp()) > precedence(expr[i])) ||
                (precedence(peekOp()) == precedence(expr[i]) && expr[i] != '^')  // Right-associative ^ only
            )) {
                char op[2] = { popOp(), '\0' };
                Node* right = popNode();
                Node* left = popNode();
                Node* opNode = createNode(op);
                opNode->left = left;
                opNode->right = right;
                pushNode(opNode);
            }
            pushOp(expr[i]);
            i++;
        } else {
            printf("Invalid character: %c\n", expr[i]);
            exit(1);
        }
    }

    while (!isEmptyOp()) {
        char op[2] = { popOp(), '\0' };
        Node* right = popNode();
        Node* left = popNode();
        Node* opNode = createNode(op);
        opNode->left = left;
        opNode->right = right;
        pushNode(opNode);
    }
}

// Traversals
void generatePrefix(Node* root) {
    if (!root) return;
    printf("%s ", root->data);
    generatePrefix(root->left);
    generatePrefix(root->right);
}

void generatePostfix(Node* root) {
    if (!root) return;
    generatePostfix(root->left);
    generatePostfix(root->right);
    printf("%s ", root->data);
}

int main() {
    char expr[100];
    printf("Enter infix expression (supports + - * / %% ^):\n");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0';  // remove newline

    infixToTree(expr);
    Node* root = popNode();

    printf("\nPrefix (Polish Notation): ");
    generatePrefix(root);
    printf("\n");

    printf("Postfix (Reverse Polish): ");
    generatePostfix(root);
    printf("\n");

    return 0;
}