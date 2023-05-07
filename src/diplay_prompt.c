/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "mysh.h"

int my_strlen(char const *src);
char *get_env(env_t *env, char *find);
void check_github(mysh_t *mysh);
void my_put_nbr(int nb);

void display_directory(mysh_t *mysh, env_t *env)
{
    if (mysh->no_env == true)
        return;
    char *directory = getcwd(NULL, 0);
    if (strcmp(directory, get_env(env, "HOME")) == 0) {
        my_putstr("~");
        return;
    }
    int separator = 0;
    for (int i = 0; directory[i] != '\0'; i++) {
        if (directory[i] == '/')
            separator = i;
    }
    my_putstr(&directory[separator + 1]);
    free(directory);
}

void check_status(mysh_t *mysh)
{
    check_github(mysh);
    if (mysh->status == 0) {
        my_putstr("\033[32;1m ✔ \033[44;1m\033[37;1m");
    } else {
        my_putstr("\033[31;1m ✘ ");
        my_put_nbr(mysh->status);
        my_putstr(" \033[44;1m\033[37;1m");
    }
}

int display_prompt(mysh_t *mysh, env_t *env)
{
    my_putstr("\033[44;1m");
    check_status(mysh);
    display_directory(mysh, env);
    if (mysh->github[0] != '\0') {
            my_putstr("\033[49m\033[33;1m git:(\033[32;1m");
            my_putstr(mysh->github);
            my_putstr("\033[33;1m) >\033[37;0m ");
    } else
        printf("\033[0m\033[33;1m\033[49m >\033[37;0m ");
    return (0);
}
