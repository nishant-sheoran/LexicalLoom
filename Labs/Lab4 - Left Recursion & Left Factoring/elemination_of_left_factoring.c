#include <stdio.h>
#include <string.h>
int main()
{
    char gram[20], part_1[20], part_2[20], modified_Gram[20], new_Gram[20], temp_Gram[20];
    int i, j = 0, k = 0, l = 0, pos;
    printf("Enter the Production : A->");
    gets(gram);
    for (i = 0; gram[i] != '|'; i++, j++)
        part_1[j] = gram[i];
    part_1[j] = '\0';
    for (j = ++i, i = 0; gram[j] != '\0'; j++, i++)
        part_2[i] = gram[j];
    part_2[i] = '\0';
    for (i = 0; i < strlen(part_1) || i < strlen(part_2); i++)
    {
        if (part_1[i] == part_2[i])
        {
            modified_Gram[k] = part_1[i];
            k++;
            pos = i + 1;
        }
    }
    for (i = pos, j = 0; part_1[i] != '\0'; i++, j++)
    {
        new_Gram[j] = part_1[i];
    }
    new_Gram[j++] = '|';
    for (i = pos; part_2[i] != '\0'; i++, j++)
    {
        new_Gram[j] = part_2[i];
    }
    modified_Gram[k] = 'X';
    modified_Gram[++k] = '\0';
    new_Gram[j] = '\0';
    printf("\nGrammar Without Left Factoring is: \n");
    printf(" A->%s", modified_Gram);
    printf("\n X->%s\n", new_Gram);
}