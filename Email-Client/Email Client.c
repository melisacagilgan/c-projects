#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct dateTime
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
};

struct Email
{
    int number;
    char name[51];
    struct dateTime dt;
    char subject[51];
    char content[201];
    struct Email *next;
};

struct myList
{
    struct Email *head;
    struct Email *tail;
    int size;
};

typedef struct myList *List;

// Function Prototypes

List initialiseInbox(void);
List initialiseSent(void);
List sendEmail(List, char *, char *, char *);
List deleteInboxEmail(List, int);
List deleteSentEmail(List, int);
void printEmails(List, List);
void searchEmail(List, List);
void overwrite(List, List);
void overwrite(List, List);

int main()
{
    int id, check, length;
    char option, recipient[UCHAR_MAX], subject[UCHAR_MAX], content[UCHAR_MAX];
    struct Email *temp;
    List inboxList, sentList;

    inboxList = initialiseInbox();
    sentList = initialiseSent();

    printf("\n\nWelcome to Your Email Client!\n");
    printf("Your inbox and sent box have been loaded successfully.");
    do
    {
        printf("\n\n--- MENU ---\n\n");
        printf("1. Send an email\n2. Delete an email from your inbox\n3. Delete an email for your sent box\n4. See "
               "your emails\n5. Search for an email\n6. Exit\n\n");
        printf("Option:");
        fflush(stdin);
        scanf("%c", &option);

        switch (option)
        {
        case '1':
            fflush(stdin);
            printf("\n");
            do
            {
                printf("Recipient:");
                gets(recipient);
                length = strlen(recipient);
                if (length > 50)
                {
                    printf("Recipient name should be maximum 50 character! Please enter again.\n\n");
                }
            } while (length > 50);
            do
            {
                printf("Subject:");
                gets(subject);
                length = strlen(subject);
                if (length > 50)
                {
                    printf("Subject should be maximum 50 character! Please enter again.\n\n");
                }
            } while (length > 50);
            do
            {
                printf("Content:");
                gets(content);
                length = strlen(content);
                if (length > 200)
                {
                    printf("Content should be maximum 200 character! Please enter again.\n\n");
                }
            } while (length > 200);
            sentList = sendEmail(sentList, recipient, subject, content);
            printf("Your email has been sent successfully.\n");
            break;
        case '2':
            printf("Email ID:");
            scanf("%d", &id);
            check = 0; // To check whether the id is valid or not
            for (temp = inboxList->head; temp != NULL; temp = temp->next)
            {
                if (temp->number == id)
                {
                    check = 1;
                }
            }
            if (check == 0)
            {
                printf("No email with ID %d in your inbox!", id); // Error message
            }
            if (check == 1)
            {
                inboxList = deleteInboxEmail(inboxList, id);
                printf("Email with ID %d has been deleted from your inbox.", id);
            }
            break;
        case '3':
            printf("Email ID:");
            scanf("%d", &id);
            check = 0; // To check whether the id is valid or not
            for (temp = sentList->head; temp != NULL; temp = temp->next)
            {
                if (temp->number == id)
                {
                    check = 1;
                }
            }
            if (check == 0)
            {
                printf("No email with ID %d in your sentbox!", id); // Error message
            }
            else
            {
                sentList = deleteSentEmail(sentList, id);
                printf("Email with ID %d has been deleted from your sent box.", id);
            }
            break;
        case '4':
            printEmails(inboxList, sentList);
            break;
        case '5':
            searchEmail(inboxList, sentList);
            break;
        case '6':
            printf("\nBye!");
            break;
        default:
            printf("Wrong option!\n"); // Error message
            break;
        }
        overwrite(inboxList, sentList); // To write the linked lists to the file again
    } while (option != '6');
    return 0;
}

