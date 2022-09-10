#include "Header.h"

/*This function initialises the queue*/
Queue CreateQueue(void)
{
    Queue q;

    q = (struct QueueRecord *)malloc(sizeof(struct QueueRecord));
    if (q == NULL) // Error check
    {
        printf("Out of memory space\n");
    }
    else
    {
        MakeEmptyQueue(q);
        return q;
    }
}

/*This function sets the queue size to 0, and creates a dummy element
and sets the front and rear point to this dummy element*/
void MakeEmptyQueue(Queue q)
{
    q->size = 0;
    q->front = (struct Node *)malloc(sizeof(struct Node));
    if (q->front == NULL) // Error check
    {
        printf("Out of memory space\n");
    }
    else
    {
        q->front->next = NULL;
        q->rear = q->front;
    }
}

void Enqueue(Queue q, struct Node *newVisitor) // Adding new visitor to the queue
{
    struct Node *p;
    if (q->front->next == NULL)
    {
        q->front->next = newVisitor;
        q->rear = q->rear->next;
        q->rear->next = NULL;
        q->size++;
    }
    else
    {
        p = q->front;
        while (p->next != NULL)
        {
            if (newVisitor->arrivalTime < p->next->arrivalTime) // Enqueue according to arrival time
            {
                break;
            }
            else if (newVisitor->arrivalTime ==
                     p->next->arrivalTime) // Enqueue according to priority when their arrival time are the same
            {
                if (newVisitor->visitorType == 'M' || newVisitor->visitorType == p->next->visitorType)
                {
                    break;
                }
                else if ((newVisitor->visitorType == 'L' || newVisitor->visitorType == 'S') &&
                         p->next->visitorType == 'M')
                {
                    p = p->next;
                    break;
                }
            }
            else
            {
                p = p->next;
            }
        }
        newVisitor->next = p->next;
        p->next = newVisitor;
        q->size++;
    }
}

struct Node *Dequeue(Queue q) // Deleting a node in the front of the queue
{
    struct Node *temp, *deletedNode;

    temp = q->front;
    deletedNode = temp->next;

    temp->next = deletedNode->next;

    q->size--;

    return deletedNode;
}

/*Shows if the queue is empty*/
int IsEmptyQueue(Queue q)
{
    return (q->size == 0);
}

/*Returns the queue size*/
int QueueSize(Queue q)
{
    return (q->size);
}

/*Returns the value stored in the front of the queue*/
int FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
    {
        return q->front->next->arrivalTime;
    }
    else
    {
        return -1;
    }
}

/*Returns the value stored in the rear of the queue*/
int RearOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
    {
        return q->rear->arrivalTime;
    }
    else
    {
        return -1;
    }
}

/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    struct Node *temp;

    temp = q->front->next;
    printf("Queue\n");
    printf("Visitor Type\t    Arrival Time\tService Time\tService StartTime\tRobot ID\tBook ISBN\n");
    while (temp != NULL)
    {
        printf("----> %c\t\t\t%d\t\t     %d\t\t        %d\t\t    %d\t      %s\n", temp->visitorType, temp->arrivalTime,
               temp->serviceTime, temp->serviceStartTime, temp->robotID, temp->bookISBN);
        temp = temp->next;
    }
}
