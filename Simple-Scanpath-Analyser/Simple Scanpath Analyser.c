#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ScanpathList
{
    char str[100];
    struct ScanpathList *next;
} ScanpathList;

// Taking a scanpath file name and creating a linked list from the scanpaths read from that file
ScanpathList *createScanpathList(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("\nError! %s cannot open or doesn't exist!", fileName);
        exit(1);
    }

    ScanpathList *headScanpath = (ScanpathList *)malloc(sizeof(ScanpathList));
    headScanpath->next = NULL;
    ScanpathList *scanpath = headScanpath;

    while (!feof(file))
    {
        while (scanpath->next != NULL)
        {
            scanpath = scanpath->next;
        }
        scanpath->next = (ScanpathList *)malloc(sizeof(ScanpathList));
        scanpath = scanpath->next;
        fscanf(file, "%s", scanpath->str);
        scanpath->next = NULL;
    }
    fclose(file);
    return headScanpath;
}

// Finding the most frequent digit using digit array
int mostFrequentDigit(int digitArr[])
{
    int maxValue = digitArr[0];
    int i;
    for (i = 1; i < 10; ++i)
    {
        if (digitArr[i] > maxValue)
        {
            maxValue = digitArr[i];
        }
    }
    return maxValue;
}

// Searching the pattern in the scanpath string of a list using Rabin-Karp Algorithm
void searchPatternInOneList(char *pattern, ScanpathList *scanpathList, int d, int q)
{
    ScanpathList *temp = scanpathList->next;
    int counter = 1, flag = 0;
    int patternCount = 0, scanpathCount = 0;
    int digitArr[10] = {0};
    do
    {
        int M = strlen(pattern);
        int N = strlen(temp->str);
        int i, j;
        int p = 0; // Hash value for pattern
        int t = 0; // Hash value for scanpath string
        int h = 1;

        // The value of h would be "pow(d, M-1)%q"
        for (i = 0; i < M - 1; i++)
        {
            h = (h * d) % q;
        }

        // Calculating the hash value of pattern and first window of scanpath string
        for (i = 0; i < M; i++)
        {
            p = (d * p + pattern[i]) % q;
            t = (d * t + temp->str[i]) % q;
        }

        int sameStr = 0;
        // Sliding the pattern over scanpath string one by one
        for (i = 0; i <= N - M; i++)
        {
            // Checking the hash values of current window of scanpath string and pattern
            // If the hash values match, it will check for characters one by one
            if (p == t)
            {
                // Checking for characters one by one
                for (j = 0; j < M; j++)
                {
                    if (temp->str[i + j] != pattern[j])
                    {
                        break;
                    }
                }

                // If p == t and pattern[0...M-1] = temp->str[i, i+1, ...i+M-1]
                if (j == M)
                {
                    int index;
                    flag = 1;
                    if (sameStr != 1)
                    {
                        scanpathCount++;
                        if (counter != 1)
                        {
                            printf("\n");
                        }
                        printf("%d. ", counter);
                    }
                    else
                    {
                        printf("    ");
                    }
                    sameStr = 1;
                    patternCount++;
                    for (index = 0; index <= N; index++)
                    {
                        if (index == i)
                        {
                            printf("[");
                        }
                        if (index == i + M)
                        {
                            printf("]");
                        }
                        printf("%c", temp->str[index]);
                        if (index < i)
                        {
                            digitArr[temp->str[index] - '0']++;
                        }
                    }
                }
            }

            // Calculating the hash value for the next window of scanpath string
            // Removing leading digit, adding trailing digit
            if (i < N - M)
            {
                t = (d * (t - temp->str[i] * h) + temp->str[i + M]) % q;

                // In case of getting a negative value of t, it convert it to positive
                if (t < 0)
                    t = (t + q);
            }
        }
        counter++;
        temp = temp->next;
    } while (temp != NULL);
    if (flag != 1)
    {
        printf("None");
    }
    else
    {
        int freqScanpath = mostFrequentDigit(digitArr);
        printf("\n%d patterns detected in %d scanpaths", patternCount, scanpathCount);
        printf("\nThe most frequent AOI before the pattern is/are %d\n\n", freqScanpath);
    }
}

// Maintaining searchPattern functionality
void searchPattern(char *pattern, ScanpathList *autismScanpath, ScanpathList *scanpath, int d, int q)
{
    printf("Detected patterns for people with autism:\n");
    searchPatternInOneList(pattern, autismScanpath, d, q);
    printf("Detected patterns for people without autism:\n");
    searchPatternInOneList(pattern, scanpath, d, q);
}

int main()
{
    ScanpathList *autismScanpath;
    ScanpathList *scanpath;
    char fileName[30], pattern[100];
    printf("Enter the file name for people with autism: ");
    scanf("%s", fileName);
    autismScanpath = createScanpathList(fileName);
    printf("Enter the file name for people without autism: ");
    scanf("%s", fileName);
    scanpath = createScanpathList(fileName);
    printf("Enter the pattern: ");
    scanf("%s", pattern);
    searchPattern(pattern, autismScanpath, scanpath, 10, 11);
    return 0;
}