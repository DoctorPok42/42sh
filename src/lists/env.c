/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** env
*/

#include "lists.h"
#include "mysh.h"

int my_strlen(char const *str);
char *my_strcat(char *dest, char const *src);
char **my_str_to_word_array(char *str, char separator);

env_t *put_in_env(char **tab, env_t *env)
{
    char **tmp;

    for (int i = 0; tab[i] != NULL; i++) {
        tmp = my_str_to_word_array(tab[i], '=');
        env->name = tmp[0];
        for (int i = 0; tmp[1][i] != '\0'; i++);
        env->value = tmp[1];
        env->next = malloc(sizeof(env_t));
        env = env->next;
    }
    env->next = NULL;
    return env;
}

char **env_tab(env_t *env)
{
    char **tab = malloc(sizeof(char *) * 3);
    int i = 0;

    while (env->next != NULL) {
        tab[i] = malloc(sizeof(char) * (my_strlen(env->name) +
            my_strlen(env->value) + 2));
        tab[i] = my_strcat(env->name, "=");
        tab[i] = my_strcat(tab[i], env->value);
        env = env->next;
        i++;
    }
    tab[i] = NULL;
    return tab;
}
