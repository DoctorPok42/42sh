/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** task04
*/

#include <stdlib.h>
#include <stdbool.h>

static bool check(char const c, char const separator)
{
    if (c == separator || c == '\t' || c == '\n' || c == '\0' || c == ' ')
        return true;
    return false;
}

static int count_word(char const *str, char const separator)
{
    int nb_words = 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (check(str[i], separator) && !check(str[i + 1], separator)) {
            nb_words += 1;
        }
    }
    return nb_words;
}

static char **put_in_tab(char **tab, char const *str, char const separator)
{
    int nb_words = count_word(str, separator);
    int j = 0;
    int size = 0;
    for (int i = 0; i < nb_words; i++) {
        for (size = 0; str[j] != separator && str[j] != '\0'; j++, size++);
        j -= size;
        tab[i] = malloc(sizeof(char) * size + 1);
        tab[i][size] = '\0';
        for (int k = 0; k < size; k++, j++) {
            tab[i][k] = str[j];
        }
        while (str[j] == separator || str[j] == '\t') {
            j++;
        }
    }
    return tab;
}

char **my_str_to_word_array(char *str, char const separator)
{
    int nb_words = count_word(str, separator);
    char **tab = malloc(sizeof(char *) * (nb_words + 1));
    if (tab == NULL)
        return NULL;
    tab[nb_words] = NULL;
    tab = put_in_tab(tab, str, separator);

    for (int i = 0; tab[nb_words - 1][i] != '\0'; i++) {
        if (tab[nb_words - 1][i] == ' ' || tab[nb_words - 1][i] == '\t') {
            tab[nb_words - 1][i] = '\0';
        }
    }

    for (int i = 0; i < nb_words; i++) {
        for (int j = 0; tab[i][j] != '\0'; j++) {
            (tab[i][j] == '\n') ? tab[i][j] = '\0' : 0;
        }
    }

    return tab;
}
