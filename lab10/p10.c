#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet
{
    int size;
    int *ptr_arr; // parent
} DisjointSets;

typedef struct _PrintDisjointSet
{
    int size;
    int *ptr_arr; // wall
} PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets *maze, int n);
int find(DisjointSets *sets, int x);
void union_(DisjointSets *sets, int i, int j);
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n);
void printMaze(PrintDisjointSets *maze, int n);
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze);

int main(int argc, char *argv[])
{
    int num;
    FILE *fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &num);
    fclose(fi);

    DisjointSets *sets;
    PrintDisjointSets *maze;

    sets = (DisjointSets *)malloc(sizeof(DisjointSets));
    maze = (PrintDisjointSets *)malloc(sizeof(PrintDisjointSets));

    init(sets, maze, num);

    createMaze(sets, maze, num);

    printMaze(maze, num);

    freeMaze(sets, maze);

    return 0;
}

void init(DisjointSets *sets, PrintDisjointSets *maze, int n)
{
    sets->size = n * n + 1;
    sets->ptr_arr = (int *)malloc(sets->size * sizeof(int));

    maze->size = 2 * n * (n - 1);
    maze->ptr_arr = (int *)malloc(maze->size * sizeof(int));

    for (int i = 0; i < sets->size; i++)
        sets->ptr_arr[i] = 0;

    for (int i = 0; i < maze->size; i++)
    {
        if (i == n || i == maze->size - 1)
            maze->ptr_arr[i] = 0;
        else
            maze->ptr_arr[i] = 1;
    }
}

int find(DisjointSets *sets, int x)
{
    if (sets->ptr_arr[x] <= 0)
        return x;
    else
        return find(sets, sets->ptr_arr[x]);
}

void union_(DisjointSets *sets, int i, int j)
{
    int r_i = find(sets, i);
    int r_j = find(sets, j);

    if (r_i == r_j)
        return;

    if (sets->ptr_arr[r_j] < sets->ptr_arr[r_i])
        sets->ptr_arr[r_i] = r_j;
    else
    {
        if (sets->ptr_arr[r_j] == sets->ptr_arr[r_i])
            sets->ptr_arr[r_i]--;
        sets->ptr_arr[r_j] = r_i;
    }
}

void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n)
{
    srand(time(NULL));
    int firstCell, secondCell;

    while (find(sets, 1) != find(sets, sets->size - 1))
    {
        int randomWall = rand() % (maze->size);

        if (randomWall % (2 * n - 1) < n - 1)
        { // vertical
            firstCell = randomWall / (2 * n - 1) * n + randomWall % (2 * n - 1) + 1;
            secondCell = firstCell + 1;
        }
        else
        { // horizontal
            firstCell = randomWall / (2 * n - 1) * n + randomWall % (2 * n - 1) - n + 2;
            secondCell = firstCell + n;
        }

        int r_first = find(sets, firstCell);
        int r_second = find(sets, secondCell);

        if (r_first != r_second)
        {
            union_(sets, r_first, r_second);
            maze->ptr_arr[randomWall] = 0;
        }
    }
}
void printMaze(PrintDisjointSets *maze, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" - ");
    }
    printf("\n");

    int j;
    for (int i = 0; i < maze->size; i += 2 * n - 1)
    {
        if (i == 0)
            printf("   ");
        else
            printf("|  ");

        for (j = i; j < i + n - 1; j++)
        {
            if (maze->ptr_arr[j] == 1)
                printf("|  ");
            else
                printf("   ");
        }
        if (j == maze->size) {
            printf("\n");
            break;
        }
        else printf("|\n");

        for (; j < i + 2 * n - 1; j++)
        {
            if (maze->ptr_arr[j] == 1)
                printf(" - ");
            else
                printf("   ");
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++)
    {
        printf(" - ");
    }
    printf("\n");
}
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze)
{
    free(sets->ptr_arr);
    free(sets);
    free(maze->ptr_arr);
    free(maze);
}