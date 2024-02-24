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
    int marker_num = 0;

    // marker * marker_arr = (marker *) calloc(1, sizeof(marker));
    marker marker_arr[MARKER_NUM] = {};

    while (fscanf(source, "%s", command) != EOF)
    {
        // printf("%s\n", command);
        if ((strchr(command, ':')) != NULL)
        {
            strcpy(marker_arr[marker_num].marker_name, command);
            marker_arr[marker_num].marker_pt = pt;
            marker_num++;
            pt--;
            // printf("pt - %d\n", pt);
        }
        pt++;
    }

    fseek(source, 0, SEEK_SET);

    int is_marker = 0;

    while (fscanf(source, "%s", command) != EOF)
    {
        if (strchr(command, ';') == NULL)
        {
            for (int k = 0; k < MARKER_NUM; k++)
            {
                if (!strcmp(command, marker_arr[k].marker_name))
                {
                    is_marker = 1;
                }
            }

            if (is_marker == 0)
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
                                for (int k = 0; k < REGISTR_NUM; k++)
                                {
                                    if(strstr(marker_arr[k].marker_name, registr) != NULL)
                                    {
                                        printf("%d", ALL_COMMANDS[i].digital_com);
                                        fprintf(res, "%d", ALL_COMMANDS[i].digital_com);
                                        printf(" %d", marker_arr[k].marker_pt);
                                        fprintf(res, " %d", marker_arr[k].marker_pt);
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

        is_marker = 0;
    }

    // free(marker_arr);
}
