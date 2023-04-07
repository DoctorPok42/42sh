/*
** EPITECH PROJECT, 2023
** mysh2
** File description:
** setenv
*/

#include "mysh.h"

int my_tablen(char **tab);
int my_strlen(char const *str);
int my_str_isalpha(char const *str);
int my_caract_isalpha(char const str);
int func_env(mysh_t *mysh, env_t *env, parser_t *parser);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);

static env_t *last_env(env_t *env)
{
    while (env->next != NULL)
        env = env->next;
    return env;
}

static int error(parser_t *parser)
{
    if (my_tablen(parser->args) > 3) {
        my_putstr("setenv: Too many arguments.\n");
        return -1;
    }

    if (parser->args[1] != NULL && (parser->args[1][0] >= '0' &&
        parser->args[1][0] <= '9' ||
        my_caract_isalpha(parser->args[1][0])) != 0) {
        my_putstr("setenv: Variable name must begin with a letter.\n");
        return -1;
    }

    if (parser->args[1] != NULL && my_str_isalpha(parser->args[1]) != 0) {
        my_putstr("setenv: Variable name must contain alphanumeric");
        my_putstr(" characters.\n");
        return -1;
    }

    return 0;
}

static int check_env(env_t *env, char **args)
{
    char *tmp = NULL;
    char *tmp2 = NULL;
    while (env->next != NULL) {
        tmp = my_strcat(env->name, "=");
        tmp = my_strcat(tmp, env->value);
        if (my_strncmp(tmp, args[1], my_strlen(args[1])) == 0 &&
            args[2] != NULL) {
                tmp2 = malloc(sizeof(char) * (my_strlen(args[2]) + 1));
                tmp2 = args[2];
                env->value = tmp2;
                return (0);
        } if (my_strncmp(tmp, args[1], my_strlen(args[1])) == 0 &&
            args[2] == NULL) {
            env->value = "";
            return 0;
        }
        free(tmp);
        env = env->next;
    }
    return 1;
}

int func_setenv(mysh_t *mysh, env_t *env, parser_t *parser)
{
    if (error(parser) != 0) return -1;
    if (parser->args[1] == NULL) {
        func_env(mysh, env, parser); return 0;
    }
    if (env->next != NULL && check_env(env, parser->args) == 0) return 0;
    if (env->next != NULL) {
        env = last_env(env);
        env->name = parser->args[1];
        if (parser->args[2] != NULL) {
            env->value = parser->args[2];
        } else
            env->value = "";
        env->next = malloc(sizeof(env_t));
    } else {
        env->name = parser->args[1];
        if (parser->args[2] != NULL) {
            env->value = parser->args[2];
        } else
            env->value = "";
    } return 0;
}
