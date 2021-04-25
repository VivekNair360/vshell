#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "vshell.h"

#define TRUE (1)
#define NORM_BUFF_LEN_BYTES (1024)

int main (int argc, char ** argv)
{
    char * cmd;
    
    do
    {
        print_prompt_1();
        
        cmd = read_cmd();

        if (!cmd)
        {
            exit(EXIT_SUCCESS);
        }

        if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
        {
            free(cmd);
            continue;
        }

        if (strcmp(cmd, "exit\n") == 0)
        {
            free(cmd);
            break;
        }

        printf("%s\n", cmd);

        free(cmd);

    } while (TRUE);
    
    exit(EXIT_SUCCESS);
}

char * read_cmd (void)
{
    char buff[NORM_BUFF_LEN_BYTES];
    char * ptr = NULL;
    char ptrlen = 0;

    while (fgets(buff, NORM_BUFF_LEN_BYTES, stdin))
    {
        int bufflen = strlen(buff);

        if (!ptr)
        {
            ptr = malloc(bufflen + 1);
        }
        else
        {
            char * ptr2 = realloc(ptr, ptrlen + bufflen + 1);

            if (ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr)
        {
            fprintf(stderr, "error: failed to allocate buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr + ptrlen, buff);

        if (buff[bufflen - 1] == '\n')
        {
            if (bufflen == 1 || buff[bufflen - 2] != '\\')
            {
                return ptr;
            }

            ptr[ptrlen + bufflen - 2] = '\0';
            bufflen -= 2;
            print_prompt_2();
        }

        ptrlen += bufflen;
    }

    return ptr;

}