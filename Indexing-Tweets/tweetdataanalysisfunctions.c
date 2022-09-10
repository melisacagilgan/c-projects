#include "avltree.h"

char *lowerCase(char *hashtag) /*To make sure that Cprogramming and cprogramming hashtags are considered as the same, I
                                  made all hashtag letters lower*/
{
    int index;
    for (index = 0; index < strlen(hashtag); index++)
    {
        hashtag[index] = tolower(hashtag[index]);
    }
    return hashtag;
}

AVLTree read_tweet_data(char *file_name)
{
    AVLTree t;
    FILE *tweets;
    int indexString, indexTemp, indexTweet = 0;
    char *stringTweet = (char *)malloc(281 * sizeof(char));
    if (stringTweet == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }

    t = CreateTree(); /*Creating a tree*/
    t = MakeEmptyTree(t);

    tweets = fopen(file_name, "r");

    if (tweets == NULL) /*Program exits if file pointer returns NULL*/
    {
        printf("Error! The file cannot open!\n");
        exit(1);
    }

    while (!feof(tweets))
    {
        fgets(stringTweet, 280, tweets); /*To read the each line as string*/
        indexTweet++;                    /*Each reading adds 1 to indexTweet and it creates the index of each tweet*/
        indexString =
            0; /*To read the "stringTweet" array from the beginning. stringTweet represents the tweets in rows*/
        while (stringTweet[indexString]) /*Exits from the loop when stringTweet[indexString] is equal to NULL*/
        {
            indexTemp =
                0; /*To read tempHashtag from the beginning. tempHashtag represents the hashtags of stringTweet*/
            if (stringTweet[indexString] == '#') /*If there is "#" character, there has to be a hashtag*/
            {
                char *tempHashtag = (char *)malloc(
                    281 *
                    sizeof(char)); /*I defined tempHashtag here because for each hashtag, I need an empty string array*/
                if (tempHashtag == NULL) /*Program exits if tempHashtag pointer returns NULL.*/
                {
                    printf("Out of memory!\n");
                    exit(1);
                }
                indexString++;
                /* "isalpha" is not equal to 0 means all the characters are alphabetical.
                    "ispunct" is equal to zero means there is no punctuation mark
                    "isspace" is equal to zero means there is no space kind of characters*/
                while (isalpha(stringTweet[indexString]) != 0 && ispunct(stringTweet[indexString]) == 0 &&
                       isspace(stringTweet[indexString]) == 0)
                {
                    tempHashtag[indexTemp++] =
                        stringTweet[indexString]; /*To copy the found hashtag(character by character) to a temporary
                                                     string(tempHashtag)*/
                    indexString++;
                    if (!(isalpha(stringTweet[indexString]) != 0 && ispunct(stringTweet[indexString]) == 0 &&
                          isspace(stringTweet[indexString]) == 0))
                    {
                        tempHashtag[indexTemp] = '\0'; /*To make the last character of tempHashtag is NULL*/
                    }
                }

                tempHashtag = lowerCase(tempHashtag);
                t = insert_hashtag(t, tempHashtag, indexTweet); /*Hashtag insertion to the tree*/
            }
            indexString++;
        }
    }
    fclose(tweets); /*Closing the file*/
    return t;
}

