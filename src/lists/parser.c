/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parser
*/

#include <stdlib.h>
#include "lists.h"

int my_strlen(char const *src);
char **my_str_to_word_array(char const *str, char const separator);
int my_tablen(char **tab);

parser_t *put_parser(parser_t *parser, char **tab)
{
    char **tmp = NULL; parser_t *head = parser;
    for (int i = 0; tab[i] != NULL; i++) {
        tmp = my_str_to_word_array(tab[i], ' ');
        head->cmd = malloc(sizeof(char) * (my_strlen(tmp[0]) + 1));
        head->cmd[my_strlen(tmp[0])] = '\0';
        for (int j = 0; tmp[0][j] != '\0'; j++) {
            head->cmd[j] = tmp[0][j];
        }
        head->args = malloc(sizeof(char *) * (my_tablen(tmp) + 1));
        head->args[my_tablen(tmp)] = NULL;
        for (int j = 0; tmp[j] != NULL; j++) {
            head->args[j] = tmp[j];
        }
        head->next = malloc(sizeof(parser_t));
        head = head->next;
    }
    parser->next->args = NULL;
    parser->next->cmd = NULL;
    head->next = NULL;
    return parser;
}
