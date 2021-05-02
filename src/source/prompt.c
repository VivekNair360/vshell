#include <stdio.h>
#include "../headers/vshell.h"

#define NORM_PROMPT "$ "
#define MULTI_LINE_PROMPT "> "


/* 
    Displayed when shell is waiting for user command. 
    Future value for PS1 environment variable.    
*/

void print_prompt_1(void)
{
    /* Error variable that contains number
       depending on success or failure of
       the printing of PS1 */

    int PS1err = fprintf(stderr, NORM_PROMPT);

    /* Check on error variable for PS1 printing. Values:
       Success: Num characters printed ( > 0)
       Error: ( < 0) */

    if (PS1err < 0)
    {
        /* PS1 Error message printing */
        
        printf("print_prompt_1: Character printing error\n");
    }
}

/* 
    Displayed when shell is waiting for multi-line user command. 
    Future value for PS2 environment variable.    
*/

void print_prompt_2(void)
{
    /* Error variable that contains number
       dependeing on success or failure of
       the printing of PS2 */

    int PS2err = fprintf(stderr, MULTI_LINE_PROMPT);

    /* Check on error variable for PS2 printing. Values:
       Success: Num characters printed ( > 0)
       Error: ( < 0) */
    
    if (PS2err < 0)
    {
        /* PS2 Error message printing */

        printf("print_prompt_2: Character printing error\n");
    }
}