AVLTree insert_hashtag(AVLTree t, char *hashtag, int indexTweet)
{
    int index = 0;
    if (t == NULL) /*If t is empty, it creates a new node*/
    {
        t = (struct Tree *)malloc(sizeof(struct Tree));
        if (t == NULL)
        {
            printf("Out of memory space!\n");
        }
        else
        {
            t->hashtag = (char *)malloc((1 + strlen(hashtag)) * sizeof(char));
            strcpy(t->hashtag, hashtag);
            t->index = (int *)malloc(sizeof(int));
            t->index[0] = indexTweet;
            t->height = 0;
            t->indexCount = 1;
            t->left = t->right = NULL;
        }
    }
    else if (strcmp(hashtag, t->hashtag) < 0) /*If hashtag is shorter than t->hashtag, go to left*/
    {
        t->left = insert_hashtag(t->left, hashtag, indexTweet);
        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) ==
            2) /*If the balancing factor is more than one, tree should be balanced*/
        {
            if (strcmp(hashtag, t->left->hashtag) < 0) /*The problem is left-left, single rotation*/
            {
                t = SingleRotateWithLeft(t);
            }
            else /*The problem is left-right, double rotation*/
            {
                t = DoubleRotateWithLeft(t);
            }
        }
    }
    else if (strcmp(hashtag, t->hashtag) > 0) /*If hashtag is longer than t->hashtag, go to right*/
    {
        t->right = insert_hashtag(t->right, hashtag, indexTweet);
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) ==
            2) /*If the balancing factor is more than one, tree should be balanced*/
        {
            if (strcmp(hashtag, t->right->hashtag) > 0) /*The problem is right-right, single rotation*/
            {
                t = SingleRotateWithRight(t);
            }
            else /*The problem is right-left, double rotation*/
            {
                t = DoubleRotateWithRight(t);
            }
        }
    }
    else /*If hashtag and t>hashtag are the same, add the new tweet index to the integer array of hashtag indexes*/
    {
        t->index = (int *)realloc(t->index, (t->indexCount + 1) *
                                                sizeof(int)); /*To extend the integer array of hashtag indexes by 1*/
        t->index[t->indexCount] = indexTweet;                 /*To add the new hashtag index to the integer array*/
        t->indexCount++;                                      /*To increase the number of indexes by 1*/
    }
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1; /*To define the tree height*/
    return t;
}

void display_index(AVLTree t) /*Recursive display function in-order.*/
{
    int index;
    static int check = 0; /*Using static prevents to reset the check value*/
    if (check == 0)
    {
        printf("\nHashtag Index\n-------------\n");
    }
    if (t != NULL)
    {
        check++; /*To print the string "hashtag index" only once, I increase the check value by 1 continuously*/
        display_index(t->left);
        printf("%-18s\t(Tweets: ", t->hashtag);
        for (index = 0; index < t->indexCount; index++)
        {
            if (t->indexCount - 1 != index)
            {
                printf("%d,", t->index[index]);
            }
            else
            {
                printf("%d", t->index[index]);
            }
        }
        printf(")\n");
        display_index(t->right);
    }
}

AVLTree display_the_most_trending_hashtag(
    AVLTree t) /*This function is to recursively find the highest indexCount value in the tree*/
{
    /*Since the tree is unsorted with respect to indexCount(number of indexes that a hashtag has), We need to check all
     * the datas in the tree to be sure that we found the maximum value.*/
    /*To make it faster, we should have insert all the datas according to indexCount*/
    /*Complexity of finding the most trending hashtag is O(n), but if we use an avl tree sorted according to indexCount,
     * this complexity would be O(logn)*/
    AVLTree rootLeftMax = t, rootRightMax = t;
    AVLTree leftMax, rightMax;

    if (t == NULL)
    {
        return t;
    }
    else
    {
        if (t->left != NULL)
        {
            leftMax = display_the_most_trending_hashtag(t->left);
            if (rootLeftMax->indexCount < leftMax->indexCount)
            {
                rootLeftMax = leftMax;
            }
        }

        if (t->right != NULL)
        {
            rightMax = display_the_most_trending_hashtag(t->right);
            if (rootRightMax->indexCount < rightMax->indexCount)
            {
                rootRightMax = rightMax;
            }
        }
    }
    return rootLeftMax->indexCount > rootRightMax->indexCount
               ? rootLeftMax
               : rootRightMax; /*If rootLeftMax->indexCount > rootRightMax->indexCount, returns rootLeftMax, otherwise
                                  rootRightMax*/
}

void treeTraversal(AVLTree t, char *hashtag,
                   int indexCount) /*It is a simple tree traversal. This function is to show the other popular hashtags
                                      and their indexes if there is more than one. If not, it won't do anything */
{
    int index;
    if (t != NULL) /*It simply traverses the tree and if there are more popular hashtags, It prints them*/
    {
        if (t->indexCount == indexCount && strcmp(t->hashtag, hashtag) != 0)
        {
            printf("%-18s\t(Tweets:", t->hashtag);
            for (index = 0; index < t->indexCount; index++)
            {
                if (t->indexCount - 1 != index)
                {
                    printf("%d,", t->index[index]);
                }
                else
                {
                    printf("%d", t->index[index]);
                }
            }
            printf(")\n");
        }
        if (t->left != NULL)
        {
            treeTraversal(t->left, hashtag, indexCount);
        }
        if (t->right != NULL)
        {
            treeTraversal(t->right, hashtag, indexCount);
        }
    }
}
