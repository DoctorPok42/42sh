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

void search_globins(parser_t *parser)
{
    glob_t result = {0};
    int args_place = -1;
    for (int i = 1; parser->args[i] != NULL; i++) {
        if (glob(parser->args[i], 0, NULL, &result) == 0) {
            args_place = my_tablen(parser->args);
        }
        if (args_place == -1)
            continue;
        parser->args[args_place] = NULL;
        if (result.gl_pathc < 2)
            continue;
        for (size_t i = 0; i < result.gl_pathc; i++) {
            parser->args[args_place - 1] = malloc(sizeof(char) *
            (strlen(result.gl_pathv[i]) + 1));
            strcpy(parser->args[args_place - 1], result.gl_pathv[i]);
            args_place++;
        }
        globfree(&result);
        parser->args[args_place] = NULL;
    }
}
