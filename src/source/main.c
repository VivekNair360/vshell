#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../headers/vshell.h"

#define EQUAL 0
#define TRUE 1
#define NORM_BUFF_LEN_BYTES 1024
#define BUFF_ALLOC_FAIL "error: failed to allocate buffer: %s\n"

int main (int argc, char ** argv)
{
    char * cmd;

    /* 
        REPL (Read, Eval, Print, Loop)
    */
    
    do
    {

        print_prompt_1();
        
        /* 
            Read user input 
        */

        cmd = read_cmd();

        /*
            Evaluate user input
        */

        if (!cmd)
        {
            exit(EXIT_SUCCESS);
        }

        if (cmd[0] == '\0' || strcmp(cmd, "\n") == EQUAL)
        {
            free(cmd);
            continue;
        }

        if (strcmp(cmd, "exit\n") == EQUAL)
        {
            free(cmd);
            break;
        }

        /*
            Print result of command
        */

        printf("%s\n", cmd);

        free(cmd);

        /*
            Loop
        */

    } while (TRUE);
    
    exit(EXIT_SUCCESS);
}

/*
    Reads user input from stdin into NORM_BUFF_LEN_BYTES chunks, 
    and stores this input in a buffer
*/

char * read_cmd (void)
{
    /*
        Declare buffer, 
        pointer to user input,
        and length of pointer variables
    */

    char buff[NORM_BUFF_LEN_BYTES];
    char * ptr = NULL;
    char ptrlen = 0;

    /*
        Read NORM_BUFF_LEN_BYTES from stdin into the buffer,
        and copy the contents of the buffer to a character array,
        and return a pointer to the character array */

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
            fprintf(stderr, BUFF_ALLOC_FAIL, strerror(errno));
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