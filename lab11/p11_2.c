#include <stdio.h>
#include <stdlib.h>

struct QuickSort
{
    int Capacity;
    int Size;
    int *array;
};

typedef struct QuickSort *QuickSort;

QuickSort make_list(int size);
void Insert(QuickSort q, int a);
void printArray(QuickSort q);
void swap(int *a, int *b);
int middle_partition(QuickSort q, int low, int high);
int leftmost_partition(QuickSort q, int left, int right);
int rightmost_partition(QuickSort q, int left, int right);
void quicksort(QuickSort q, int left, int right, int type);

void main(int argc, char *argv[])
{
    char type_s[10];
    int list_size, key, type_i;
    QuickSort q;
    FILE *fi = fopen(argv[1], "r");

    fscanf(fi, "%s", &type_s);
    if (!(strcmp(type_s, "leftmost")))
        type_i = 0;
    else if (!(strcmp(type_s, "rightmost")))
        type_i = 1;
    else if (!(strcmp(type_s, "middle")))
        type_i = 2;

    fscanf(fi, "%d", &list_size);
    q = make_list(list_size);
    for (int i = 0; i < list_size; i++)
    {
        fscanf(fi, "%d", &key);
        Insert(q, key);
    }

    quicksort(q, 0, list_size - 1, type_i);

    free(q->array);
    free(q);
}

QuickSort make_list(int size)
{
    QuickSort q = malloc(sizeof(struct QuickSort));
    q->Capacity = size;
    q->Size = 0;
    q->array = (int *)malloc(size * sizeof(int));
    return q;
}

void Insert(QuickSort q, int a)
{
    q->array[q->Size++] = a;
}

void printArray(QuickSort q)
{
    printf("result : ");
    for (int i = 0; i < q->Size; i++)
        printf("%d ", q->array[i]);
    printf("\n");
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int middle_partition(QuickSort q, int low, int high)
{
    int mid = (low + high) / 2;
    int pivot = q->array[mid];
    printf("pivot value: %d\n", pivot);
    int i = low;
    int j = high;

    while (i <= j)
    {
        while (i <= j && q->array[i] < pivot)
            i++;
        while (i <= j && q->array[j] >= pivot)
            j--;
        if (i <= j)
        {
            if (i == mid)
                mid = j;
            else if (j == mid)
                mid = i;
            swap(&q->array[i], &q->array[j]);
            i++; j--;
        }
    }
    swap(&q->array[i], &q->array[mid]);
    printArray(q);
    return i;
}

int leftmost_partition(QuickSort q, int left, int right)
{
    int pivot = q->array[left];
    printf("pivot value: %d\n", pivot);
    int i = left + 1;
    int j = right;
    while (1)
    {
        while (i <= right && q->array[i] <= pivot)
            i++;
        while (j > left && q->array[j] > pivot)
            j--;
        if (i >= j)
            break;
        swap(&q->array[i], &q->array[j]);
    }
    swap(&q->array[left], &q->array[j]);
    printArray(q);
    return j;
}

int rightmost_partition(QuickSort q, int left, int right)
{
    int pivot = q->array[right];
    printf("pivot value: %d\n", pivot);
    int i = left;
    int j = right - 1;
    while (1)
    {
        while (i <= right && q->array[i] < pivot)
            i++;
        while (j >= left && q->array[j] >= pivot)
            j--;
        if (i >= j)
            break;
        swap(&q->array[i], &q->array[j]);
    }
    swap(&q->array[right], &q->array[i]);
    printArray(q);
    return i;
}

void quicksort(QuickSort q, int left, int right, int type)
{
    if (left >= right)
        return;
    int p;
    if (type == 0)
        p = leftmost_partition(q, left, right);
    else if (type == 1)
        p = rightmost_partition(q, left, right);
    else if (type == 2)
        p = middle_partition(q, left, right);

    quicksort(q, left, p - 1, type);
    quicksort(q, p + 1, right, type);
}