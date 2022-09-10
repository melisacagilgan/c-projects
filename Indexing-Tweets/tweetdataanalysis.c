#include "avltree.h"

int main()
{
    AVLTree myTree, popularHashtag;
    int option, index;
    char *file_name = "tweets.txt";

    myTree = read_tweet_data(file_name); /*read_tweet_data functions returns the tree. myTree is my tree structure*/

    printf("\n>>>Welcome to Hashtag Analysis at Twitter<<<\n\n");
    do
    {
        printf("  --Menu--\n  1. Display the hashtag index\n  2. Display the most trending hashtag\n  3. Exit\n");
        printf("\nOption:");
        scanf("%d", &option);
        while (option < 1 || option > 3) /*Option error check*/
        {
            printf("Invalid option! Please enter again!\n");
            printf("\nOption:");
            scanf("%d", &option);
        }
        if (option == 1)
        {
            display_index(myTree); /*Displays all the hashtags in the tree*/
            printf("\n\n");
        }
        if (option == 2)
        {
            printf("\nThe most trending hashtag\n-------------------------\n");
            popularHashtag = display_the_most_trending_hashtag(myTree); /*Prints the most popular hashtag in the tree*/
            printf("%-18s\t(Tweets:", popularHashtag->hashtag);
            for (index = 0; index < popularHashtag->indexCount; index++)
            {
                if (popularHashtag->indexCount - 1 != index)
                {
                    printf("%d,", popularHashtag->index[index]);
                }
                else
                {
                    printf("%d", popularHashtag->index[index]);
                }
            }
            printf(")\n");
            treeTraversal(
                myTree, popularHashtag->hashtag,
                popularHashtag->indexCount); /*Prints the other popular hashtags in the tree if there is more than one*/
            printf("\n\n");
        }
        if (option == 3)
        {
            printf("\nBye!\n");
            break;
        }
    } while (option != 3); /*Exit*/

    return 0;
}
