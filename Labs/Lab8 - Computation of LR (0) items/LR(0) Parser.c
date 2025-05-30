#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char lhs;
    char rhs[10];
} Production;

typedef struct {
    char lhs;
    char rhs[10];
} Item;

Production productions[MAX];
Item items[MAX][MAX];
int itemCount[MAX];
int n, stateCount = 0;
char symbols[MAX];
int symbolCount = 0;

int isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

int productionExists(Item itemSet[], int count, Item item) {
    for (int i = 0; i < count; i++) {
        if (itemSet[i].lhs == item.lhs && strcmp(itemSet[i].rhs, item.rhs) == 0)
            return 1;
    }
    return 0;
}

void closure(Item closureSet[], int *closureCount) {
    int added = 1;
    while (added) {
        added = 0;
        for (int i = 0; i < *closureCount; i++) {
            char *dotPos = strchr(closureSet[i].rhs, '.');
            if (dotPos && *(dotPos + 1) && isNonTerminal(*(dotPos + 1))) {
                char B = *(dotPos + 1);
                for (int j = 0; j < n; j++) {
                    if (productions[j].lhs == B) {
                        Item newItem;
                        newItem.lhs = productions[j].lhs;
                        sprintf(newItem.rhs, ".%s", productions[j].rhs);
                        if (!productionExists(closureSet, *closureCount, newItem)) {
                            closureSet[(*closureCount)++] = newItem;
                            added = 1;
                        }
                    }
                }
            }
        }
    }
}

void gotoFunction(Item currentSet[], int count, char symbol, Item result[], int *resultCount) {
    *resultCount = 0;
    for (int i = 0; i < count; i++) {
        char *dotPos = strchr(currentSet[i].rhs, '.');
        if (dotPos && *(dotPos + 1) == symbol) {
            Item movedItem;
            movedItem.lhs = currentSet[i].lhs;
            strcpy(movedItem.rhs, currentSet[i].rhs);
            int pos = dotPos - currentSet[i].rhs;
            movedItem.rhs[pos] = symbol;
            movedItem.rhs[pos + 1] = '.';
            strcpy(movedItem.rhs + pos + 2, currentSet[i].rhs + pos + 2);

            result[(*resultCount)++] = movedItem;
        }
    }
    closure(result, resultCount);
}

int itemsEqual(Item a[], int aCount, Item b[], int bCount) {
    if (aCount != bCount) return 0;
    for (int i = 0; i < aCount; i++) {
        if (!productionExists(b, bCount, a[i]))
            return 0;
    }
    return 1;
}

int addItemSet(Item newSet[], int newCount) {
    for (int i = 0; i < stateCount; i++) {
        if (itemsEqual(items[i], itemCount[i], newSet, newCount))
            return i;
    }
    for (int i = 0; i < newCount; i++)
        items[stateCount][i] = newSet[i];
    itemCount[stateCount] = newCount;
    return stateCount++;
}

void computeLR0Items() {
    Item startItem;
    startItem.lhs = productions[0].lhs;
    sprintf(startItem.rhs, ".%s", productions[0].rhs);

    Item initialSet[MAX];
    int count = 0;
    initialSet[count++] = startItem;
    closure(initialSet, &count);

    addItemSet(initialSet, count);

    for (int i = 0; i < stateCount; i++) {
        for (int j = 0; j < symbolCount; j++) {
            Item gotoSet[MAX];
            int gotoCount = 0;
            gotoFunction(items[i], itemCount[i], symbols[j], gotoSet, &gotoCount);
            if (gotoCount > 0) {
                int state = addItemSet(gotoSet, gotoCount);
                printf("Goto(I%d, %c) = I%d\n", i, symbols[j], state);
            }
        }
    }

    for (int i = 0; i < stateCount; i++) {
        printf("\nI%d:\n", i);
        for (int j = 0; j < itemCount[i]; j++) {
            printf("  %c -> %s\n", items[i][j].lhs, items[i][j].rhs);
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (e.g., S->CC):\n");
    for (int i = 0; i < n; i++) {
        char prod[20];
        scanf("%s", prod);
        productions[i].lhs = prod[0];
        strcpy(productions[i].rhs, prod + 3);
    }

    // Collect grammar symbols
    for (int i = 0; i < n; i++) {
        for (int j = 0; productions[i].rhs[j]; j++) {
            char sym = productions[i].rhs[j];
            if (sym == '\0' || sym == '|' || sym == '.') continue;
            int found = 0;
            for (int k = 0; k < symbolCount; k++) {
                if (symbols[k] == sym) {
                    found = 1;
                    break;
                }
            }
            if (!found && sym != '\0')
                symbols[symbolCount++] = sym;
        }
    }

    computeLR0Items();
    return 0;
}