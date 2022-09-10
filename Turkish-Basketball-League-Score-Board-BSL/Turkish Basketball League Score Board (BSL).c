#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table
{
    char team[50];
    int tG;
    int wH;
    int lH;
    int wA;
    int lA;
    int wC;
    int lC;
    int tP;
};

void Load_Scoreboard_Table();
void Display_Scoreboard_Table();
void Search();
void interactive_board();

int main()
{
    struct table *p =
        (struct table *)malloc(sizeof(struct table)); /*To make pointer structure declaration dynamically*/
    char file_name[20] = "input.txt";
    char myString[200], ch;
    char selection1[20];
    char selection2[20];
    int line = 1, i;
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        line = 0;
        Display_Scoreboard_Table(line, p);
    }
    else
    {
        for (i = 0; fscanf(file, "%c", &ch) != EOF; i++)
        {
            if (ch == '\n')
            {
                line++;
            }
        }
        p = (struct table *)realloc(p, line * sizeof(struct table)); /*Reallocation of memory*/
        fclose(file);
        Load_Scoreboard_Table(file_name, &myString, p); /*Structure type pass by reference*/
        Display_Scoreboard_Table(line, p);
        do
        {
            printf("Enter the name of the team (Exit - X, Sort - S):");
            gets(selection1);
            if (strcmp(selection1, "X") == 0 ||
                strcmp(selection1, "x") ==
                    0) /*To compare 2 strings from each other and if they are the same, exit from the loop*/
            {
                printf("Bye!");
                break;
            }
            else
            {
                if (strcmp(selection1, "S") == 0 ||
                    strcmp(selection1, "s") == 0) /*To compare 2 strings from each other*/
                {
                    printf("Sort by (G: games, P: points):");
                    gets(selection2);
                    interactive_board(line, selection2, p);
                }
                else
                {
                    Search(selection1, p, line);
                }
            }
        } while (strcmp(selection1, "X") != 0 && strcmp(selection1, "x") != 0);
    }
    return 0;
}

void Load_Scoreboard_Table(char *file_name, char *myString, struct table *p)
{
    char ch;
    int total_line = 1, counter, counter2;
    char *tok;                          /*To separate the string*/
    FILE *file = fopen(file_name, "r"); /*To open the files for reading purpose*/
    if (file == NULL)
    {
        total_line = 0; /*Error Message*/
        Display_Scoreboard_Table(total_line, p);
    }
    else
    {
        for (counter = 0; fscanf(file, "%c", &ch) != EOF; counter++)
        {
            if (ch == '\n')
            {
                total_line++; /*To count the # of lines and change new line to semicolon to use tok properly*/
                ch = ';';
            }
        }
        rewind(file);
        for (counter = 0; counter < total_line; counter++)
        {
            fscanf(file, "%s", myString);               /*To read the each line as string*/
            tok = strtok(myString, ";");                /*To separate the string from the semicolon */
            for (counter2 = 0; tok != NULL; counter2++) /*Reading input from a file and load it to structs*/
            {
                switch (counter2)
                {
                case 0:
                    strcpy(p->team, tok);
                    break;
                case 1:
                    p->tG = atoi(tok);
                    break;
                case 2:
                    p->wH = atoi(tok);
                    break;
                case 3:
                    p->lH = atoi(tok);
                    break;
                case 4:
                    p->wA = atoi(tok);
                    break;
                case 5:
                    p->lA = atoi(tok);
                    break;
                case 6:
                    p->wC = atoi(tok);
                    break;
                case 7:
                    p->lC = atoi(tok);
                    break;
                case 8:
                    p->tP = atoi(tok);
                    break;
                }
                tok = strtok(NULL, ";");
            }
            p++;
        }
        fclose(file);
    }
}
void Display_Scoreboard_Table(int line, struct table *p)
{
    int counter;
    if (line == 0) /*To check the permission*/
    {
        printf("You cannot have any permission to read this file or the file is empty!");
    }
    else
    {
        printf("Score records file has been successfully loaded!\n");
        printf("Following records have been loaded:\n");
        printf("Team\t\tG\tWH\tLH\tWA\tLA\tWin\tLost\tPoints\n");
        for (counter = 0; counter < line; counter++)
        {
            printf("%-10s\t%d\t%d\t%d\t%d\t%d\t%d\t%3d\t%4d\n", p->team, p->tG, p->wH, p->lH, p->wA, p->lA, p->wC,
                   p->lC, p->tP); /*To print the scoreboard table to the screen using structures*/
            p++;
        }
    }
}
void Search(char str[20], struct table *p, int line)
{
    int i = 0, valid = 0;
    for (i = 0; i < line; i++)
    {
        if (strcmp(str, p->team) == 0) /*To compare 2 strings from each other*/
        {
            printf("%s has %d win, %d lost and total of %d points!\n", p->team, p->wC, p->lC, p->tP);
            valid = 1;
        }
        p++;
    }
    if (valid == 0)
    {
        printf("That team is unknown! Please try again!\n");
    }
}
void interactive_board(int line, char str2[20], struct table *p)
{
    int i, j;
    struct table temp;
    if (strcmp(str2, "G") == 0 || strcmp(str2, "g") == 0) /*To compare 2 strings from each other*/
    {
        for (i = 0; i < line - 1; i++) /*Bubble sort algorithm*/
        {
            for (j = 0; j < (line - 1 - i); j++)
            {
                if (p[j].tG < p[j + 1].tG)
                {
                    temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
        printf("Team\t\tG\tWH\tLH\tWA\tLA\tWin\tLost\tPoints\n");
        for (i = 0; i < line; i++)
        {
            printf("%-10s\t%d\t%d\t%d\t%d\t%d\t%d\t%3d\t%4d\n", p->team, p->tG, p->wH, p->lH, p->wA, p->lA, p->wC,
                   p->lC, p->tP); /*To print the structures*/
            p++;
        }
    }
    else if (strcmp(str2, "P") == 0 || strcmp(str2, "p") == 0) /*To compare 2 strings from each other*/
    {
        for (i = 0; i < line; i++) /*Bubble sort algorithm*/
        {
            for (j = 0; j < (line - 1 - i); j++)
            {
                if (p[j].tP < p[j + 1].tP)
                {
                    temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
        printf("Team\t\tG\tWH\tLH\tWA\tLA\tWin\tLost\tPoints\n");
        for (i = 0; i < line; i++)
        {
            printf("%-10s\t%d\t%d\t%d\t%d\t%d\t%d\t%3d\t%4d\n", p->team, p->tG, p->wH, p->lH, p->wA, p->lA, p->wC,
                   p->lC, p->tP); /*To print the structures*/
            p++;
        }
    }
    else
    {
        printf("This is not a valid selection.Please try again!\n"); /*Error Message*/
    }
}
