#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>

const int NAME_MAX = 15;
const int REGISTR_MAX = 15;
const int MARKER_MAX = 15;
const int COMMAND_NUM = 21;
const int REGISTR_NUM = 4;
const int LABEL_NUM = 100;

const int INIT_CAPACITY = 10;
const int INIT_ARRAY = 10;

void SPU_construct(struct SPU* proc);
void SPU_deconstruct(struct SPU* proc);
int* fill_array(int* array, int* size);
void cmd_execution(struct SPU* proc);
void read_register(struct stack* pstk, struct registrs* preg, int registr);
void push_register(struct stack* pstk, struct registrs* preg, int registr);
void f_add(struct stack* pstk);
void f_sub(struct stack* pstk);
void f_dif(struct stack* pstk);
void f_mul(struct stack* pstk);
void f_sqr(struct stack* pstk);
void f_out(struct stack* pstk);
void f_dmp(struct stack* st, struct stack* pt, struct registrs* preg);
void f_in(struct stack* pstk);
void f_push(struct stack* pstk, int value);
void f_push_r(struct stack* pstk, struct registrs* preg, int registr);
void f_pop_r(struct stack* pstk, struct registrs* preg, int registr);
void f_pop(struct stack* pstk);
void scan(FILE* source, FILE* res, char* command, char* registr);
void scan(FILE* res, FILE* source);

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
    jmp = 9,
    jb = 10,
    jbe = 11,
    ja = 12,
    jae = 13,
    je = 14,
    jne = 15,
    dmp = 16,
    push_r = 17,
    pop_r = 24,
    call = 25,
    ret = 26,
    sqr = 27,
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
                                                    {"pop", 1, pop},
                                                    {"jmp", 1, jmp},
                                                    {"jb", 1, jb},
                                                    {"jbe", 1, jbe},
                                                    {"ja", 1, ja},
                                                    {"jae", 1, jae},
                                                    {"je", 1, je},
                                                    {"jne", 1, jne},
                                                    {"dmp", 0, dmp},
                                                    {"call", 1, call},
                                                    {"sqr", 0, sqr},
                                                    {"ret", 0, ret}};

struct registr
{
    char registr_name[REGISTR_MAX];
    int digital_reg;
};

struct label
{
    char label_name[MARKER_MAX];
    int label_pt;

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
    struct stack pt;
};
