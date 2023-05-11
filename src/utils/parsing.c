/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parsing
*/

#include <stdbool.h>
#include <string.h>
#include "mysh.h"
#include "lists.h"

char *get_env(env_t *env, char *find);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
parser_t *put_parser(parser_t *parser, char **tab);
char **my_str_to_word_array(char const *str, char const separator);

char **parsing_path(env_t *env)
{
    char *path = get_env(env, "PATH");
    char **path_slice = my_str_to_word_array(path, ':');

    for (int i = 0; path_slice[i] != NULL; i++) {
        path_slice[i] = my_strcat(path_slice[i], "/");
    }

    return path_slice;
}

bool token(char arg)
{
    char *token[9] = {"&&", ";", "|", "||", ">", ">>", "<", "<<", NULL};
    for (int j = 0; token[j] != NULL; j++) {
        if (arg == token[j][0] && (arg == token[j][1] || token[j][1] == '\0'))
            return false;
    }
    return true;
}

static int delete_space(char *str, int i, int j)
{
    if (str[i] != ' ' && str[i] != '\t') {
        str[j++] = str[i];
    } else if (j > 0 && str[i + 1] != '\0' && str[i + 1] != ' ' &&
        str[i + 1] != '\t') {
        str[j++] = ' ';
    }
    return j;
}

static char **clean_tab(char **tab)
{
    int i, j, k;
    for (i = 0; tab[i] != NULL; i++) {
        for (j = 0, k = 0; tab[i][j] != '\0'; j++) {
            k = delete_space(tab[i], j, k);
        }
        tab[i][k] = '\0';
    }
    return tab;
}

parser_t *parse_args(char *input, parser_t *parser)
{
    char **tab = malloc(sizeof(char *) * 100);
    int i = 0; int j = 0;int size = 0;
    while (input[i] != '\0') {
        if (token(input[i]) == true) {
            (size == 0) ? tab[j] = malloc(sizeof(char) * 100) : 0;
            (size == 0 && input[i] == ' ') ? i++ : 0;
            tab[j][size] = input[i]; size++; tab[j][size] = '\0';
        } else {
            j++; size = 0; tab[j] = malloc(sizeof(char) * 3);
            tab[j][0] = input[i];
            tab[j][1] = (token(input[i + 1]) == false) ? input[i + 1] : '\0';
            tab[j][2] = '\0';
            (token(input[i + 1]) == false) ? i++ : 0;
            j++; size = 0;
        } i++;
    }
    if (size > 0) {
        tab[j][size] = '\0'; j++;
    } tab[j] = NULL; tab = clean_tab(tab);
    parser = put_parser(parser, tab); return parser;
}
