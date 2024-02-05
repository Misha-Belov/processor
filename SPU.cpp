#include "ass.h"

int main()
{
    struct SPU proc = {};

    SPU_construct(&proc);
    proc.array_command = fill_array(proc.array_command, &(proc.array_size));

    cmd_execution(&proc);
}

void cmd_execution(struct SPU* proc)
{
    int IP = 0;
    for(;;)
    {
        switch(proc->array_command[IP])
        {

            case push:
            {
                f_push(&proc->st, proc->array_command[IP + 1]);
                IP += 2;
                break;
            }
            case push_r:
            {
                f_push_r(&proc->st, &proc->reg, proc->array_command[IP + 1]);
                IP += 2;
                break;
            }
            case add:
            {
                f_add(&proc->st);
                IP++;
                break;
            }
            case sub:
            {
                f_sub(&proc->st);
                IP++;
                break;
            }
            case dif:
            {
                f_dif(&proc->st);
                IP++;
                break;
            }
            case mul:
            {
                f_mul(&proc->st);
                IP++;
                break;
            }
            case dmp:
            {
                f_dmp(&proc->st, &proc->pt, &proc->reg);
                IP++;
                break;
            }
            case in:
            {
                f_in(&proc->st);
                IP++;
                break;
            }
            case out:
            {
                f_out(&proc->st);
                IP++;
                break;
            }
            case jmp:
            {
                IP = proc->array_command[IP + 1];
                break;
            }
            case jb:
            {
                if (proc->st.data[proc->st.size - 2] < proc->st.data[proc->st.size - 1])
                {
                    IP = proc->array_command[IP + 1];
                }
                else IP += 2;
                break;
            }
            case jbe:
            {
                if (proc->st.data[proc->st.size - 2] <= proc->st.data[proc->st.size - 1])
                {
                    IP = proc->array_command[IP + 1];
                }
                else IP += 2;
                break;
            }
            case ja:
            {
                if (proc->st.data[proc->st.size - 2] > proc->st.data[proc->st.size - 1])
                {
                    IP = proc->array_command[IP + 1];
                }
                else IP += 2;
                break;
            }
            case jae:
            {
                if (proc->st.data[proc->st.size - 2] >= proc->st.data[proc->st.size - 1])
                {
                    IP = proc->array_command[IP + 1];
                }
                else IP += 2;
                break;
            }
            case je:
            {
                if (proc->st.data[proc->st.size - 2] == proc->st.data[proc->st.size - 1])
                {
                    IP = proc->array_command[IP + 1];
                }
                else IP += 2;
                break;
            }
            case jne:
            {
                if (proc->st.data[proc->st.size - 2] != proc->st.data[proc->st.size - 1])
                {
                    IP = proc->array_command[IP + 1];
                }
                else IP += 2;
                break;
            }
            case pop_r:
            {
                f_pop_r(&proc->st, &proc->reg, proc->array_command[IP + 1]);
                IP += 2;
                break;
            }
            case call:
            {
                f_push(&proc->pt, IP);
                IP = proc->array_command[IP + 1];
                break;
            }
            case ret:
            {
                if (proc->pt.size >= 1)
                {
                    IP = proc->pt.data[proc->pt.size - 1] + 2;
                    printf("%d %d ", proc->pt.size, IP);
                    f_pop(&proc->pt);
                }
                else
                    IP += 1;
                break;
            }
            case 0:
            {
                IP += 2;
                break;
            }
            case hlt:
            {
                SPU_deconstruct(proc);
                return;
                break;
            }
            default:
            {
                perror("wrong command\n");
                break;
            }
        }
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

void SPU_deconstruct(struct SPU* proc)
{
    free (proc->st.data);
    proc->st.data = NULL;
    proc->st.capacity = 0;
    proc->st.size = 0;

    proc->reg.rax = 0;
    proc->reg.rbx = 0;
    proc->reg.rcx = 0;
    proc->reg.rdx = 0;

    free (proc->array_command);
    proc->array_command = NULL;
    proc->array_size = 0;
}

int* fill_array(int* array, int* size)
{
    FILE* instr = fopen("digit.txt", "r");

    int value = 0, i = 0;

    while (fscanf(instr, "%d", &value) != EOF)
    {
        if(i == *size - 1)
        {
            int* tmp = 0;
            if (!(tmp = (int*) realloc(array, 2 * *size * sizeof(int))))
            {
                perror("problem in realloc\n");
            }
            *size = *size * 2;
            array = tmp;
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
            perror("problem in realloc\n");
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
            perror("problem in realloc\n");
        }
        pstk->capacity = pstk->capacity * 2;
        pstk->data = tmp;
    }

    push_register(pstk, preg, registr);
    pstk->size++;
}

void push_register(struct stack* pstk, struct registrs* preg, int registr)
{
    switch (registr)
    {
        case rax:
            *(pstk->data + pstk->size) = preg->rax;
            break;
        case rbx:
            *(pstk->data + pstk->size) = preg->rbx;
            break;
        case rcx:
            *(pstk->data + pstk->size) = preg->rcx;
            break;
        case rdx:
            *(pstk->data + pstk->size) = preg->rdx;
            break;
        default:
            perror("wrong register");
            break;
    }
}

void read_register(struct stack* pstk, struct registrs* preg, int registr)
{

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
            perror("wrong register");
            break;
    }
}

void f_pop_r(struct stack* pstk, struct registrs* preg, int registr)
{
    if (pstk->size == 0)
    {
        perror("stack is empty\n");
    }

    read_register(pstk, preg, registr);
    push_register(pstk, preg, registr);

    pstk->size--;
}

void f_pop(struct stack* pstk)
{
    if (pstk->size == 0)
    {
        perror("stack is empty\n");
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

void f_dmp(struct stack* st, struct stack* pt, struct registrs* preg)
{
    FILE* dump = fopen("dump.txt", "a");

    if (st->size == 0)
    {
        perror("stack is empty\n");
        return;
    }

    for (int i = 0; i < pt->size; i++)
        fprintf(dump, "%d ", *(pt->data + i));

    fprintf(dump, "\n");

    for (int i = 0; i < st->size; i++)
        fprintf(dump, "%d ", *(st->data + i));

    fprintf(dump, "     registr rax: %d; ", preg->rax);
    fprintf(dump, "registr rbx: %d; ", preg->rbx);
    fprintf(dump, "registr rcx: %d; ", preg->rcx);
    fprintf(dump, "registr rdx: %d; ", preg->rdx);

    fprintf(dump, "\n");

    //--------------------------------------------------

    for (int i = 0; i < st->size; i++)
        printf("%d ", *(st->data + i));

    printf("     registr rax: %d; ", preg->rax);
    printf("registr rbx: %d; ", preg->rbx);
    printf("registr rcx: %d; ", preg->rcx);
    printf("registr rdx: %d; ", preg->rdx);

    printf("\n");

    fclose(dump);
}

void f_out(struct stack* pstk)
{
    if (pstk->size == 0)
    {
        perror("stack is empty\n");
        return;
    }

    printf("%d\n", pstk->data[pstk->size - 1]);
}
