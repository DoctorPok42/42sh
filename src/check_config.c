/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_config
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "mysh.h"

char *get_env(env_t *env, char *find);
char *my_strcat(char *dest, char const *src);

void check_config(mysh_t *mysh, env_t *env_list)
{
    char *home = get_env(env_list, "HOME");
    char *path = my_strcat(home, "/.cache/42sh\0");
    char *history = my_strcat(path, "/.history\0");
    char *alias = my_strcat(path, "/.alias\0");

    if (access(path, F_OK) == -1) {
        mkdir(path, 0777);
    }

    if (access(history, F_OK) == -1) {
        int fd = open(history, O_CREAT, 0777);
        close(fd);
    }

    if (access(alias, F_OK) == -1) {
        int fd = open(alias, O_CREAT, 0777);
        close(fd);
    }
    mysh->history = history;
    mysh->alias = alias;
}
