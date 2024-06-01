#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue
{
    int size;
    int *key;
    int front;
    int rear;
} Queue;

Queue *CreateQueue(int X);
void Enqueue(Queue *Q, int item);
int Dequeue(Queue *Q);

typedef struct _Graph
{
    int size;
    int *vertex;
    int **edge;
} Graph;

Graph *CreateGraph(int X);
void InsertEdge(Graph *G, int u, int v);
void Topsort(Graph *G);

int main(int argc, char *argv[])
{
    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);

    Graph *G = CreateGraph(X);

    for (int i = 0; i < X; i++)
    {
        fscanf(fi, "%d", &G->vertex[i]);
    }

    while (fscanf(fi, "%d %d", &u, &v) != EOF)
    {
        InsertEdge(G, u, v);
    }

    Topsort(G);

    return 0;
}

Queue *CreateQueue(int X)
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->size = X;
    Q->key = (int *)malloc(sizeof(int) * X);
    Q->front = 0;
    Q->rear = -1;

    return Q;
}

void Enqueue(Queue *Q, int item)
{
    Q->key[++Q->rear] = item;
}

int Dequeue(Queue *Q)
{
    Q->size--;
    int item = Q->key[Q->front++];

    return item;
}

Graph *CreateGraph(int X)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->size = X;
    G->vertex = (int *)malloc(sizeof(int) * X);
    G->edge = (int **)malloc(sizeof(int *) * X);

    for (int i = 0; i < X; i++)
    {
        G->edge[i] = (int *)malloc(sizeof(int) * X);
        for (int j = 0; j < X; j++)
            G->edge[i][j] = 0;
    }

    return G;
}

void InsertEdge(Graph *G, int u, int v)
{
    int r = -1;
    int c = -1;
    for (int i = 0; i < G->size; i++)
    {
        if (G->vertex[i] == u)
            r = i;
        else if (G->vertex[i] == v)
            c = i;
    }

    if (r != -1 && c != -1)
        G->edge[r][c] = 1;
}

void Topsort(Graph *G)
{
    int *indegree = (int *)malloc(sizeof(int) * G->size);

    for (int i = 0; i < G->size; i++)
        indegree[i] = 0;

    for (int i = 0; i < G->size; i++)
    {
        for (int j = 0; j < G->size; j++)
        {
            if (G->edge[i][j] == 1)
                indegree[j]++;
        }
    }

    Queue *Q = CreateQueue(G->size);
    int v, r;

    for (int i = 0; i < G->size; i++)
    {
        if (indegree[i] == 0)
            Enqueue(Q, G->vertex[i]);
    }
    
    while (Q->size != 0)
    {
        v = Dequeue(Q);
        printf("%d ", v);

        for (int i = 0; i < G->size; i++)
        {
            if (G->vertex[i] == v)
                r = i;
        }

        for (int i = 0; i < G->size; i++)
        {
            if (G->edge[r][i] == 1)
            {
                if (--indegree[i] == 0)
                    Enqueue(Q, G->vertex[i]);
            }
        }
    }
    printf("\n");

    free(indegree);
    free(Q->key);
    free(Q);
}
