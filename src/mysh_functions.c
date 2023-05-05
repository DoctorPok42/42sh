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

void get_input(mysh_t *mysh);
void my_putstr(char const *str);
int display_prompt(mysh_t *mysh, env_t *env);
int my_strcmp(char const *s1, char const *s2);
int parse_input(mysh_t *mysh, env_t *env, char *cmd);
int mysh_launch(mysh_t *mysh, env_t *env, parser_t *parser);
int check_alias(mysh_t *mysh, env_t *env, parser_t *parser);

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
    return -1;
}

int mysh_loop(mysh_t *mysh, env_t *env)
{
    mysh->input = NULL;
    char *cmd = NULL;

    if (isatty(0) == 1)
        mysh->status = display_prompt(mysh, env);

    get_input(mysh);
    write(1, "\n", 1);

    if (mysh->status == -42)
        return (mysh->status);
    if (mysh->input[0] == '\0')
        return 0;

    if (parse_input(mysh, env, cmd) == 84 || mysh->status == -42)
        return (84);
    return mysh->status;
}
