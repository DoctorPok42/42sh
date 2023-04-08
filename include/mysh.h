/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** 42sh
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <stdlib.h>
    #include <stdbool.h>
    #include "lists.h"

void my_putstr(char const *str);

typedef struct mysh_s {
    char **env;
    char *pwd;
    int status;
    int exit;
    bool no_env;
    char *github;
} mysh_t;

int func_cd(mysh_t *mysh, env_t *env, parser_t *parser);
int func_setenv(mysh_t *mysh, env_t *env, parser_t *parser);
int func_unsetenv(mysh_t *mysh, env_t *env, parser_t *parser);
int func_env(mysh_t *mysh, env_t *env, parser_t *parser);
int func_alias(mysh_t *mysh, env_t *env, parser_t *parser);
int func_unalias(mysh_t *mysh, env_t *env, parser_t *parser);
int func_history(mysh_t *mysh, env_t *env, parser_t *parser);
int func_exit(mysh_t *mysh, env_t *env, parser_t *parser);

typedef struct list_flags_s {
    char const *flags;
    int (*function)(mysh_t *mysh, env_t *env, parser_t *parser);
} flags;

static const flags FLAGS[] = {
    {flags : "cd", function : &func_cd},
    {flags : "setenv", function : &func_setenv},
    {flags : "unsetenv", function : &func_unsetenv},
    {flags : "env", function : &func_env},
    {flags : "alias", function : &func_alias},
    {flags : "unalias", function : &func_unalias},
    {flags : "history", function : &func_history},
    {flags : "exit", function : &func_exit},
    {flags : NULL, function : NULL}};

#endif // MYSH_H