List initialiseInbox(void)
{
    int count;
    int inbox_line = 1;
    char ch, inboxFile_name[20] = "inbox.txt";
    FILE *inboxFile = fopen(inboxFile_name, "r");

    List inboxList = (struct myList *)malloc(sizeof(struct myList)); // Creating List

    inboxList->head = (struct Email *)malloc(sizeof(struct Email));

    inboxList->head->next = NULL; // Creating a dummy node
    inboxList->tail = inboxList->head;
    inboxList->size = 0;

    if (inboxFile == NULL)
    {
        printf("We cannot open your inbox!\n");
        exit(1);
    }
    else
    {
        for (count = 0; fscanf(inboxFile, "%c", &ch) != EOF; count++) // Inbox file line counter
        {
            if (ch == '\n')
            {
                inbox_line++;
            }
        }

        rewind(inboxFile); // Taking cursor to the beginning

        for (count = 0; count < inbox_line; count++) // Reading inbox from the file
        {
            inboxList->tail->next = (struct Email *)malloc(sizeof(struct Email)); // Allocating memory for the new node
            fscanf(inboxFile, "%d;%[^;];%d/%d/%d %d:%d;%[^;];%[^\n]", &inboxList->tail->number, inboxList->tail->name,
                   &inboxList->tail->dt.day, &inboxList->tail->dt.month, &inboxList->tail->dt.year,
                   &inboxList->tail->dt.hour, &inboxList->tail->dt.minute, inboxList->tail->subject,
                   inboxList->tail->content);
            inboxList->size++;
            if ((count + 1) != inbox_line)
            {
                inboxList->tail = inboxList->tail->next;
            }
        }

        inboxList->tail->next = NULL;

        fclose(inboxFile);

        return inboxList;
    }
}

List initialiseSent(void)
{

    int count;
    int sent_line = 1;
    char ch, sentFile_name[20] = "sent.txt";
    FILE *sentFile = fopen(sentFile_name, "r");

    List sentList = (struct myList *)malloc(sizeof(struct myList)); // Creating List

    sentList->head = (struct Email *)malloc(sizeof(struct Email));

    sentList->head->next = NULL; // Creating a dummy node
    sentList->tail = sentList->head;
    sentList->size = 0;

    if (sentFile == NULL)
    {
        printf("We cannot open your sentbox!\n");
        exit(1);
    }
    else
    {
        for (count = 0; fscanf(sentFile, "%c", &ch) != EOF; count++) // Sent file line counter
        {
            if (ch == '\n')
            {
                sent_line++;
            }
        }

        rewind(sentFile); // Taking cursor to the beginning

        for (count = 0; count < sent_line; count++)
        {
            sentList->tail->next = (struct Email *)malloc(sizeof(struct Email));
            fscanf(sentFile, "%d;%[^;];%d/%d/%d %d:%d;%[^;];%[^\n]", &sentList->tail->number, sentList->tail->name,
                   &sentList->tail->dt.day, &sentList->tail->dt.month, &sentList->tail->dt.year,
                   &sentList->tail->dt.hour, &sentList->tail->dt.minute, sentList->tail->subject,
                   sentList->tail->content);
            sentList->size++;
            if ((count + 1) != sent_line)
            {
                sentList->tail = sentList->tail->next;
            }
        }

        sentList->tail->next = NULL;

        fclose(sentFile);

        return sentList;
    }
}

List sendEmail(List sentList, char *recipient, char *subject, char *content)
{
    int index = 0;
    struct dateTime dt;
    struct Email *temp = (struct Email *)malloc(sizeof(struct Email)); // Temporary node

    time_t ti = time(NULL); // To find the current time
    struct tm t = *localtime(&ti);
    temp->dt.day = t.tm_mday; // Filling the new node
    temp->dt.month = t.tm_mon + 1;
    temp->dt.year = t.tm_year + 1900;
    temp->dt.hour = t.tm_hour;
    temp->dt.minute = t.tm_min;

    strcpy(temp->name, recipient);
    strcpy(temp->subject, subject);
    strcpy(temp->content, content);

    if (sentList->head == NULL) // Adding a node to the empty linked list
    {
        sentList->size++;
        temp->number = sentList->size;

        sentList->head = sentList->tail;

        sentList->tail = temp;
        sentList->tail->next = NULL;
    }
    else
    {
        sentList->size++;
        temp->number = sentList->size;

        sentList->tail->next = temp;
        sentList->tail = sentList->tail->next;
        sentList->tail->next = NULL;
    }

    return sentList;
}

