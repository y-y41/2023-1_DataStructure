#include <stdio.h>
#include <stdlib.h>

struct MergeSort
{
    int Capacity;
    int Size;
    int *array;
    int *Tmparray;
};

typedef struct MergeSort *MergeSort;

MergeSort make_list(int size);
void Insert(MergeSort m, int a);
void printArray(MergeSort A, int l, int r);
void RmergeSort(MergeSort A, int l, int r);
void ImergeSort(MergeSort A, int n);
void merge(MergeSort A, int l, int m, int r);

void main(int argc, char *argv[])
{
    int size, key;
    int *iter_tmp, *rec_tmp;
    FILE *fi = fopen(argv[1], "r");
    MergeSort iter_m, rec_m;

    fscanf(fi, "%d", &size);

    iter_m = make_list(size);
    rec_m = make_list(size);

    for (int i = 0; i < size; i++)
    {
        fscanf(fi, "%d", &key);
        Insert(iter_m, key);
        Insert(rec_m, key);
    }

    printf("input : \n");
    printArray(iter_m, 0, iter_m->Size - 1);
    printf("\n");

    printf("iterative : \n");
    ImergeSort(iter_m, iter_m->Size - 1);
    printf("\n");

    printf("recursive : \n");
    RmergeSort(rec_m, 0, rec_m->Size - 1);
    printf("\n");
}

MergeSort make_list(int size)
{
    MergeSort merge = (MergeSort)malloc(sizeof(struct MergeSort));
    merge->Capacity = size;
    merge->Size = 0;
    merge->array = (int *)malloc(sizeof(int) * size);
    merge->Tmparray = (int *)malloc(sizeof(int) * size);
    return merge;
}

void Insert(MergeSort m, int a)
{
    m->array[m->Size] = a;
    m->Size++;
}

void printArray(MergeSort A, int l, int r)
{
    for (int i = l; i <= r; i++)
    {
        printf("%d ", A->array[i]);
    }
    printf("\n");
}

void RmergeSort(MergeSort A, int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) / 2;
    RmergeSort(A, l, mid);
    RmergeSort(A, mid + 1, r);
    merge(A, l, mid, r);
}

void ImergeSort(MergeSort A, int n)
{
    int size, l;
    for (size = 1; size <= n; size = 2 * size)
    {
        for (l = 0; l < n; l += 2 * size)
        {
            int m = l + size - 1;
            int r = (l + 2 * size - 1 < n) ? l + 2 * size - 1 : n;
            merge(A, l, m, r);
        }
    }
}

void merge(MergeSort A, int l, int m, int r)
{
    int LeftEnd, RightEnd, Lpos, Rpos, mid, i;
    Lpos = LeftEnd = l;
    RightEnd = r;
    mid = m;
    Rpos = m + 1;

    while (Lpos <= mid && Rpos <= RightEnd)
    {
        if (A->array[Lpos] <= A->array[Rpos])
            A->Tmparray[LeftEnd++] = A->array[Lpos++];
        else
            A->Tmparray[LeftEnd++] = A->array[Rpos++];
    }

    while (Lpos <= mid)
        A->Tmparray[LeftEnd++] = A->array[Lpos++];
    while (Rpos <= RightEnd)
        A->Tmparray[LeftEnd++] = A->array[Rpos++];

    for (i = l; i <= r; i++, RightEnd--)
        A->array[RightEnd] = A->Tmparray[RightEnd];

    printArray(A, l, r);
}