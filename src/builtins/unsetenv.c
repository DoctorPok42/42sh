/*
** EPITECH PROJECT, 2023
** mysh2
** File description:
** unsetenv
*/

#include "mysh.h"
#include "lists.h"

int my_strlen(char const *str);
char *my_strcat(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);

static int test(env_t *env, char *args)
{
    while (env->next->next != NULL) {
        if (my_strncmp(env->next->name, args, my_strlen(args)) == 0) {
            env->next = env->next->next;
            return (0);
        }
        env = env->next;
    }
}

int func_unsetenv(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    char **args = parser->args;
    int i = 1;
    if (env->next == NULL) {
        return (0);
    }
    if (args[1] == NULL) {
        my_putstr("unsetenv: Too few arguments.\n");
        return (0);
    }

    while (args[i] != NULL) {
        test(env, args[i]);
        i++;
    }

    return (0);
}
