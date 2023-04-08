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
void my_put_nbr(int nb);
int my_strlen(char const *src);
int error_handling(int status);
void check_github(mysh_t *mysh);
void my_putstr(char const *str);
char **parsing_path(mysh_t *mysh);
char *get_env(env_t *env, char *find);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
parser_t *parse_args(char *input, parser_t *parser);
int launch_redirection(env_t *env, parser_t *parser, int status);
int launch_pipe(env_t *env, parser_t *parser, int status);
int launch_file(env_t *env, parser_t *parser, int status);
int launch_default(env_t *env, parser_t *parser, int status);
char **my_str_to_word_array(char const *str, char const separator);

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

static int mysh_execute(mysh_t *mysh, env_t *env, parser_t *parser)
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

void check_status(mysh_t *mysh)
{
    check_github(mysh);
    if (mysh->status == 0) {
        my_putstr("\033[32;1m ✔ \033[44;1m\033[37;1m");
    } else {
        my_putstr("\033[31;1m ✘ ");
        my_put_nbr(mysh->status);
        my_putstr(" \033[44;1m\033[37;1m");
    }
}

int mysh_loop(mysh_t *mysh, env_t *env)
{
    char *input = NULL; size_t len = 0; int loop = 0; size_t size = 0;
    parser_t *parser = malloc(sizeof(parser_t));
    while (loop == 0) { my_putstr("\033[44;1m"); check_status(mysh);
        (!mysh->no_env) ? my_putstr(&getcwd(NULL, size)[my_strlen(
                get_env(env, "HOME")) + 1]) : 0;
        if (mysh->github[0] != '\0') { printf("\033[49m\033[33;1m git:("
            "\033[32;1m%s\033[33;1m) >\033[37;0m ", mysh->github);
        } else  { printf("\033[0m\033[33;1m\033[49m >\033[37;0m ");
        } if (getline(&input, &len, stdin) == -1) {mysh->status = -42; break;
        } loop = 1;
    } if (mysh->status == -42) return (mysh->status);
    mysh->input = input;
    parse_args(input, parser);
    while (parser->next != NULL && mysh->status != -42 && input[0] != '\n') {
        if (parser->cmd[0] == '|' || parser->cmd[0] == '>' ||
            parser->cmd[0] == '<') { parser = parser->next->next; continue;
        } if (parser->cmd[0] == ';') { parser = parser->next; continue;
        }
        mysh->status = mysh_execute(mysh, env, parser); parser = parser->next;
    } return (mysh->status);
}
