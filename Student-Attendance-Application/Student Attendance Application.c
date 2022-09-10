#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student Data Structure
// I added 1 extra byte to all the character arrays for string terminator value which is NULL
typedef struct Student
{
    char studentID[4];
    char name[41];
    char deptCode[4];
} Student;

typedef struct Table
{
    int index;
    struct Student *student;
} Table;

// Function Prototypes
Table *hashTable(Table *, int);
Table *rehashTable(Table *, int, int);
Table *addStudent(Table *, int, int *, float *);
void searchStudent(Table *, int, int, char[]);
void printTable(Table *, int);
bool isPrime(int);

int main()
{
    Table *table = (Table *)malloc(sizeof(Table));
    int stopProcess = 0, size = 11;
    int addOption, option;
    float loadFactor = 0.0;
    char id[4];

    table = hashTable(table, size); // Hash Table creation with the given size
    do
    {
        printf("Select an open addressing technique:\n1) Double Hashing\n2) Quadratic Probing\n");
        scanf("%d", &addOption);
        getchar(); // To get rid of the new line character
        if (addOption != 1 && addOption != 2)
        {
            printf("Invalid option! Please re-enter.\n");
            addOption = -1;
        }
    } while (addOption == -1);
    do
    {
        printf(
            "\nSelect a functionality:\n1) Add a student\n2) Search for a student using ID\n3) Print Table\n4) Exit\n");
        scanf("%d", &option);
        getchar(); // To get rid of the new line character
        switch (option)
        {
        case 1:
            // I sent the address of size to addStudent function so that printTable function will work correctly in case
            // of rehashing. Also, I do the same thing to loadFactor function as well so that it will calculate the load
            // factor of the table without being affected by each function(addStudent) call
            table = addStudent(table, addOption, &size, &loadFactor);
            break;
        case 2:
            printf("Enter unique identifier: ");
            gets(id);
            searchStudent(table, addOption, size, id);
            break;
        case 3:
            printTable(table, size);
            break;
        case 4:
            stopProcess = 1; // Terminating the process
            break;
        default:
            printf("Invalid option! Please re-enter.\n");
        }
    } while (!stopProcess);
    return 0;
}

// Creating the hash table with the given size
Table *hashTable(Table *table, int size)
{
    table = (Table *)realloc(table, size * (sizeof(Table)));
    int i;
    if (table == NULL)
    {
        printf("Cannot allocate more memory.\n");
        exit(1);
    }
    else
    {
        for (i = 0; i < size; i++)
        {
            table[i].index = i;
            table[i].student = NULL;
        }
    }
    return table;
}

// Rehashing the hash table with the given size
Table *rehashTable(Table *table, int size, int oldSize)
{
    int i;
    Table *newTable = (Table *)malloc(size * sizeof(Table));
    if (newTable == NULL)
    {
        printf("Cannot allocate initial memory.\n");
        exit(1);
    }
    else
    {
        for (i = 0; i < oldSize; i++)
        {
            newTable[i].index = table[i].index;
            if (table[i].student != NULL)
            {
                newTable[i].student = (Student *)malloc(sizeof(Student));
                newTable[i].student[0] = table[i].student[0];
            }
            else
            {
                newTable[i].student = NULL;
            }
        }
        for (i = oldSize; i < size; i++)
        {
            newTable[i].index = i;
            newTable[i].student = NULL;
        }
    }
    return newTable;
}

// Displaying the hash table
void printTable(Table *table, int size)
{
    int i;
    printf("%-10s%-10s%-25s%s\n", "Index", "ID", "Name", "Department");
    for (i = 0; i < size; i++)
    {
        if (table[i].student == NULL)
        {
            printf("%d", table[i].index);
        }
        else
        {
            printf("%-10d%s%-7s%s%12s%s", table[i].index, table[i].student[0].studentID, "", table[i].student[0].name,
                   "", table[i].student[0].deptCode);
        }
        printf("\n");
    }
}

