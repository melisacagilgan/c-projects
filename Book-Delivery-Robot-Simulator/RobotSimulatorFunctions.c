#include "Header.h"

void parseInput(char **argv, int *noOfVisitors, int *noOfRobots, int *maxArrivalTime, int *maxServiceTime)
{
    *noOfVisitors = atoi(argv[1]);
    *noOfRobots = atoi(argv[2]);
    *maxArrivalTime = atoi(argv[3]);
    *maxServiceTime = atoi(argv[4]);
}

List createVisitorList(List l, int noOfVisitors, int noOfRobots, int maxArrivalTime, int maxServiceTime,
                       char **ISBN) // Initializing the visitor list
{
    char priorityArray[3] = {"MLS"};
    char priority;
    int arrivalTime;
    int serviceTime;
    int serviceStartTime = 0;
    int robotID = 0;
    int index, count;
    l = CreateList();
    for (count = 0; count < noOfVisitors; count++)
    {
        index = rand() % 3;
        priority = priorityArray[index];
        arrivalTime = rand() % (maxArrivalTime) + 1;
        serviceTime = rand() % (maxServiceTime) + 1;
        index = rand() % 10;
        InsertList(l, priority, arrivalTime, serviceTime, serviceStartTime, robotID, ISBN[index]);
    }
    return l;
}

Queue initialiseSimulatorQueue(Queue q) // Initializing the queue
{
    q = CreateQueue();
    return q;
}

Robot initialiseSimulatorRobots(Robot r, int noOfRobots) // Initializing the simulator robots
{
    int count;
    r = CreateRobotList();
    for (count = 0; count < noOfRobots; count++)
    {
        r->tail->next = (struct Robot *)malloc(sizeof(struct Robot));
        if (r->tail->next == NULL)
        {
            printf("Out of memory!");
            exit(1);
        }
        else
        {

            r->tail = r->tail->next;
            r->tail->ID = count + 1;
            r->tail->notAvailabilityTime = 0;
            r->tail->usage = 0;
            if ((count + 1) == noOfRobots)
            {
                r->tail->next = NULL;
            }
        }
    }
    return r;
}

void newVisitor(List l, Queue q, char **ISBN, int intISBN[])
{
    struct Node *newVisitor;
    int index;
    while (l->head->next != NULL)
    {
        newVisitor = DeleteList(l);
        index = indexOf(newVisitor->bookISBN, ISBN); // Finding the most popular book index
        intISBN[index]++;
        Enqueue(q, newVisitor);
    }
}

int indexOf(char *bookISBN, char **ISBN) // If there is the same amount of usage of book, it gives randomly one of them.
{
    int index;
    for (index = 0; index < 10; index++)
    {
        if (!strcmp(bookISBN, *(ISBN + index)))
        {
            return index;
        }
    }
}

struct Robot *earliestAvailability(Robot r) // To find the robot which has a closest availability time
{
    struct Robot *temp, *p;
    temp = r->head->next;
    int min = temp->notAvailabilityTime;
    p = temp;

    while (temp->next != NULL)
    {
        temp = temp->next;
        if (temp->notAvailabilityTime < min)
        {
            min = temp->notAvailabilityTime;
            p = temp;
        }
    }
    return p;
}

int serveVisitor(List l, Queue q, Robot r, int clock, int *maxTime, int *totalTime)
{
    struct Node *newVisitor;
    struct Robot *temp, *p;
    int waitingTime = 0;
    int count = 0;
    temp = r->head->next;
    while (temp != NULL) // Checking the availability of the robots and assigning them to the first coming visitors. I
                         // didn't check if the queue is empty or not in this line because in case of processing the
                         // last visitors, the queue would be empty. The empty queue check is done at a later point
    {
        if (temp->notAvailabilityTime <=
            0) // The robot will be free a minute later when its job is completed. If the arrival time is at 10 and the
               // service time is 5, this robot will take the next visitor at minute 16.
        {
            if (FrontOfQueue(q) <= clock && FrontOfQueue(q) != -1) // I checked whether the queue is empty or not.
            {
                newVisitor = Dequeue(q);
                newVisitor->serviceStartTime = clock;
                temp->notAvailabilityTime = newVisitor->serviceTime;
                newVisitor->robotID = temp->ID;
                waitingTime = clock - newVisitor->arrivalTime; // To find the waiting time in the queue
                if (waitingTime > *maxTime)
                {
                    *maxTime = waitingTime; // To find the max waiting time in the queue
                }
                *totalTime += waitingTime;   // To find the total waiting time in the queue
                ReinsertList(l, newVisitor); // Addind the visitor back to the list
                temp->usage++;
            }
        }
        else
        {
            temp->notAvailabilityTime =
                temp->notAvailabilityTime - 1; // Counting back from the availability time. If the service time is 7, it
                                               // will count back from the 7 to 0. When it is 0, it will be available.
            if (temp->notAvailabilityTime <= 0)
            {
                count++;
            }
        }
        temp = temp->next;
    }

    return count;
}

void reportStatistics(List l, Robot r, int noOfVisitors, int noOfRobots, int clock, int *intISBN, char **ISBN,
                      int maxTime, int totalTime) // Report of the simulator
{
    struct Robot *temp;
    struct Node *p;
    int count = 1;
    temp = r->head->next;
    printf("\n\t---Final Report---\n");
    printf("How many robots served the visitors? %d\n", noOfRobots);
    printf("How many visitors were served? %d\n", noOfVisitors);
    printf("How many visitors were served by each robot?\n");
    while (temp != NULL)
    {
        printf("\t%d. Robot served %d times\n", count, temp->usage);
        count++;
        temp = temp->next;
    }
    printf("How long did it take to complete the simulation? %d\n", clock);
    printf("The average waiting time %.2f\n",
           (totalTime * 1.0 / noOfVisitors * 1.0)); // totalTime and noOfVisitors are integers that is why I multiplied
                                                    // them by 1.0 because the returning value type is float.
    printf("The maximum waiting time %d\n", maxTime);
    printf("The most popular book is %s\n\n", ISBN[highestIndex(intISBN)]);
}

int highestIndex(int intISBN[]) // To find the most popular book
{
    int highestIndex = 0, counter;
    for (counter = 1; counter < 10; counter++)
    {
        if (intISBN[highestIndex] < intISBN[counter])
        {
            highestIndex = counter;
        }
    }
    return highestIndex;
}
