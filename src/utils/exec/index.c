/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** index
*/

#include <unistd.h>
#include "mysh.h"

void my_putstr(char const *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int launch_redirection(env_t *env, parser_t *parser, int status);
int launch_pipe(env_t *env, parser_t *parser, int status);
int launch_file(env_t *env, parser_t *parser, int status);
int launch_default(env_t *env, parser_t *parser, int status);

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

int mysh_launch(mysh_t *mysh, env_t *env, parser_t *parser)
{
    char *next_cmd = parser->next->cmd;
    if (next_cmd == NULL)
        return launch_default(env, parser, mysh->status);

    if (my_strcmp(next_cmd, "|") == 0)
        return launch_pipe(env, parser, mysh->status);
    if ((my_strcmp(next_cmd, ">") == 0) || (my_strcmp(next_cmd, ">>") == 0))
        return launch_redirection(env, parser, mysh->status);
    if ((my_strcmp(next_cmd, "<") == 0) || (my_strcmp(next_cmd, "<<") == 0))
        return launch_file(env, parser, mysh->status);
    return launch_default(env, parser, mysh->status);
}
