#include <stdio.h>
#include "../headers/vshell.h"


/* Displayed when shell is waiting for user command */
void print_prompt_1(void)
{
    fprintf(stderr, "$ ");
}

/* Displayed when shell is waiting for multi-line user command */
void print_prompt_2(void)
{
    fprintf(stderr, "> ");
}