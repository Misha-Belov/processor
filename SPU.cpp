#include "ass.h"

int main()
{
    int counter = 0;
    struct SPU proc = {};

    SPU_construct(&proc);
    proc.array_command = fill_array(proc.array_command, &(proc.array_size));

    for(;;)
    {
        switch(proc.array_command[counter])
        {
            case push:
            {
                f_push(&proc.st, proc.array_command[counter + 1]);
                counter++;
                break;
            }
            case push_r:
            {
                f_push_r(&proc.st, &proc.reg, proc.array_command[counter + 1]);
                counter++;
                break;
            }
            case add:
            {
                f_add(&proc.st);
                break;
            }
            case sub:
            {
                f_sub(&proc.st);
                break;
            }
            case dif:
            {
                f_dif(&proc.st);
                break;
            }
            case mul:
            {
                f_mul(&proc.st);
                break;
            }
            case out:
            {
                f_out(&proc.st, &proc.reg);
                break;
            }
            case in:
            {
                f_in(&proc.st);
                break;
            }
            case pop_r:
            {
                f_pop(&proc.st, &proc.reg, proc.array_command[counter + 1]);
                counter++;
                break;
            }
            case hlt:
            {
                return 0;
                break;
            }
            default:
            {
                return 0;
                break;
            }
        }

        counter++;
    }
}

void SPU_construct(struct SPU* proc)
{
    proc->st.data = (int*) calloc(INIT_CAPACITY, sizeof(int));
    proc->st.capacity = INIT_CAPACITY;
    proc->st.size = 0;

    proc->reg.rax = 0;
    proc->reg.rbx = 0;
    proc->reg.rcx = 0;
    proc->reg.rdx = 0;

    proc->array_command = (int*) calloc(INIT_ARRAY, sizeof(int));
    proc->array_size = INIT_ARRAY;
}

int* fill_array(int* array, int* size)
{
    FILE* instr = fopen("digit.txt", "r");

    int value = 0, i = 0;

    while (fscanf(instr, "%d", &value) != EOF)
    {
        if(i == *size - 1)
        {
            *size = *size * 2;
            array = (int*) realloc(array, 2 * *size * sizeof(int));
        }

        array[i] = value;
        i++;
    }
    return array;
}

void f_push(struct stack* pstk, int value)
{
    if (pstk->size == pstk->capacity)
    {
        int* tmp = 0;
        if (!(tmp = (int*) realloc(pstk->data, 2 * pstk->capacity * sizeof(int))))
        {
            printf("%d\n", 2 * pstk->capacity * sizeof(int));
            printf("problem in realloc\n");
        }
        pstk->capacity = pstk->capacity * 2;
        pstk->data = tmp;
    }
    *(pstk->data + pstk->size) = value;
    pstk->size++;
}

void f_push_r(struct stack* pstk, struct registrs* preg, int registr)
{
    if (pstk->size == pstk->capacity)
    {
        int* tmp = 0;
        if (!(tmp = (int*) realloc(pstk->data, 2 * pstk->capacity * sizeof(int))))
        {
            printf("%d\n", 2 * pstk->capacity * sizeof(int));
            printf("problem in realloc\n");
        }
        pstk->capacity = pstk->capacity * 2;
        pstk->data = tmp;
    }
    switch (registr)
    {
        case 1:
            *(pstk->data + pstk->size) = preg->rax;
            break;
        case 2:
            *(pstk->data + pstk->size) = preg->rbx;
            break;
        case 3:
            *(pstk->data + pstk->size) = preg->rcx;
            break;
        case 4:
            *(pstk->data + pstk->size) = preg->rdx;
            break;
        default:
            printf("wrong registr");
            break;
    }

    pstk->size++;
}

void f_pop(struct stack* pstk, struct registrs* preg, int registr)
{
    if (pstk->size == 0)
    {
        printf("stack is empty\n");
    }

    switch (registr)
    {
        case rax:
            preg->rax = *(pstk->data + pstk->size - 1);
            break;
        case rbx:
            preg->rbx = *(pstk->data + pstk->size - 1);
            break;
        case rcx:
            preg->rcx = *(pstk->data + pstk->size - 1);
            break;
        case rdx:
            preg->rdx = *(pstk->data + pstk->size - 1);
            break;
        default:
        printf("wrong registr");
            break;
    }

    pstk->size--;
}

void f_add(struct stack* pstk)
{
    pstk->data[pstk->size - 2] += pstk->data[pstk->size - 1];
    pstk->size--;
}

void f_sub(struct stack* pstk)
{
    pstk->data[pstk->size - 2] -= pstk->data[pstk->size - 1];
    pstk->size--;
}

void f_dif(struct stack* pstk)
{
    pstk->data[pstk->size - 2] = pstk->data[pstk->size - 2] / pstk->data[pstk->size - 1];
    pstk->size--;
}

void f_mul(struct stack* pstk)
{
    pstk->data[pstk->size - 2] = pstk->data[pstk->size - 2] * pstk->data[pstk->size - 1];
    pstk->size--;
}

void f_in(struct stack* pstk)
{
    int x = 0;
    printf("Input number:\n");
    scanf("%d", &x);
    f_push(pstk, x);
}

void f_out(struct stack* pstk, struct registrs* preg)
{
    if (pstk->size == 0)
    {
        printf("stack is empty\n");
        return;
    }

    for (int i = 0; i < pstk->size; i++)
        printf("%d ", *(pstk->data + i));

    printf("     registr rax: %d; ", preg->rax);
    printf("registr rbx: %d; ", preg->rbx);
    printf("registr rcx: %d; ", preg->rcx);
    printf("registr rdx: %d; ", preg->rdx);

    printf("\n");
}
