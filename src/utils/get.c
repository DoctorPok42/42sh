/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get
*/

#include "mysh.h"
#include "lists.h"

int my_strncmp(char const *s1, char const *s2, int n);
int my_strlen(char const *str);

char *get_env(env_t *env, char *find)
{
    char *char_find = NULL;

    for (int i = 0; env->next != NULL; i++) {
        if (my_strncmp(env->name, find, my_strlen(find)) == 0) {
            char_find = malloc(sizeof(char) * my_strlen(env->value));
            char_find = env->value;
            return char_find;
        }
        env = env->next;
    }
    return char_find;
}
