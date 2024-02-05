#include "ass.h"

int main()
{
    FILE* res = fopen("dis_result.txt", "w");
    FILE* source = fopen("digit.txt", "r");

    scan(res, source);

    fclose(source);
    fclose(res);
}


void scan(FILE* res, FILE* source)
{
    int dig_com = 0;

    while (fscanf(source, "%d", &dig_com) != EOF)
    {
        switch(dig_com)
        {
            case push:
            {
                fprintf(res, "%s", "push ");
                fscanf(source, "%d", &dig_com);
                fprintf(res, "%d\n", dig_com);
                break;
            }
            case push_r:
            {
                fprintf(res, "%s", "push ");
                fscanf(source, "%d", &dig_com);
                switch (dig_com)
                {
                    case rax:
                        fprintf(res, "%s\n", "rax");
                        break;
                    case rbx:
                        fprintf(res, "%s\n", "rbx");
                        break;
                    case rcx:
                        fprintf(res, "%s\n", "rcx");
                        break;
                    case rdx:
                        fprintf(res, "%s\n", "rdx");
                        break;
                    default:
                        printf("wrong registr");
                        break;
                }
                break;
            }
            case add:
            {
                fprintf(res, "%s", "add\n");
                break;
            }
            case sub:
            {
                fprintf(res, "%s", "sub\n");
                break;
            }
            case dif:
            {
                fprintf(res, "%s", "dif\n");
                break;
            }
            case mul:
            {
                fprintf(res, "%s", "mul\n");
                break;
            }
            case out:
            {
                fprintf(res, "%s", "out\n");
                break;
            }
            case in:
            {
                fprintf(res, "%s", "in\n");
                break;
            }
            case pop_r:
            {
                fprintf(res, "%s", "pop ");
                fscanf(source, "%d", &dig_com);
                switch (dig_com)
                {
                    case rax:
                        fprintf(res, "%s\n", "rax");
                        break;
                    case rbx:
                        fprintf(res, "%s\n", "rbx");
                        break;
                    case rcx:
                        fprintf(res, "%s\n", "rcx");
                        break;
                    case rdx:
                        fprintf(res, "%s\n", "rdx");
                        break;
                    default:
                        printf("wrong registr");
                        break;
                }
                break;
            }
            case hlt:
            {
                fprintf(res, "%s", "hlt\n");
                break;
            }
            default:
            {
                return;
                break;
            }
        }
    }
}
