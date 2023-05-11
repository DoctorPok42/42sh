/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** free_struct
*/

#include "mysh.h"
#include "lists.h"

void free_env(env_t *env_list)
{
    env_t *tmp = env_list;
    env_t *next = NULL;

    while (tmp->next != NULL) {
        next = tmp->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
        tmp = next;
    }
}

void free_struct(mysh_t *mysh, env_t *env_list)
{
    free(mysh->input);
    free(mysh->history);
    free(mysh->alias);
    free(mysh);
    free_env(env_list);
}
