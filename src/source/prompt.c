#include <stdio.h>
#include "../headers/vshell.h"

#define NORM_PROMPT "$ "
#define MULTI_LINE_PROMPT "> "


/* Displayed when shell is waiting for user command */

void print_prompt_1(void)
{
    fprintf(stderr, NORM_PROMPT);
}

/* Displayed when shell is waiting for multi-line user command */

void print_prompt_2(void)
{
    fprintf(stderr, MULTI_LINE_PROMPT);
}