/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** help
*/

#include <stdio.h>
#include "mysh.h"

int func_help(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    (void) env;
    (void) parser;

    printf("Usage: help [FLAG]\n");
    printf("Flags:\n");
    printf("    -h, --help: display this help message\n");
    printf("    -b, --battery: display battery status\n");
    printf("    -c, --cpu: display cpu status\n");
    printf("    -m, --memory: display memory status\n");
    printf("    -n, --network: display network status\n");

    return (0);
}
