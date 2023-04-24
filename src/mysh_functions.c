/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** 42sh_functions
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "mysh.h"
#include "lists.h"

void my_putstr(char const *str);
int display_prompt(mysh_t *mysh, env_t *env);
int my_strcmp(char const *s1, char const *s2);
int parse_input(mysh_t *mysh, env_t *env);
int mysh_launch(mysh_t *mysh, env_t *env, parser_t *parser);

int mysh_execute(mysh_t *mysh, env_t *env, parser_t *parser)
{
    for (int i = 0; FLAGS[i].flags != NULL; i++) {
        if (my_strcmp(parser->cmd, FLAGS[i].flags) == 0) {
            mysh->status = FLAGS[i].function(mysh, env, parser);
            return (mysh->status);
        }
    }
    if (mysh->no_env) {
        my_putstr(parser->cmd); my_putstr(": Command not found.\n");
        return (127);
    } else
        return mysh_launch(mysh, env, parser);
    return (mysh->status);
}

int mysh_loop(mysh_t *mysh, env_t *env)
{
    char *input = NULL;
    size_t len = 0;
    int loop = 0;

    while (loop == 0) {
        if (isatty(0) == 1)
            mysh->status = display_prompt(mysh, env);
        if (mysh->status == -42)
            return (mysh->status);
        if (getline(&input, &len, stdin) == -1)
            mysh->status = -42;
        loop = 1;
    }

    if (mysh->status == -42)
        return (mysh->status);
    mysh->input = input;
    if (parse_input(mysh, env) == 84)
        return (84);
    return mysh->status;
}
