#include <stdio.h>
#include <stdlib.h>

void stack_construct(struct stack* pstk, int init_capacity);
bool push(struct stack* pstk, int el);
int pop(struct stack* pstk);
void stack_destruct(struct stack* pstk);
void print_stack(struct stack* pstk);
void add(struct stack* pstk);
size_t hash_func(void* data, int size_of_data);
bool stack_check(struct stack* pstk);

const int CANARY = 0x888888;


struct stack
{
    size_t canary1 = CANARY;
    int* data;
    int size;
    int capacity;
    size_t hash_old;
    size_t canary2 = CANARY;
};


// [(1,2,2),2,1,1,2,1,(k1,2,1,2,2,k2),1,2]


int main()
{
    struct stack st = {};
    stack_construct(&st, 5);
    push(&st, 1);
    push(&st, 2);
    push(&st, 3);
    push(&st, 4);
    push(&st, 5);
    push(&st, 6);
    print_stack(&st);
    add(&st);
    print_stack(&st);
    printf("%d\n", pop(&st));
    printf("%d\n", pop(&st));
    printf("%d\n", pop(&st));
    printf("%d\n", pop(&st));
    printf("%d\n", pop(&st));
    print_stack(&st);
    stack_destruct(&st);
}

void stack_construct(struct stack* pstk, int init_capacity)
{
    pstk->data = (int*) calloc(init_capacity, sizeof(int));
    pstk->capacity = init_capacity;
    pstk->size = 0;
}

void print_stack(struct stack* pstk)
{
    if (pstk->size == 0)
    {
        printf("stack is empty\n");
        return;
    }

    for (int i = 0; i < pstk->size; i++)
        printf("%d ", *(pstk->data + i));
    printf("\n");
}

bool push(struct stack* pstk, int el)
{
    if (pstk->size == pstk->capacity)
    {
        int* tmp = 0;
        if (!(tmp = (int*) realloc(pstk->data, 2 * pstk->capacity * sizeof(int))))
        {
            printf("%d\n", 2 * pstk->capacity * sizeof(int));
            printf("problem in realloc\n");
            return false;
        }
        pstk->capacity = pstk->capacity * 2;
        pstk->data = tmp;
    }
    *(pstk->data + pstk->size) = el;
    pstk->size++;
    return true;
}

int pop(struct stack* pstk)
{
    if (pstk->size == 0)
    {
        printf("stack is empty\n");
        return -374560234;
    }

    pstk->size--;
    return *(pstk->data + pstk->size);
}

void add(struct stack* pstk)
{
    if(!stack_check(pstk))
    {
        printf("stack was broken\n");
        return;
    }

    if (pstk->size <= 1)
    {
        printf("not enough numbers\n");
    }

    pstk->data[pstk->size - 2] += pstk->data[pstk->size - 1];
    pstk->size--;
}


void stack_destruct(struct stack* pstk)
{
    if (pstk->data == NULL)
    {
        printf("stack do not exist\n");
        return;
    }

    free(pstk->data);
    pstk->data = NULL;
    pstk->capacity = 0;
    pstk->size = 0;
}

bool stack_check(struct stack* pstk)
{
    if(pstk->canary1 == CANARY && pstk->canary2 == CANARY)
        return true;
    return false;
}

size_t hash_func(void* data, int size_of_data)
{
}
