/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exit
*/

#include "mysh.h"

int func_exit(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) env;
    (void) parser;
    mysh->status = -42;
    return (-42);
}
