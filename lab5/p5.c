#include <stdio.h>
#include <stdlib.h>

struct CircularQueueStruct
{
    int *key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

typedef struct CircularQueueStruct *CircularQueue;

CircularQueue MakeEmpty(int max);
int IsEmpty(CircularQueue Q);
int IsFull(CircularQueue Q);
void Dequeue(CircularQueue Q);
void Enqueue(CircularQueue Q, int X);
void PrintFirst(CircularQueue Q);
void PrintRear(CircularQueue Q);
void DeleteQueue(CircularQueue Q);

void main(int argc, char *argv[])
{
    char command;
    FILE *input;
    CircularQueue queue;
    int queueSize;
    int tmpNum;

    input = fopen(argv[1], "r");
    // queue = MakeEmpty(queueSize);

    while (1)
    {
        command = fgetc(input);
        if (feof(input))
            break;
        switch (command)
        {
        case 'n':
            fscanf(input, "%d", &queueSize);
            queue = MakeEmpty(queueSize);
            break;
        case 'e':
            fscanf(input, "%d", &tmpNum);
            Enqueue(queue, tmpNum);
            break;
        case 'd':
            Dequeue(queue);
            break;
        case 'f':
            PrintFirst(queue);
            break;
        case 'r':
            PrintRear(queue);
            break;
        default:
            break;
        }
    }
    DeleteQueue(queue);
}

CircularQueue MakeEmpty(int max)
{
    CircularQueue queue = malloc(sizeof(struct CircularQueueStruct));
    queue->key = malloc(sizeof(int) * max);
    queue->first = 0;
    queue->rear = -1;
    queue->max_queue_size = max;
    queue->qsize = 0;

    return queue;
}

int IsEmpty(CircularQueue Q)
{
    if (Q->qsize == 0)
        return 1;
    else
        return 0;
}

int IsFull(CircularQueue Q)
{
    if (Q->qsize == Q->max_queue_size)
        return 1;
    else
        return 0;
}
void Dequeue(CircularQueue Q) {
    if (IsEmpty(Q)) {
        printf("Dequeue failed: Queue is Empty!\n");
    }
    else {
        printf("Dequeue %d\n", Q->key[Q->first]);
        Q->first = (Q->first + 1) % Q->max_queue_size;
        Q->qsize--;
    }
}
void Enqueue(CircularQueue Q, int X) {
    if (IsFull(Q)) {
        printf("Enqueue failed: Queue is Full!\n");
    }
    else {
        printf("Enqueue %d\n", X);
        Q->qsize++;
        Q->rear = (Q->rear + 1) % Q->max_queue_size;
        Q->key[Q->rear] = X;
    }
}
void PrintFirst(CircularQueue Q) {
    if (IsEmpty(Q))
        printf("Queue is Empty!\n");
    else
        printf("First: %d\n", Q->key[Q->first]);
}
void PrintRear(CircularQueue Q) {
    if (IsEmpty(Q))
        printf("Queue is Empty!\n");
    else
        printf("Rear: %d\n", Q->key[Q->rear]);
}
void DeleteQueue(CircularQueue Q) {
    free(Q->key);
    free(Q);
}
