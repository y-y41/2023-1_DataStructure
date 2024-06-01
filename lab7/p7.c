#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

struct AVLNode
{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Max(ElementType num1, ElementType num2);
int Height(Position P);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);

int main(int argc, char **argv)
{

    AVLTree myTree = NULL;
    int key;

    FILE *fi = fopen(argv[1], "r");
    while (fscanf(fi, "%d", &key) != EOF)
    {
        myTree = Insert(key, myTree);
        PrintInorder(myTree);
        printf("\n");
    }
    fclose(fi);

    DeleteTree(myTree);
    return 0;
}

int Max(ElementType num1, ElementType num2)
{
    if (num1 > num2)
        return num1;
    else
        return num2;
}

int Height(Position P)
{
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

Position SingleRotateWithLeft(Position node)
{
    Position newNode;

    newNode = node->Left;
    node->Left = newNode->Right;
    newNode->Right = node;

    node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
    newNode->Height = Max(Height(newNode->Left), node->Height) + 1;

    return newNode;
}

Position SingleRotateWithRight(Position node)
{
    Position newNode;

    newNode = node->Right;
    node->Right = newNode->Left;
    newNode->Left = node;

    node->Height = Max(Height(node->Right), Height(node->Left)) + 1;
    newNode->Height = Max(Height(newNode->Right), node->Height) + 1;

    return newNode;
}

Position DoubleRotateWithLeft(Position node)
{
    node->Left = SingleRotateWithRight(node->Left);

    return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node)
{
    node->Right = SingleRotateWithLeft(node->Right);

    return SingleRotateWithRight(node);
}

AVLTree Insert(ElementType X, AVLTree T)
{
    if (T == NULL)
    {
        T = malloc(sizeof(struct AVLNode));
        if (T != NULL)
        {
            T->Element = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if (X == T->Element)
    {
        printf("Insertion Error: %d already in the tree!\n", T->Element);
    }
    else if (X < T->Element)
    {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2)
        {
            if (X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    }
    else if (X > T->Element)
    {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2)
            if (X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
    }
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

void PrintInorder(AVLTree T)
{
    if (T != NULL)
    {
        PrintInorder(T->Left);
        printf("%d(%d) ", T->Element, T->Height);
        PrintInorder(T->Right);
    }
}
void DeleteTree(AVLTree T)
{
    if (T->Left != NULL)
        DeleteTree(T->Left);
    if (T->Right != NULL)
        DeleteTree(T->Right);
    free(T);
}
