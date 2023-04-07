/*
** EPITECH PROJECT, 2023
** mysh2
** File description:
** put_in_args
*/

#include <stdlib.h>
#include "lists.h"

int my_tablen(char **tab);
int my_strlen(char const *src);
char **my_str_to_word_array(char const *str, char const separator);

char **put_in_args(parser_t *parser, char *buff)
{
    char **tmp = my_str_to_word_array(buff, '\n');
    int size_one = my_tablen(parser->args);
    int size_two = my_tablen(tmp);
    char **tab = malloc(sizeof(char *) * (size_one + size_two) + 1);
    for (int i = 0; i < size_one; i++) {
        tab[i] = malloc(sizeof(char) * (my_strlen(parser->args[i]) + 1));
        tab[i][my_strlen(parser->args[i])] = '\0';
        for (int j = 0; parser->args[i][j] != '\0'; j++) {
            tab[i][j] = parser->args[i][j];
        }
    }
    for (int i = 0; i < size_two; i++) {
        tab[size_one + i] = malloc(sizeof(char) * (my_strlen(tmp[i]) + 1));
        tab[size_one + i][my_strlen(tmp[i])] = '\0';
        for (int j = 0; tmp[i][j] != '\0'; j++) {
            tab[size_one + i][j] = tmp[i][j];
        }
    }
    tab[size_one + size_two + 1] = NULL;
    return tab;
}
