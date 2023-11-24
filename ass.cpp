#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int NAME_MAX = 6;
const int COMMAND_NUM = 7;

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
                                                    {"hlt", 0, -1} };

int main()
{
    FILE* source = fopen("source.txt", "r");

    char command[10] = {0};
    int value = 0;

    while (fscanf(source, "%s", command) != EOF)
    {
        for (int i = 0; i < COMMAND_NUM; i++)
        {
            if (!strcmp(command, ALL_COMMANDS[i].command))
            {
                printf("%d", ALL_COMMANDS[i].digital_com);

                if (ALL_COMMANDS[i].arg_num != 0)
                {
                    if (fscanf(source, "%d", &value))
                        printf(" %d", value);
                }

                printf("\n");
            }
        }
    }
}
