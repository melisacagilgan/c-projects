#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct Tree *AVLTree;

/*Tree structure decleration*/

struct Tree
{
    char *hashtag;  /*To keep an hashtag from a tweet*/
    int *index;     /*It keeps all tweets' indexex that the relative hashtag includes*/
    int indexCount; /*It keeps the number of tweets' indexex that the relative hashtag includes*/
    AVLTree left;
    AVLTree right;
    int height; /*Tree height(depth)*/
};

// Function Prototypes of AVL Tree

AVLTree CreateTree(void);
AVLTree MakeEmptyTree(AVLTree);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
int AVLTreeHeight(AVLTree);
int Max(int, int);

// Function Prototypes of Tweet Data Analysis

char *lowerCase(char *);
AVLTree read_tweet_data(char *);
AVLTree insert_hashtag(AVLTree, char *, int);
void display_index(AVLTree);
AVLTree display_the_most_trending_hashtag(AVLTree);
void treeTraversal(AVLTree, char *, int);
