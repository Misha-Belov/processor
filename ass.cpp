#include "ass.h"

int main()
{
    FILE* source = fopen("source.txt", "r");
    FILE* res = fopen("digit.txt", "w");

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
