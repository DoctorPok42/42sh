/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mysh.h"
#include "lists.h"

int put_in_history(mysh_t *mysh)
{
    FILE *fp; char line[256]; int last_num = 0;
    fp = fopen("config/history.txt", "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", "config/history.txt");
        return -1;
    }
    while (fgets(line, sizeof(line), fp)) {
        int num;
        if (sscanf(line, "%d", &num) == 1) {
            last_num = num;
        }
    }
    fclose(fp);
    fp = fopen("config/history.txt", "a");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", "config/history.txt");
        return -1;
    }
    fprintf(fp, "%d %s", last_num + 1, mysh->input); fclose(fp);
    return (0);
}

int func_history(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    (void) env;
    (void) parser;

    struct stat st;
    if (stat("config/history.txt", &st) == -1) {
        printf("Erreur d'ouverture du fichier %s\n", "config/history.txt");
        return -1;
    }
    int fd = open("config/history.txt", O_RDONLY);

    char *buffer = malloc(sizeof(char) * st.st_size + 1);
    read(fd, buffer, st.st_size);
    buffer[st.st_size] = '\0';

    printf("%s", buffer);

    free(buffer);
    close(fd);
    return (0);
}