List deleteInboxEmail(List inboxList, int id)
{
    struct Email *temp, *p;
    temp = inboxList->head;
    if (temp->next == NULL) // Deleting the last remaining node
    {
        free(inboxList->head);
        inboxList->head = NULL;
    }
    else
    {
        if (temp->number == id) // Deleting the first node
        {
            p = temp->next;
            inboxList->head = p;

            free(temp);
        }
        else
        {
            while (temp->next->number != id)
            {
                temp = temp->next;
            }
            p = temp->next->next;
            temp->next = p;
        }
    }

    return inboxList;
}

List deleteSentEmail(List sentList, int id)
{
    struct Email *temp, *p;

    if (sentList->head->next == NULL) // Deleting the last remaining node
    {
        free(sentList->head);
        sentList->head = NULL;
    }
    else
    {
        temp = sentList->head;
        if (temp->number == id) // Deleting the first node
        {
            p = temp->next;
            sentList->head = p;

            free(temp);
        }
        else
        {
            while (temp->next->number != id)
            {
                temp = temp->next;
            }
            p = temp->next->next;
            temp->next = p;
        }
    }

    return sentList;
}

void printEmails(List inboxList, List sentList)
{
    struct Email *temp;
    // Printing the inbox
    printf("\n\nYour Inbox:\n");
    if ((temp = inboxList->head) == NULL)
    {
        printf("\tYour inbox is empty!\n");
    }
    else
    {
        for (temp = inboxList->head; temp != NULL; temp = temp->next)
        {
            printf("%d\t%s\t%d/%d/%d\t%d:%d\t%s\t%s\n", temp->number, temp->name, temp->dt.day, temp->dt.month,
                   temp->dt.year, temp->dt.hour, temp->dt.minute, temp->subject, temp->content);
        }
    }
    // Printing the sent box
    printf("\nYour Sent Box:\n");
    if ((temp = sentList->head) == NULL)
    {
        printf("\tYour sent box is empty!\n");
    }
    else
    {
        for (temp = sentList->head; temp != NULL; temp = temp->next)
        {
            printf("%d\t%s\t%d/%d/%d\t%d:%d\t%s\t%s\n", temp->number, temp->name, temp->dt.day, temp->dt.month,
                   temp->dt.year, temp->dt.hour, temp->dt.minute, temp->subject, temp->content);
        }
    }
}

