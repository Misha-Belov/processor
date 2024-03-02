#include "ass.h"

int main()
{
    FILE* source = fopen("source.txt", "r");
    FILE* res = fopen("digit.txt", "w");

    char command[NAME_MAX] = {0};
    char registr[REGISTR_MAX] = {0};

    scan(source, res, command, registr);

    fclose(source);
    fclose(res);
}


void scan(FILE* source, FILE* res, char* command, char* registr)
{
//     struct stat st;
//     stat("source.txt", &st);
//     size_t size = st.st_size;
//
//     char* string = (char*) calloc((size + 1), sizeof(char));
//     fread(string, sizeof(char), size, source);
//
//     char * pt = strchr(string, ';');
//
//     size_t i = 0;
//
//     while (*pt != '\n')
//     {
//         *pt = '\n';
//         i++;
//     }

    int pt = 0;
    int label_num = 0;

    // marker * marker_arr = (marker *) calloc(1, sizeof(marker));
    label label_arr[LABEL_NUM] = {};

    while (fscanf(source, "%s", command) != EOF)
    {
        // printf("%s\n", command);
        if ((strchr(command, ':')) != NULL)
        {
            strcpy(label_arr[label_num].label_name, command);
            label_arr[label_num].label_pt = pt;
            label_num++;
            pt--;
            printf("%s - %d\n", command, pt);
        }
        pt++;
    }

    for (int k = 0; k < LABEL_NUM; k++)
    {
        printf("%s - %d out of %d\n", label_arr[k].label_name, k, LABEL_NUM);
    }

    fseek(source, 0, SEEK_SET);

    int is_label = 0;

    while (fscanf(source, "%s", command) != EOF)
    {
        if (strchr(command, ';') == NULL)
        {
            for (int k = 0; k < LABEL_NUM; k++)
            {
                if (!strcmp(command, label_arr[k].label_name))
                {
                    is_label = 1;
                }
            }

            if (is_label == 0)
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
                                for (int k = 0; k < LABEL_NUM; k++)
                                {
                                    if(strstr(label_arr[k].label_name, registr) != NULL)
                                    {
                                        printf("%d", ALL_COMMANDS[i].digital_com);
                                        fprintf(res, "%d", ALL_COMMANDS[i].digital_com);
                                        printf(" %d", label_arr[k].label_pt);
                                        fprintf(res, " %d", label_arr[k].label_pt);
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
        }
        else
        {
            while(fgetc(source) != '\n')
            {}
        }

        is_label = 0;
    }

    // free(marker_arr);
}
