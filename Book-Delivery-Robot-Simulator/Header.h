#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

/*A Node declaration to store a value, pointer to the next node and a priority value*/
struct Node
{
    char visitorType; // Also the priority
    int arrivalTime;
    int serviceTime;
    int serviceStartTime;
    int robotID;
    char bookISBN[13];
    struct Node *next;
};

struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int length;
};

struct Robot // Instead of keeping integer array for robots, I kept struct Robot
{
    int ID;
    int notAvailabilityTime; // The remaining total busy time is greater than zero. Available is equal to zero.
    int usage;
    struct Robot *next;
};

struct RobotRecord
{
    struct Robot *head;
    struct Robot *tail;
};

/*Queue Record that will store the following:
  size: total number of elements stored in the list
  front: it shows the front node of the queue (front of the queue)
  rear: it shows the rare node of the queue (rear of the queue)*/
struct QueueRecord
{
    struct Node *front; /* pointer to front of queue */
    struct Node *rear;  /* pointer to rear of queue */
    int size;           /* number of items in queue */
};

typedef struct QueueRecord *Queue;
typedef struct ListRecord *List;
typedef struct RobotRecord *Robot;

/*Linked List functions*/
List CreateList(void);
void MakeEmptyList(List);
Robot CreateRobotList(void);
void MakeEmptyRobotList(Robot);
void InsertList(List, char, int, int, int, int, char *);
void ReinsertList(List, struct Node *);
struct Node *DeleteList(List);
void DisplayList(List);
void DisplayRobotList(Robot);

/*Queue functions*/
Queue CreateQueue(void);
void MakeEmptyQueue(Queue);
void Enqueue(Queue, struct Node *);
struct Node *Dequeue(Queue);
int QueueSize(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);

/*Robot Simulator Functions*/
void parseInput(char **, int *, int *, int *, int *);
List createVisitorList(List, int, int, int, int, char **);
Queue initialiseSimulatorQueue(Queue);
Robot initialiseSimulatorRobots(Robot, int);
void newVisitor(List, Queue, char **, int *);
struct Robot *earliestAvailability(Robot r);
int serveVisitor(List, Queue, Robot, int, int *, int *);
void reportStatistics(List, Robot, int, int, int, int *, char **, int, int);
int highestIndex(int *);
