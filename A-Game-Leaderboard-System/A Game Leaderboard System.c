#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Champion
{
    char championName[51]; // 50 characters + 1 NULL character('\0') = 51
    float expectedWinRate;
    int battleNumber;
    int winNumber;
    float actualWinRate;
    float winRateRatio;
    float expectationSkew;
};
typedef struct Champion Champion;

void initializeChampions(char *, char *, int);
void getBattleData(char *, Champion *, int);
void computeWinRate(Champion *, int);
void heapSort(Champion *, int, int);
void heapify(Champion *, int, int, int);
void swap(Champion *, Champion *);
void printLeaderboard(Champion *, int);

int main(int argc, char **argv)
{
    // argv[0] holds the name of the file
    int criteria = atoi(argv[1]); // Converting a string type value to int
    char *ChampionDataFile = argv[2];
    char *BattlesDataFile = argv[3];

    if (criteria > 3 || criteria < 1)
    {
        printf("\nError!\n  Sorting criteria is not between 1-3.\n");
        exit(0);
    }

    initializeChampions(ChampionDataFile, BattlesDataFile, criteria);
    free(ChampionDataFile);
    free(BattlesDataFile);
    return 0;
}

void initializeChampions(char *ChampionDataFile, char *BattlesDataFile, int criteria)
{

    Champion *champions = (Champion *)malloc(sizeof(Champion));

    char ch, str[51]; // 50 characters + 1 NULL character('\0') = 51
    int i, j, lineCount = 1;
    int maxIndex;

    FILE *file = fopen(ChampionDataFile, "r"); // To open the file for reading
    if (file == NULL)
    {
        printf("Error! champions.txt cannot be opened or the file does not exist.\n"); // Error Message
        exit(1);
    }
    else
    {
        for (i = 0; fscanf(file, "%c", &ch) != EOF; i++) // Line Counter
        {
            if (ch == '\n')
            {
                lineCount++;
            }
        }
        // Reallocation of the memory
        champions = (Champion *)realloc(champions, sizeof(Champion) * lineCount);
        rewind(file);
        for (i = 0; i < lineCount; i++)
        {
            fscanf(file, "%s", str); // Initializing the struct values
            strcpy(champions[i].championName, str);
            fscanf(file, "%s", str);
            champions[i].expectedWinRate = atof(str); // Converting a string type value to float
            champions[i].battleNumber = 0;
            champions[i].winNumber = 0;
            champions[i].actualWinRate = 0.0;
            champions[i].winRateRatio = 0.0;
            champions[i].expectationSkew = 0.0;
        }
        fclose(file);
        getBattleData(BattlesDataFile, champions, lineCount);
        if (lineCount != 1) // Having single element in the heap
        {
            heapSort(champions, lineCount, criteria);
        }
        printLeaderboard(champions, lineCount);
        free(champions);
    }
}

void getBattleData(char *BattlesDataFile, Champion *champions, int championLine)
{
    char ch, str[51];
    int i, j, k, lineCount = 1;

    FILE *file = fopen(BattlesDataFile, "r"); // To open the file for reading

    if (file == NULL)
    {
        printf("Error! battles.txt cannot be opened or the file does not exist.\n"); // Error Message
        exit(1);
    }
    else
    {
        for (i = 0; fscanf(file, "%c", &ch) != EOF; i++) // Line Counter
        {
            if (ch == '\n')
            {
                lineCount++;
            }
        }
        rewind(file);
        for (i = 0; i < lineCount; i++)
        {
            fscanf(file, "%s", str); // BattleID
            fscanf(file, "%s", str); // BattleParticipant1
            k = 0;
            while (k < championLine)
            {
                if (strcmp(champions[k].championName, str) == 0)
                {
                    champions[k].battleNumber++;
                }
                k++;
            };
            fscanf(file, "%s", str); // BattleParticipant2
            k = 0;
            while (k < championLine)
            {
                if (strcmp(champions[k].championName, str) == 0)
                {
                    champions[k].battleNumber++;
                }
                k++;
            };
            fscanf(file, "%s", str); // Winner
            k = 0;
            while (k < championLine)
            {
                if (strcmp(champions[k].championName, str) == 0)
                {
                    champions[k].winNumber++;
                }
                k++;
            };
        }
    }
    fclose(file);
    computeWinRate(champions, championLine);
}

