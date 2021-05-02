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

        /* If no user input from stdin (for whatever reason),
           exit the program. */

        if (!cmd)
        {
            exit(EXIT_SUCCESS);
        }

        /* If the user simply pressed the ENTER key, continue the loop */

        if (cmd[0] == '\0' || strcmp(cmd, "\n") == EQUAL)
        {
            free(cmd);
            continue;
        }

        /* If the user typed the 'exit' command 
           (e.g. wants to terminate the vshell session),
           break the loop */

        if (strcmp(cmd, "exit\n") == EQUAL)
        {
            free(cmd);
            break;
        }

        /*
            Print result of command
        */

        printf("%s\n", cmd);

        /* Free the memory used by the command as it is no longer needed */

        free(cmd);

        /*
            Loop
        */

    } while (TRUE);

    /* Terminate vshell successfully */
    
    exit(EXIT_SUCCESS);
}

/*
    Reads user input from stdin into NORM_BUFF_LEN_BYTES chunks, 
    stores this input in a buffer,
    copies the input to a char array,
    and returns a pointer to this array.
    Return Values:
    NULL: Nothing to output (user input from stdin has been fully processed)
    ( > 0): This is a pointer to a character array containing the user input from stdin
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
        and return a pointer to the character array 
    */

    while (fgets(buff, NORM_BUFF_LEN_BYTES, stdin))
    {
        /* Variable to keep track of buffer length
           in order to reallocate memory if
           needed or anticipated, and
           free memory when reading from stdin is complete
           or upon error while reading */

        int bufflen = strlen(buff);

        /* Check if ptr is NULL */

        if (!ptr)
        {
            /* In case ptr is NULL, 
               allocate bufflen + 1 bytes (1 byte for NUL terminator)
               and assign to ptr a pointer to the beginning of this region */
               
            ptr = malloc(bufflen + 1);
        }
        else
        {
            /* Temporary variable to store pointer to 
               buffer (extended by byte length of latest read from stdin
               plus 1 for NUL terminator).
               New buffer is the old one with contents unchanged from start
               of old buffer to min(size of old, size of new). */

            char * ptr2 = realloc(ptr, ptrlen + bufflen + 1);

            /* Check if pointer to new buffer is NULL */

            if (ptr2)
            {
                /* The realloc() succeeded (ptr2 is not NULL),
                   and the pointer to the current buffer (ptr)
                   is updated to the pointer to the new buffer */

                ptr = ptr2;
            }
            else
            {
                /* The realloc() failed (ptr2 is NULL),
                   and the current buffer is freed,
                   and the pointer to the current buffer is set to NULL */

                free(ptr);
                ptr = NULL;
            }
        }

        /* Check if ptr is still NULL (implies buffer memory allocation failed) */

        if (!ptr)
        {
            /* Print error message to indicate the buffer memory allocation failure
               and return NULL */

            fprintf(stderr, BUFF_ALLOC_FAIL, strerror(errno));
            return NULL;
        }

        /* Memory has been properly allocated to ptr1,
           this now copies the contents of the current read from stdin
           (located in buff) to the position right after the contents
           of the previous read.
           
           Note for future: Return value (a pointer to destination string) currently ignored */

        strcpy(ptr + ptrlen, buff);

        /* Check if current input in buffer ends with newline */

        if (buff[bufflen - 1] == '\n')
        {
            /* If the last element in the buffer is not escaped,
               we have finished reading in the input line
               and we return a pointer to current buffer
               (containing the full input line) */

            if (bufflen == 1 || buff[bufflen - 2] != '\\')
            {
                return ptr;
            }

            /* The input in the buffer is escaped,
               so we set the null terminator 2 positions
               from the end of the buffer, and decrement our
               buffer length variable by 2.
               We then print PS2 to process the incoming
               multiline input */

            ptr[ptrlen + bufflen - 2] = '\0';
            bufflen -= 2;
            print_prompt_2();
        }

        /* Increment the current end position of user input */

        ptrlen += bufflen;
    }

    /* We are done reading the user input from stdin,
       and now return a pointer to our buffer containing
       the contents of the user input */

    return ptr;

}