#include "Header.h"

List CreateList(void) // Initialize the visitor list
{
    List l;

    l = (struct ListRecord *)malloc(sizeof(struct ListRecord));
    if (l == NULL)
    {
        printf("Out of memory!\n");
        return NULL;
    }
    else
    {
        MakeEmptyList(l);
        return l;
    }
}

void MakeEmptyList(List l)
{
    l->head = (struct Node *)malloc(sizeof(struct Node));
    if (l->head == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }

    l->head->next = NULL;
    l->tail = l->head;
    l->length = 0;
}

Robot CreateRobotList(void) // Initialize the struct robot
{
    Robot r;

    r = (struct RobotRecord *)malloc(sizeof(struct RobotRecord));
    if (r == NULL)
    {
        printf("Out of memory!\n");
        return NULL;
    }
    else
    {
        MakeEmptyRobotList(r);
        return r;
    }
}

void MakeEmptyRobotList(Robot r)
{
    r->head = (struct Robot *)malloc(sizeof(struct Robot));
    if (r->head == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }

    r->head->next = NULL;
    r->tail = r->head;
}

void InsertList(List l, char visitorType, int arrivalTime, int serviceTime, int serviceStartTime, int robotID,
                char bookISBN[]) // Creating a new visitor and adding to the list
{
    struct Node *temp, *p;

    temp = (struct Node *)malloc(sizeof(struct Node)); // Creating a new node
    if (temp == NULL)                                  // Error check
    {
        printf("Out of memory space\n");
    }
    else
    {
        temp->visitorType = visitorType;
        temp->arrivalTime = arrivalTime;
        temp->serviceTime = serviceTime;
        temp->serviceStartTime = serviceStartTime;
        temp->robotID = robotID;
        strcpy(temp->bookISBN, bookISBN);
        p = l->tail;

        while (p->next != NULL)
        {
            if (temp->arrivalTime < p->next->arrivalTime) // Enqueue according to arrival time
            {
                break;
            }
            else if (temp->arrivalTime ==
                     p->next->arrivalTime) // Enqueue according to priority when their arrival time are the same
            {
                if (temp->visitorType == 'M' || temp->visitorType == p->next->visitorType)
                {
                    break;
                }
                else if ((temp->visitorType == 'L' || temp->visitorType == 'S') && p->next->visitorType == 'M')
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
        temp->next = p->next;
        p->next = temp;
        l->length++;
    }
}

void ReinsertList(List l, struct Node *newVisitor) // Reinsert the visitor to the list
{
    newVisitor->next = NULL;
    l->tail->next = newVisitor;
    l->tail = l->tail->next;
    l->length++;
}

struct Node *DeleteList(List l) // Returns a visitor from the list
{
    struct Node *deletedNode;
    if (l->head->next != NULL)
    {
        deletedNode = l->head->next;
        if (deletedNode->next != NULL)
        {
            l->head->next = deletedNode->next;
        }
        else
        {
            l->head->next = NULL;
        }
    }
    l->length--;
    return deletedNode;
}

void DisplayList(List l) // This function is to see the list while writing the code
{
    struct Node *temp;
    temp = l->head->next;
    printf("Visitor Type\t    Arrival Time\tService Time\tService StartTime\tRobot ID\tBook ISBN\n");
    while (temp != NULL)
    {
        printf("----> %c\t\t\t%d\t\t     %d\t\t        %d\t\t    %d\t      %s\n", temp->visitorType, temp->arrivalTime,
               temp->serviceTime, temp->serviceStartTime, temp->robotID, temp->bookISBN);
        temp = temp->next;
    }
}
