#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9;

typedef struct Node
{
    int vertex;
    int dist;
    int prev;
} Node;

typedef struct Graph
{
    int size;
    Node *nodes;
    int **matrix;
} Graph;

Graph *createGraph(int X);
Graph *findShortestPath(Graph *G, int s);
void printShortestPath(Graph *G);

typedef struct Heap
{
    int capacity;
    int size;
    Node *elements;
} Heap;

Heap *createMinHeap(int X);
void insert(Heap *H, Node N);
Node deleteMin(Heap *H);
void decreaseKey(Heap *H, Node N);

int main(int argc, char *argv[])
{
    FILE *fi = fopen(argv[1], "r");
    int size;

    fscanf(fi, "%d", &size);

    Graph *G = createGraph(size);

    int node_s, node_d, weight;
    while (fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF)
    {
        G->matrix[node_s][node_d] = weight;
    }

    G = findShortestPath(G, 1);

    printShortestPath(G);

    return 0;
}

Graph *createGraph(int X)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->size = X;
    G->nodes = (Node *)malloc(sizeof(Node) * (X + 1));
    G->matrix = (int **)malloc(sizeof(int *) * (X + 1));

    for (int i = 1; i <= X; i++)
    {
        G->matrix[i] = (int *)malloc(sizeof(int) * (X + 1));
        for (int j = 1; j <= X; j++)
            G->matrix[i][j] = 0;
    }

    return G;
}

Graph *findShortestPath(Graph *G, int s)
{
    for (int i = 1; i <= G->size; i++)
    {
        G->nodes[i].vertex = i;
        G->nodes[i].prev = 0;
        G->nodes[i].dist = INF;
    }

    G->nodes[s].dist = 0;

    for (int i = 1; i <= G->size; i++)
    {
        if (G->matrix[s][i] != 0)
        {
            G->nodes[i].dist = G->matrix[s][i];
            G->nodes[i].prev = s;
        }
    }

    Heap *H = createMinHeap(G->size);

    for (int i = 1; i <= G->size; i++)
    {
        insert(H, G->nodes[i]);
    }

    while (H->size != 0)
    {
        Node u = deleteMin(H);
        for (int i = 1; i <= G->size; i++)
        {
            if (G->matrix[u.vertex][i] != 0)
            {
                if (u.dist + G->matrix[u.vertex][i] < G->nodes[i].dist)
                {
                    G->nodes[i].dist = u.dist + G->matrix[u.vertex][i];
                    G->nodes[i].prev = u.vertex;
                    decreaseKey(H, G->nodes[i]);
                }
            }
        }
    }

    return G;
}

void printShortestPath(Graph *G)
{
    for (int i = 2; i < G->size + 1; i++)
    {
        if (G->nodes[i].dist != INF)
        {
            printf("%d", i);
            int n = G->nodes[i].vertex;

            while (n != 1)
            {
                printf("<-%d", G->nodes[n].prev);
                n = G->nodes[n].prev;
            }
            printf(" cost: %d\n", G->nodes[i].dist);
        }
        else
        {
            printf("%d can not be reached.\n", i);
        }
    }
}

Heap *createMinHeap(int X)
{
    Heap *H = (Heap *)malloc(sizeof(Heap));
    H->capacity = X;
    H->size = 0;
    H->elements = (Node *)malloc(sizeof(Node) * (X + 1));

    for (int i = 0; i <= X; i++)
    {
        H->elements[i].vertex = 0;
        H->elements[i].dist = 0;
        H->elements[i].prev = 0;
    }

    return H;
}

void insert(Heap *H, Node N)
{
    int i;

    if (H->size >= H->capacity)
    {
        printf("Heap is full.\n");
        return;
    }

    for (i = ++H->size; H->elements[i / 2].dist > N.dist; i /= 2)
    {
        H->elements[i] = H->elements[i / 2];
    }

    H->elements[i] = N;
}

Node deleteMin(Heap *H)
{
    int i, child;
    Node MinElement = H->elements[1];
    Node LastElement = H->elements[H->size--];

    for (i = 1; i * 2 <= H->size; i = child)
    {
        child = i * 2;

        if (child != H->size && H->elements[child + 1].dist < H->elements[child].dist)
            child++;

        if (LastElement.dist > H->elements[child].dist)
            H->elements[i] = H->elements[child];
        else
            break;
    }

    H->elements[i] = LastElement;

    return MinElement;
}

void decreaseKey(Heap *H, Node N)
{
    int idx = N.vertex;

    while (idx > 0 && H->elements[(idx - 1) / 2].dist > N.dist)
    {
        H->elements[idx] = H->elements[(idx - 1) / 2];
        idx = (idx - 1) / 2;
    }

    H->elements[idx] = N;
}
