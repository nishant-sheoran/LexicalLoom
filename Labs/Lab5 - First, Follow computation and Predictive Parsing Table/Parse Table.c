#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 20
#define MAX_SYMBOLS 10
#define MAX_LEN 10

char prod[MAX_RULES][MAX_LEN];
char first[MAX_SYMBOLS][MAX_LEN];
char follow[MAX_SYMBOLS][MAX_LEN];
char table[MAX_SYMBOLS][MAX_SYMBOLS][MAX_LEN];
char nonterminals[MAX_SYMBOLS], terminals[MAX_SYMBOLS];

int numRules = 0, numNonterminals, numTerminals;

// Check if a character is a terminal
int isTerminal(char c) {
    return !isupper(c) && c != '@';
}

// Add a character to a set (if not already present)
void addToSet(char *set, char c) {
    if (!strchr(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// Compute First set
void findFirst(char symbol, char *result) {
    if (isTerminal(symbol)) {
        addToSet(result, symbol);
        return;
    }

    for (int i = 0; i < numRules; i++) {
        if (prod[i][0] == symbol) {
            int j = 3; // Start after "A->"
            while (prod[i][j] != '\0') {
                if (prod[i][j] == '@') {
                    addToSet(result, '@');
                    break;
                }

                char tempSet[MAX_LEN] = "";
                findFirst(prod[i][j], tempSet);
                strcat(result, tempSet);

                if (!strchr(tempSet, '@')) break; // Stop if epsilon is not in First
                j++;
            }
        }
    }
}

// Compute Follow set
void findFollow(char symbol, char *result) {
    if (symbol == prod[0][0]) {
        addToSet(result, '$'); // Start symbol follows $
    }

    for (int i = 0; i < numRules; i++) {
        for (int j = 3; j < strlen(prod[i]); j++) {
            if (prod[i][j] == symbol) {
                if (prod[i][j + 1] != '\0') { // If there's a next symbol
                    char firstSet[MAX_LEN] = "";
                    findFirst(prod[i][j + 1], firstSet);
                    strcat(result, firstSet);

                    if (strchr(firstSet, '@')) {
                        findFollow(prod[i][0], result);
                    }
                } else { // If it's the last symbol
                    findFollow(prod[i][0], result);
                }
            }
        }
    }
}

// Construct Parsing Table
void constructParsingTable() {
    for (int i = 0; i < numNonterminals; i++)
        for (int j = 0; j < numTerminals; j++)
            strcpy(table[i][j], ""); // Initialize table

    for (int i = 0; i < numRules; i++) {
        char firstSet[MAX_LEN] = "";
        findFirst(prod[i][3], firstSet);

        for (int j = 0; j < strlen(firstSet); j++) {
            if (firstSet[j] != '@') {
                int row = strchr(nonterminals, prod[i][0]) - nonterminals;
                int col = strchr(terminals, firstSet[j]) - terminals;

                if (strlen(table[row][col]) > 0) { // Conflict detected
                    printf("Grammar is not LL(1). Conflict at table[%c, %c]\n",
                           prod[i][0], firstSet[j]);
                    return;
                }
                strcpy(table[row][col], prod[i]);
            }
        }

        if (strchr(firstSet, '@')) {
            char followSet[MAX_LEN] = "";
            findFollow(prod[i][0], followSet);

            for (int j = 0; j < strlen(followSet); j++) {
                int row = strchr(nonterminals, prod[i][0]) - nonterminals;
                int col = strchr(terminals, followSet[j]) - terminals;

                if (strlen(table[row][col]) > 0) { // Conflict detected
                    printf("Grammar is not LL(1). Conflict at table[%c, %c]\n",
                           prod[i][0], followSet[j]);
                    return;
                }
                strcpy(table[row][col], prod[i]);
            }
        }
    }
}

// Print Parsing Table
void printTable() {
    printf("\nPredictive Parsing Table:\n\n");
    printf("   ");
    for (int j = 0; j < numTerminals; j++)
        printf("%-10c", terminals[j]);
    printf("\n----------------------------------------------------\n");

    for (int i = 0; i < numNonterminals; i++) {
        printf("%c |", nonterminals[i]);
        for (int j = 0; j < numTerminals; j++) {
            printf("%-10s", table[i][j][0] ? table[i][j] : " ");
        }
        printf("\n----------------------------------------------------\n");
    }
}

// Read Productions with Multiple RHS Support
void readProductions() {
    int ruleCount;
    printf("Enter number of rules: ");
    scanf("%d", &ruleCount);
    getchar(); // Consume newline

    printf("Enter productions (e.g., E->TR or R->+TR|@):\n");
    for (int i = 0; i < ruleCount; i++) {
        char input[MAX_LEN];
        fgets(input, MAX_LEN, stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        // Splitting productions with '|'
        char *lhs = strtok(input, "->");
        char *rhs = strtok(NULL, "->");
        char *token = strtok(rhs, "|");

        while (token) {
            sprintf(prod[numRules], "%s->%s", lhs, token);
            numRules++;
            token = strtok(NULL, "|");
        }
    }
}

int main() {
    readProductions();

    printf("Enter number of non-terminals: ");
    scanf("%d", &numNonterminals);
    getchar();
    printf("Enter non-terminals: ");
    for (int i = 0; i < numNonterminals; i++)
        scanf(" %c", &nonterminals[i]);

    printf("Enter number of terminals: ");
    scanf("%d", &numTerminals);
    getchar();
    printf("Enter terminals: ");
    for (int i = 0; i < numTerminals; i++)
        scanf(" %c", &terminals[i]);

    constructParsingTable();
    printTable();

    return 0;
}