void searchEmail(List inboxList, List sentList)
{
    struct Email *temp;
    int choice1, choice2, length;
    char recipient[UCHAR_MAX], subject[UCHAR_MAX], *found;
    printf("\nInbox (1) or Sent box (2):");
    scanf("%d", &choice1);
    printf("Recipient (1) or Subject (2):");
    scanf("%d", &choice2);
    if (choice1 == 1)
    {
        temp = inboxList->head;
        if (choice2 == 1)
        {
            fflush(stdin);

            do
            {
                printf("Recipient:");
                gets(recipient);
                length = strlen(recipient);
                if (length > 50)
                {
                    printf("Recipient name should be maximum 50 character! Please enter again.\n\n");
                }
            } while (length > 50);

            while (temp != NULL)
            {
                found = strstr(temp->name, recipient); // To find the substring(recipient) of "temp->name"
                if (found != NULL)
                {
                    printf("%d\t%s\t%d/%d/%d\t%d:%d\t%s\t%s\n", temp->number, temp->name, temp->dt.day, temp->dt.month,
                           temp->dt.year, temp->dt.hour, temp->dt.minute, temp->subject, temp->content);
                    break;
                }
                else
                {
                    temp = temp->next;
                }
            }

            if (found == NULL)
            {
                printf("There is no such an email!\n");
            }
        }
        if (choice2 == 2)
        {
            fflush(stdin);

            do
            {
                printf("Subject:");
                gets(subject);
                length = strlen(subject);
                if (length > 50)
                {
                    printf("Subject should be maximum 50 character! Please enter again.\n\n");
                }
            } while (length > 50);

            while (temp != NULL)
            {
                found = strstr(temp->subject, subject); // To find the substring(subject) of "temp->name"
                if (found != NULL)
                {
                    printf("%d\t%s\t%d/%d/%d\t%d:%d\t%s\t%s\n", temp->number, temp->name, temp->dt.day, temp->dt.month,
                           temp->dt.year, temp->dt.hour, temp->dt.minute, temp->subject, temp->content);
                    break;
                }
                else
                {
                    temp = temp->next;
                }
            }

            if (found == NULL)
            {
                printf("There is no such an email!\n");
            }
        }
    }
    if (choice1 == 2)
    {
        temp = sentList->head;
        if (choice2 == 1)
        {
            fflush(stdin);

            do
            {
                printf("Recipient:");
                gets(recipient);
                length = strlen(recipient);
                if (length > 50)
                {
                    printf("Recipient name should be maximum 50 character! Please enter again.\n\n");
                }
            } while (length > 50);

            while (temp != NULL)
            {
                found = strstr(temp->name, recipient); // To find the substring(recipient) of "temp->name"
                if (found != NULL)
                {
                    printf("%d\t%s\t%d/%d/%d\t%d:%d\t%s\t%s\n", temp->number, temp->name, temp->dt.day, temp->dt.month,
                           temp->dt.year, temp->dt.hour, temp->dt.minute, temp->subject, temp->content);
                    break;
                }
                else
                {
                    temp = temp->next;
                }
            }

            if (found == NULL)
            {
                printf("There is no such an email!\n");
            }
        }
        if (choice2 == 2)
        {
            fflush(stdin);

            do
            {
                printf("Subject:");
                gets(subject);
                length = strlen(subject);
                if (length > 50)
                {
                    printf("Subject should be maximum 50 character! Please enter again.\n\n");
                }
            } while (length > 50);

            while (temp != NULL)
            {
                found = strstr(temp->subject, subject); // To find the substring(subject) of "temp->name"
                if (found != NULL)
                {
                    printf("%d\t%s\t%d/%d/%d\t%d:%d\t%s\t%s\n", temp->number, temp->name, temp->dt.day, temp->dt.month,
                           temp->dt.year, temp->dt.hour, temp->dt.minute, temp->subject, temp->content);
                    break;
                }
                else
                {
                    temp = temp->next;
                }
            }
            if (found == NULL)
            {
                printf("There is no such an email!\n");
            }
        }
    }
}

void overwrite(List inboxList, List sentList)
{
    char inboxFile_name[20] = "inbox.txt", sentFile_name[20] = "sent.txt";

    FILE *inboxFile = fopen(inboxFile_name, "w");
    FILE *sentFile = fopen(sentFile_name, "w");

    struct Email *inbox, *sent;

    if (sentFile == NULL || inboxFile == NULL)
    {
        printf("We cannot open your inbox or sentbox!\n");
        exit(1);
    }
    else
    {
        inbox = inboxList->head;
        sent = sentList->head;

        while (inbox != NULL)
        {
            fprintf(inboxFile, "%d;%s;%d/%d/%d %d:%d;%s;%s\n", inbox->number, inbox->name, inbox->dt.day,
                    inbox->dt.month, inbox->dt.year, inbox->dt.hour, inbox->dt.minute, inbox->subject, inbox->content);
            inbox = inbox->next;
        }
        while (sent != NULL)
        {
            fprintf(sentFile, "%d;%s;%d/%d/%d %d:%d;%s;%s\n", sent->number, sent->name, sent->dt.day, sent->dt.month,
                    sent->dt.year, sent->dt.hour, sent->dt.minute, sent->subject, sent->content);
            sent = sent->next;
        }

        fclose(inboxFile);
        fclose(sentFile);
    }
}
