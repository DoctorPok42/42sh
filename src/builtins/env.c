/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** env
*/

#include "mysh.h"
#include "lists.h"

int func_env(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    (void) parser;
    for (int i = 0; env->next != NULL; i++) {
        my_putstr(env->name);
        my_putstr("=");
        my_putstr(env->value);
        my_putstr("\n");
        env = env->next;
    }
    return (0);
}
