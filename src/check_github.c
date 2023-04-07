/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_github
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "mysh.h"

void check_github(mysh_t *mysh)
{
    struct stat st = {0};
    size_t size = 0;
    if (stat(".git/", &st) == -1) {
        mysh->github = "\0";
        return;
    }
    FILE *fd = fopen(".git/HEAD", "r");
    if (fd == NULL) {
        mysh->github = "\0";
        return;
    }
    getline(&mysh->github, &size, fd);
    fclose(fd);
    mysh->github[strlen(mysh->github) - 1] = '\0';
    mysh->github = mysh->github + 16;
}
