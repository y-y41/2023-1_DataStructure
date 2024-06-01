#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    int *key;
    int top;
    int max_stack_size;
} Stack;

Stack *CreateStack(int max);
void Push(Stack *s, int x);
int Pop(Stack *s);
int Top(Stack *s);
void DeleteStack(Stack *s);
int IsEmpty(Stack *s);
int IsFull(Stack *s);
void Postfix(Stack *s, char input_str);

void main(int argc, char *argv[])
{

    FILE *fi = fopen(argv[1], "r");

    Stack *stack = CreateStack(10);

    char c;
    printf("Top numbers: ");
    while (1)
    {
        fscanf(fi, "%c", &c);
        if (c == '#')
            break;

        Postfix(stack, c);
        printf("%d ", Top(stack));
    }
    printf("\n");
    printf("evaluation result: %d\n", Pop(stack));

    fclose(fi);
    DeleteStack(stack);
}

Stack *CreateStack(int max)
{
    Stack *s = malloc(sizeof(struct Stack));

    s->key = malloc(sizeof(int) * max);
    s->top = -1;
    s->max_stack_size = max;

    return s;
}

void Push(Stack *s, int x)
{
    if (IsFull(s))
        printf("Full Stack");
    else
        s->key[++s->top] = x;
}

int Pop(Stack *s)
{
    if (IsEmpty(s))
    {
        printf("Empty Stack");
        return 0;
    }
    else
    {
        return s->key[s->top--];
    }
}

int Top(Stack *s)
{
    if (!IsEmpty(s))
        return s->key[s->top];
    return 0;
}

void DeleteStack(Stack *s)
{
    while (!IsEmpty(s))
        Pop(s);
    free(s->key);
    free(s);
}

int IsEmpty(Stack *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

int IsFull(Stack *s)
{
    if (s->top + 1 >= s->max_stack_size)
        return 1;
    else
        return 0;
}

void Postfix(Stack *s, char input_str)
{
    int a, b;
    switch (input_str) {
        case '+':
            b = Pop(s);
            a = Pop(s);
            Push(s, a + b);
            break;
        case '-':
            b = Pop(s);
            a = Pop(s);
            Push(s, a - b);
            break;
        case '*':
            b = Pop(s);
            a = Pop(s);
            Push(s, a * b);
            break;
        case '/':
            b = Pop(s);
            a = Pop(s);
            Push(s, a / b);
            break;
        case '%':
            b = Pop(s);
            a = Pop(s);
            Push(s, a % b);
            break;
        default:
	        a = input_str - '0';
            Push(s, a);
    }
}