void computeWinRate(Champion *champions, int lineCount)
{
    for (int i = 0; i < lineCount; i++)
    {
        champions[i].actualWinRate = (float)(champions[i].winNumber) / (float)(champions[i].battleNumber);
        champions[i].winRateRatio = (champions[i].actualWinRate) / (champions[i].expectedWinRate);
        champions[i].expectationSkew = fabs(champions[i].winRateRatio - 1);
        // fabs() -> takes the absolute value of a float number
    }
}

void heapSort(Champion *champions, int maxIndex, int criteria)
{
    int i;
    // Building heap
    for (i = maxIndex / 2 - 1; i >= 0; i--)
    {
        heapify(champions, maxIndex, i, criteria);
    }
    // Extracting an element from heap one by one
    for (i = maxIndex - 1; i > 0; i--)
    {
        // Moving current root to end
        swap(&champions[0], &champions[i]);
        // Calling max heapify on the reduced heap
        heapify(champions, i, 0, criteria);
    }
}

void heapify(Champion *champions, int heapSize, int rootIndex, int criteria)
{
    int largest = rootIndex;            // Initializing the largest as root
    int leftChild = 2 * rootIndex + 1;  // leftChild = 2*i + 1
    int rightChild = 2 * rootIndex + 2; // rightChild = 2*i + 2

    if (criteria == 1) // Sorting wrt actualWinRate
    {
        // If left child is larger than largest, left child will be the new largest value
        if (leftChild < heapSize && champions[leftChild].actualWinRate > champions[largest].actualWinRate)
        {
            largest = leftChild;
        }
        // If right child is larger than largest, right child will be the new largest value
        if (rightChild < heapSize && champions[rightChild].actualWinRate > champions[largest].actualWinRate)
        {
            largest = rightChild;
        }
        // If root is not the largest
        if (largest != rootIndex)
        {
            // Swapping the root with the new largest value
            swap(&champions[rootIndex], &champions[largest]);
            heapify(champions, heapSize, largest, criteria);
        }
    }
    else if (criteria == 2) // Sorting wrt expectedWinRate
    {
        if (leftChild < heapSize && champions[leftChild].expectedWinRate > champions[largest].expectedWinRate)
        {
            largest = leftChild;
        }
        if (rightChild < heapSize && champions[rightChild].expectedWinRate > champions[largest].expectedWinRate)
        {
            largest = rightChild;
        }
        if (largest != rootIndex)
        {
            swap(&champions[rootIndex], &champions[largest]);
            heapify(champions, heapSize, largest, criteria);
        }
    }
    else // Sorting wrt expectationSkew
    {
        if (leftChild < heapSize && champions[leftChild].expectationSkew > champions[largest].expectationSkew)
        {
            largest = leftChild;
        }
        if (rightChild < heapSize && champions[rightChild].expectationSkew > champions[largest].expectationSkew)
        {
            largest = rightChild;
        }
        if (largest != rootIndex)
        {
            swap(&champions[rootIndex], &champions[largest]);
            heapify(champions, heapSize, largest, criteria);
        }
    }
}

void swap(Champion *champion1, Champion *champion2)
{
    Champion temp = *champion1;
    *champion1 = *champion2;
    *champion2 = temp;
}

// Printing the leaderboard
void printLeaderboard(Champion *champions, int lineCount)
{
    printf("Champion    Battles    Win    AWR     EWR     Skew\n");
    for (int i = lineCount - 1; i >= 0; i--)
    {
        printf("%-15s%-9d%-6d%-8.2f%-8.2f%.2f\n", champions[i].championName, champions[i].battleNumber,
               champions[i].winNumber, champions[i].actualWinRate, champions[i].expectedWinRate,
               champions[i].expectationSkew);
    }
}