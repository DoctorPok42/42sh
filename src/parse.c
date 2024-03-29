/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parse
*/

#include <string.h>
#include "mysh.h"

void search_globins(parser_t *parser);
int mysh_execute(mysh_t *mysh, env_t *env, parser_t *parser);
parser_t *parse_args(char *input, parser_t *parser);
int my_strcmp(char const *s1, char const *s2);
char *check_alias(mysh_t *mysh);

int check_args(parser_t *parser, mysh_t *mysh)
{
    if ((my_strcmp(parser->cmd, "||") == 0 && mysh->status != 0) ||
        (my_strcmp(parser->cmd, "&&") == 0 && mysh->status == 0))
        return (1);
    if ((my_strcmp(parser->cmd, "||") == 0 && mysh->status == 0) ||
        (my_strcmp(parser->cmd, "&&") == 0 && mysh->status != 0))
        return (2);

    if (parser->cmd[0] == '|' ||
        parser->cmd[0] == '>' ||
        parser->cmd[0] == '<')
            return (2);

    if (parser->cmd[0] == ';')
        return (1);
    return (0);
}

static int alias_input_change(mysh_t *mysh, env_t *env, char *cmd,
    parser_t *parser)
{
    (void)env;
    (void)parser;
    cmd = mysh->input;
    if (strcmp(mysh->input, "\n") == 0)
        return (mysh->status);
    if ((cmd = check_alias(mysh)) != NULL)
        mysh->input = cmd;
    return 0;
}

int parse_input(mysh_t *mysh, env_t *env, char *cmd)
{
    parser_t *parser = malloc(sizeof(parser_t));
    int check_args_return = 0;
    if (parser == NULL)
        return (84);
    alias_input_change(mysh, env, cmd, parser);
    parse_args(mysh->input, parser);
    search_globins(parser);
    while (parser->next != NULL && mysh->status != -42 &&
        mysh->input[0] != '\n') {
        check_args_return = check_args(parser, mysh);
        if (check_args_return == 2) {
            parser = parser->next->next; continue;
        }
        if (check_args_return == 1) {
            parser = parser->next; continue;
        }
        mysh->status = mysh_execute(mysh, env, parser); parser = parser->next;
    }
    return (mysh->status);
}