// Adding a student to the hash table based on the student's id
Table *addStudent(Table *table, int addOption, int *size, float *loadFactor)
{
    Student student;
    char id[10], name[100], dept[10];
    int i = 0, oldSize = *size;
    int key, h1, h2, index;

    do
    {
        printf("Enter unique identifier: ");
        gets(id);
        if (strlen(id) > 3)
        {
            printf("Invalid id length! Please re-enter.\n");
        }

    } while (strlen(id) > 3);

    // To check whether the id entered is already registered or not
    for (i = 0; i < *size; i++)
    {
        if (table[i].student != NULL)
        {
            if (strcmp(table[i].student[0].studentID, id) == 0)
            {
                printf("Id should be unique!\n");
                return table;
            }
        }
    }

    do
    {
        printf("Enter unique name: ");
        gets(name);
        if (strlen(name) > 40)
        {
            printf("Invalid name length! Please re-enter.\n");
        }
    } while (strlen(name) > 40);

    do
    {
        printf("Enter unique department: ");
        gets(dept);
        if (strlen(dept) > 3)
        {
            printf("Invalid department code length! Please re-enter.\n");
        }
    } while (strlen(dept) > 3);

    strcpy(student.studentID, id);
    strcpy(student.name, name);
    strcpy(student.deptCode, dept);

    // Appliying the formula to find the key value
    key = (int)(student.studentID[0]) - 65 + ((int)student.studentID[1] - '0') + ((int)student.studentID[2] - '0');

    // Hash functions
    h1 = 2 * key;
    h2 = 7 - (key % 7);
    i = 0;

    // Double Hashing
    if (addOption == 1)
    {
        do
        {
            index = (h1 + i * h2) % *size; // Double hashing formula
            if (table[index].student != NULL)
            {
                i++;
            }
        } while (table[index].student != NULL);
    }

    // Quadratic Probing
    if (addOption == 2)
    {
        do
        {
            index = (h1 + i * i) % *size; // Quadratic probing formula
            if (table[index].student != NULL)
            {
                i++;
            }
        } while (table[index].student != NULL);
    }
    table[index].student = (Student *)malloc(sizeof(Student));
    table[index].student[0] = student;
    printf("%s has been registered.\n", table[index].student[0].name);
    (*loadFactor)++;

    // If the load factor is greater than 0.5, rehashing will occur
    if ((*loadFactor) / (float)(*size) > 0.5)
    {
        *size *= 2;
        if (isPrime(*size) == true)
        {
            table = rehashTable(table, *size, oldSize);
        }
        else
        {
            // To find a prime number that is greater and closest to 2 times the table size
            do
            {
                (*size)++;
            } while (isPrime(*size) == false);
            table = rehashTable(table, *size, oldSize);
        }
    }

    return table;
}

// Searching a student with the student's id
void searchStudent(Table *table, int addOption, int size, char id[4])
{
    int key, h1, h2;
    int index, i = 0;
    // Appliying the formula to find the key value
    key = (int)(id[0]) - 65 + ((int)id[1] - '0') + ((int)id[2] - '0');

    // Hash functions
    h1 = 2 * key;
    h2 = 7 - (key % 7);

    // Double Hashing
    if (addOption == 1)
    {
        do
        {
            index = (h1 + i * h2) % size; // Double hashing formula
            if (table[index].student == NULL)
            {
                printf("Student is not found!\n");
            }
            else
            {
                if (strcmp(table[index].student[0].studentID, id) == 0)
                {
                    printf("Name: %s\n", table[index].student[0].name);
                    printf("Department: %s\n", table[index].student[0].deptCode);
                    break;
                }
                else
                {
                    i++;
                }
            }
        } while (table[index].student != NULL);
    }

    // Quadratic Probing
    if (addOption == 2)
    {
        do
        {
            index = (h1 + i * i) % size; // Quadratic probing formula
            if (table[index].student == NULL)
            {
                printf("Student is not found!\n");
            }
            else
            {
                if (strcmp(table[index].student[0].studentID, id) == 0)
                {
                    printf("Name: %s\n", table[index].student[0].name);
                    printf("Department: %s\n", table[index].student[0].deptCode);
                    break;
                }
                else
                {
                    i++;
                }
            }
        } while (table[index].student != NULL);
    }
}

// To check whether num is prime or not
// If num is prime, returns true, otherwise returns false
bool isPrime(int num)
{
    int i;
    for (i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}