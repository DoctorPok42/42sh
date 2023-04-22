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

bool token(char *arg);
int error_handling(int status);
void my_putstr(char const *str);
char **parsing_path(mysh_t *mysh);
char *my_strcat(char *dest, char const *src);
int display_prompt(mysh_t *mysh, env_t *env);
int my_strcmp(char const *s1, char const *s2);
int launch_redirection(env_t *env, parser_t *parser, int status);
int launch_pipe(env_t *env, parser_t *parser, int status);
int launch_file(env_t *env, parser_t *parser, int status);
int launch_default(env_t *env, parser_t *parser, int status);
char **my_str_to_word_array(char const *str, char const separator);
int parse_input(mysh_t *mysh, env_t *env);

char *check_pass(parser_t *parser, char **path_slice)
{
    char *path = NULL;

    if (access(parser->cmd, F_OK) == 0)
        return parser->cmd;

    for (int i = 0; path_slice[i] != NULL; i++) {
        path = my_strcat(path_slice[i], parser->cmd);
        if (access(path, F_OK) == 0) {
            parser->cmd = path;
            return parser->cmd;
        }
    }
    my_putstr(parser->cmd);
    my_putstr(": Command not found.\n");
    return NULL;
}

static int mysh_launch(mysh_t *mysh, env_t *env, parser_t *parser)
{
    if (parser->next == NULL)
        return launch_default(env, parser, mysh->status);
    char *next_cmd = parser->next->cmd;

    if (my_strcmp(next_cmd, "|") == 0)
        return launch_pipe(env, parser, mysh->status);
    if ((my_strcmp(next_cmd, ">") == 0) || (my_strcmp(next_cmd, ">>") == 0))
        return launch_redirection(env, parser, mysh->status);
    if ((my_strcmp(next_cmd, "<") == 0) || (my_strcmp(next_cmd, "<<") == 0))
        return launch_file(env, parser, mysh->status);
    return launch_default(env, parser, mysh->status);
}

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
    char *input = NULL; size_t len = 0; int loop = 0;

    while (loop == 0) {
        if (isatty(0) == 1) {
            mysh->status = display_prompt(mysh, env);
        }
        if (mysh->status == -42)
            return (mysh->status);
        if (getline(&input, &len, stdin) == -1) {
            mysh->status = -42;
            break;
        }
        loop = 1;
    }
    if (mysh->status == -42)
        return (mysh->status);
    mysh->input = input;
    if (parse_input(mysh, env) == 84)
        return (84);
    return mysh->status;
}
