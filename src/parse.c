/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parse
*/

#include "mysh.h"

int mysh_execute(mysh_t *mysh, env_t *env, parser_t *parser);
parser_t *parse_args(char *input, parser_t *parser);
int my_strcmp(char const *s1, char const *s2);

int check_args(parser_t *parser, mysh_t *mysh)
{
    if (my_strcmp(parser->cmd[0], '||') == 0 && mysh->status != 0) {
        parser = parser->next;
        return (0);
    } else {
        parser = parser->next->next;
        return (0);
    }
    if (my_strcmp(parser->cmd[0], '|') == 0 ||
        my_strcmp(parser->cmd[0], '>') == 0 ||
        my_strcmp(parser->cmd[0],'<') == 0) {
            parser = parser->next->next;
            return (0);
    }
    if (parser->cmd[0] == ';') {
        parser = parser->next;
        return (0);
    }
    return (1);
}

int parse_input(mysh_t *mysh, env_t *env)
{
    parser_t *parser = malloc(sizeof(parser_t));
    if (parser == NULL)
        return (84);
    parse_args(mysh->input, parser);
    while (parser->next != NULL && mysh->status != -42 &&
        mysh->input[0] != '\n') {
        if (check_args(parser, mysh) == 0)
            continue;
        mysh->status = mysh_execute(mysh, env, parser); parser = parser->next;
    }
    return (mysh->status);
}
