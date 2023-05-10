/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** search_globins
*/

#include <stdio.h>
#include <glob.h>
#include <string.h>
#include "mysh.h"

int my_tablen(char **tab);

int search_globins(parser_t *parser)
{
    glob_t result;
    int args_place = -1;

    for (int i = 1; parser->args[i] != NULL; i++) {
        if (glob(parser->args[i], GLOB_NOCHECK |
            GLOB_TILDE, NULL, &result) == 0) {
            args_place = my_tablen(parser->args);
        }
        for (int j = 0; result.gl_pathv[j] != NULL; j++) {
            parser->args[args_place] = strdup(result.gl_pathv[j]);
            args_place++;
        }
        globfree(&result);
    }
    return (0);
}
