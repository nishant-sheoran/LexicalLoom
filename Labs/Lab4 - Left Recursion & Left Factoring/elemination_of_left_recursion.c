#include <stdio.h>
#include <string.h>

#define MAX 100

void eliminateLeftRecursion(char nonTerminal, char alpha[][MAX], int alphaCount, char beta[][MAX], int betaCount) {
    char newNonTerminal = nonTerminal + '\''; // A'
    
    printf("Transformed Grammar:\n");
    printf("%c -> ", nonTerminal);
    
    // Print βA' rules
    for (int i = 0; i < betaCount; i++) {
        printf("%s%c", beta[i], newNonTerminal);
        if (i < betaCount - 1) printf(" | ");
    }
    printf("\n");

    // Print A' → αA' | ε rules
    printf("%c -> ", newNonTerminal);
    for (int i = 0; i < alphaCount; i++) {
        printf("%s%c", alpha[i], newNonTerminal);
        if (i < alphaCount - 1) printf(" | ");
    }
    printf(" | ε\n");
}

int main() {
    char nonTerminal;
    char productions[MAX][MAX];
    int prodCount;

    printf("Enter the non-terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter the number of productions: ");
    scanf("%d", &prodCount);

    printf("Enter the productions:\n");
    for (int i = 0; i < prodCount; i++) {
        scanf("%s", productions[i]);
    }

    char alpha[MAX][MAX], beta[MAX][MAX];
    int alphaCount = 0, betaCount = 0;

    // Separate α and β
    for (int i = 0; i < prodCount; i++) {
        if (productions[i][0] == nonTerminal) {
            strcpy(alpha[alphaCount++], productions[i] + 1); // Remove non-terminal prefix
        } else {
            strcpy(beta[betaCount++], productions[i]); // Keep β as is
        }
    }

    if (alphaCount == 0) {
        printf("No Left Recursion Detected.\n");
    } else {
        eliminateLeftRecursion(nonTerminal, alpha, alphaCount, beta, betaCount);
    }

    return 0;
}
