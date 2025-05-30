#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Global Variables
int z = 0, i = 0, j = 0, c = 0;
char a[50], ac[20], stk[50], act[10];
char grammar[10][10];
int num_rules;

// Function to check for reduction rules
void check()
{
    strcpy(ac, "REDUCE TO E -> ");
    int len;
    for(z = 0; z < i; z++) 
    {
        for(int k = 0; k < num_rules; k++)
        {
            len = strlen(grammar[k]) - 3;
            if(len > 0 && strncmp(&stk[z], &grammar[k][3], len) == 0)
            {
                printf("%s%s", ac, &grammar[k][3]);
                stk[z] = 'E';
                memmove(&stk[z + 1], &stk[z + len], strlen(&stk[z + len]) + 1);
                i -= (len - 1);
                printf("\n$%s\t%s$\t", stk, a);
                z = -1;
                break;
            }
        }
    }
}

int main()
{
    printf("Enter number of grammar rules: ");
    scanf("%d", &num_rules);
    getchar();
    printf("Enter grammar rules (format: E->XYZ):\n");
    for(int k = 0; k < num_rules; k++) {
        fgets(grammar[k], 10, stdin);
        grammar[k][strcspn(grammar[k], "\n")] = 0; // Remove newline
    }
    
    printf("Enter input string: ");
    scanf("%s", a);
    
    c = strlen(a); 
    strcpy(act, "SHIFT");
    
    printf("\nstack \t input \t action\n");
    printf("\n$\t%s$\t", a);
    
    for(i = 0; j < c; i++, j++) 
    {
        printf("%s", act);
        stk[i] = a[j];     
        stk[i + 1] = '\0';
        a[j] = ' ';
        printf("\n$%s\t%s$\t", stk, a);
        check(); 
    }
    
    check(); 
    
    if(strcmp(stk, "E") == 0) 
        printf("Accept\n");
    else
        printf("Reject\n");
    
return 0;
}