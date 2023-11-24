#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int NAME_MAX = 5;
const int REGISTR_MAX = 4;
const int COMMAND_NUM = 10;
const int REGISTR_NUM = 4;

const int INIT_CAPACITY = 10;
const int INIT_ARRAY = 10;

void SPU_construct(struct SPU* proc);
int* fill_array(int* array, int* size);
void f_add(struct stack* pstk);
void f_sub(struct stack* pstk);
void f_dif(struct stack* pstk);
void f_mul(struct stack* pstk);
void f_out(struct stack* pstk, struct registrs* preg);
void f_in(struct stack* pstk);
void f_push(struct stack* pstk, int value);
void f_push_r(struct stack* pstk, struct registrs* preg, int registr);
void f_pop(struct stack* pstk, struct registrs* preg, int registr);


enum command
{
    push = 1,
    add = 2,
    sub = 3,
    dif = 4,
    mul = 5,
    out = 6,
    in = 7,
    pop = 8,
    push_r = 17,
    pop_r = 24,
    hlt = -1,
};

enum regist
{
    rax = 1,
    rbx = 2,
    rcx = 3,
    rdx = 4,
};

struct operation
{
    char command[NAME_MAX];
    int arg_num;
    int digital_com;
};

const struct operation ALL_COMMANDS[COMMAND_NUM] = {{"push", 1, push},
                                                    {"add", 0, add},
                                                    {"sub", 0, sub},
                                                    {"div", 0, dif},
                                                    {"mul", 0, mul},
                                                    {"out", 0, out},
                                                    {"in", 0, in},
                                                    {"hlt", 0, hlt},
                                                    {"pop", 1, pop}};

struct registr
{
    char registr_name[REGISTR_MAX];
    int digital_reg;
};

const struct registr ALL_REGISTRS[REGISTR_NUM] = {  {"rax", 1},
                                                    {"rbx", 2},
                                                    {"rcx", 3},
                                                    {"rdx", 4}};

struct stack
{
    int* data;
    int size;
    int capacity;
};

struct registrs
{
    int rax;
    int rbx;
    int rcx;
    int rdx;
};

struct SPU
{
    struct stack st;
    int* array_command;
    int array_size;
    struct registrs reg;
};
