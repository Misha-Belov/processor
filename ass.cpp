#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int NAME_MAX = 5;
const int REGISTR_MAX = 4;
const int COMMAND_NUM = 8;
const int REGISTR_NUM = 4;

enum command
{
    push = 1,
    add = 2,
    sub = 3,
    dif = 4,
    mul = 5,
    out = 6,
    hlt = -1,
};

struct operation
{
    char command[NAME_MAX];
    int arg_num;
    int digital_com;
};

const struct operation ALL_COMMANDS[COMMAND_NUM] = {{"push", 1, 1},
                                                    {"add", 0, 2},
                                                    {"sub", 0, 3},
                                                    {"div", 0, 4},
                                                    {"mul", 0, 5},
                                                    {"out", 0, 6},
                                                    {"hlt", 0, -1},
                                                    {"pop", 1, 7}};

struct registr
{
    char registr_name[REGISTR_MAX];
    int digital_reg;
};

const struct registr ALL_REGISTRS[REGISTR_NUM] = {  {"arx", 1},
                                                    {"brx", 2},
                                                    {"crx", 3},
                                                    {"drx", 4}};

int main()
{
    FILE* source = fopen("source.txt", "r");
    FILE* res = fopen("dig.txt", "w");

    char command[NAME_MAX] = {0};
    char registr[REGISTR_MAX] = {0};
    // int value = 0;

    while (fscanf(source, "%s", command) != EOF)
    {
        for (int i = 0; i < COMMAND_NUM; i++)
        {
            if (!strcmp(command, ALL_COMMANDS[i].command))
            {
                if (ALL_COMMANDS[i].arg_num != 0)
                {
                    fscanf(source, "%s", registr);

                    if (isdigit(registr[0]) || (registr[0] == '-' && isdigit(registr[1])))
                    {
                        printf("%d", ALL_COMMANDS[i].digital_com);
                        fprintf(res, "%d", ALL_COMMANDS[i].digital_com);
                        printf(" %s", registr);
                        fprintf(res, " %s", registr);
                    }
                    else
                    {
                        for (int j = 0; j < REGISTR_NUM; j++)
                        {
                            if (!strcmp(registr, ALL_REGISTRS[j].registr_name))
                            {
                                printf("%d", ALL_COMMANDS[i].digital_com + 16);
                                fprintf(res, "%d", ALL_COMMANDS[i].digital_com + 16);
                                printf(" %d", ALL_REGISTRS[j].digital_reg);
                                fprintf(res, " %d", ALL_REGISTRS[j].digital_reg);
                            }
                        }
                    }
                }

                else
                {
                    printf("%d", ALL_COMMANDS[i].digital_com);
                    fprintf(res, "%d", ALL_COMMANDS[i].digital_com);
                }

                printf("\n");
                fprintf(res, "\n");
            }
        }
    }

    fclose(source);
    fclose(res);
}
