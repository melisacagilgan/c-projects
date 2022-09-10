#include "avltree.h"

AVLTree CreateTree(void) /*Creating an empty tree*/
{
    return NULL;
}

AVLTree MakeEmptyTree(AVLTree t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

int AVLTreeHeight(AVLTree t) /*Tree height*/
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}

AVLTree SingleRotateWithLeft(AVLTree k2) /*(Single)Rotation for the symmetric cases (Right-Right)*/
{
    AVLTree k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;

    return k1;
}

AVLTree SingleRotateWithRight(AVLTree k1) /*(Single)Rotation for the symmetric cases (Left-Left)*/
{
    AVLTree k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;

    return k2;
}

AVLTree DoubleRotateWithLeft(AVLTree k3) /*(Double)Rotation for the asymmetric cases (Left-Right)*/
{
    k3->left = SingleRotateWithRight(k3->left);
    k3 = SingleRotateWithLeft(k3);
    return k3;
}

AVLTree DoubleRotateWithRight(AVLTree k3) /*(Double)Rotation for the asymmetric cases (Right-Left)*/
{
    k3->right = SingleRotateWithLeft(k3->right);
    k3 = SingleRotateWithRight(k3);
    return k3;
}

int Max(int x, int y) /*This function is to decide the height of the Tree. It compares the left and right subtrees'
                         heights and decide the maximum(deeper) of these*/
{
    if (x >= y)
        return x;
    else
        return y;
}
