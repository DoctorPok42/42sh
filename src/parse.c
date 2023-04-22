/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parse
*/

#include "mysh.h"

int mysh_execute(mysh_t *mysh, env_t *env, parser_t *parser);
parser_t *parse_args(char *input, parser_t *parser);

int parse_input(mysh_t *mysh, env_t *env)
{
    parser_t *parser = malloc(sizeof(parser_t));
    if (parser == NULL)
        return (84);
    parse_args(mysh->input, parser);
    while (parser->next != NULL && mysh->status != -42 &&
        mysh->input[0] != '\n') {
        if (parser->cmd[0] == '|' || parser->cmd[0] == '>' ||
            parser->cmd[0] == '<') {
                parser = parser->next->next;
                continue;
        }
        if (parser->cmd[0] == ';') {
            parser = parser->next;
            continue;
        }
        mysh->status = mysh_execute(mysh, env, parser); parser = parser->next;
    }
    return (mysh->status);
}
