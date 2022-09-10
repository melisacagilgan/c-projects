# Email-Client

## Description
This assignment aims to help you practice linked list data structure and basic linked list operations. Your main task in this assignment is to write a C program to create a simple email client application that will allow you manage your emails. This application will include two separate lists for the emails you received and the emails you sent. For each email, it stores the following details: sender for the emails you received (max 50 characters) or recipient for the emails you sent (max 50 characters), date-time (Format: DD/MM/YYYY HH:MM), subject (max 50 characters) and content (max 200 characters). When you start the application, it will read your emails from external text files (inbox.txt and sent.txt), create two separate linked lists (one for the emails you received and another one for the emails you sent) and then populate these lists with the emails stored in those two text files. This application will then provide some operations for you to manage your emails. When you exit from the application, the application will overwrite the external files with the latest version of the lists to include the latest emails in your inbox and sent box. Therefore, this simple email application needs to support the following operations.

**Reading your emails from external files and initialising your email lists:** The application will start by reading the emails from external text files called inbox.txt and sent.txt. The inbox.txt file will include the details of the emails you received including unique id, sender, date-time, subject and content separated by a semicolon. Likewise, the sent.txt file will include the details of the emails you sent including unique id, recipient, date-time, subject and content separated by a semicolon. We assume that there is no semicolon in the subjects and contents of emails.
Example content for each file is shown below:

    inbox.txt
    1;sjacob@mail.co.uk;22/10/2018 14:11;Hi;How are you?
    2;brichard@mail.com;22/10/2018 15:15;Meeting;Hi there, Will we meet at 16:00?
    3;cthomas@xyz.com;23/10/2018 16:40;Book;Can I borrow your book for tomorrow?

    sent.txt
    1;cdaniel@mail.com;22/10/2018 15:55;Notes; Can you send me your lecture notes?
    2;jennifer@mail.co.uk;23/10/2018 16:45;Hello; Hi, how are you?
    3;cthomas@xyz.com;23/10/2018 16:45;Book; Yes you can

The application will then internally store these emails in two linked lists. Please note that you cannot make any assumptions about the number of emails sent/received and there is no upper limit for the number of emails. In your internal representation, you will need to decide about the structure of your linked list based on the txt files given above.

**Sending a new email:** After the initialisation of the application with the external files, you may want to send a new email. In this case, the application will ask you to enter the email address of the recipient, subject and content. In addition to these details, the application will take the date-time from the system and add the new email with all the details in the list of emails you sent. You can find the date-time from the system as follows:

    #include <stdio.h>
    #include <time.h>
    int main() {
    time_t ti = time(NULL);
    struct tm t = *localtime(&ti);
    printf("Date: %02d/%02d/%04d\n", t.tm_mday, t.tm_mon+1,
    t.tm_year+1900);
    printf("Time: %02d:%02d\n", t.tm_hour, t.tm_min);
    return 0;
    }

**Deleting an email:** This application will allow you to select a specific email by using its unique id from one of the lists and delete it.
**Printing your emails:** This application will allow you to print both of the lists.
**Searching for an email:** The application will allow you to search for an email by using the following details: sender or receipt and subject. You firstly need to select which list you will use for searching, then specify search criterion and search keys. More than one email can be listed after searching. You can make use of external libraries in C, such as string.h library.
**Overwriting the external files:** When the application is closed, the external files should be overwritten with the latest versions of the lists.

## Programming Requirements
When you write this application, you need to consider the data structure(s) that will be necessary. Clearly, two linked lists will be required: one for the list of emails you received and another one for the list of emails you sent. Therefore, it is recommended that you implement your basic linked list operations first (add/delete/search/print, etc). By using these basic operations on linked lists, you can implement other required operations. You also need to define and use a structure for datetime. To achieve the steps you need to have the following functions. Please strictly follow the requirements of the functions given below! In addition to these functions, you can write some helper/auxiliary functions.
<p align="center"><img src="https://i.ibb.co/RNC5SLb/image-2022-09-07-003239195.png"></p>
