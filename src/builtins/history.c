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

int my_strlen(char const *str);

int put_in_history(mysh_t *mysh)
{
    FILE *fp; char line[256]; int last_num = 0;
    fp = fopen(mysh->history, "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", mysh->history);
        return -1;
    }
    while (fgets(line, sizeof(line), fp)) {
        int num;
        if (sscanf(line, "%d", &num) == 1) {
            last_num = num;
        }
    }
    fclose(fp);
    fp = fopen(mysh->history, "a");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", mysh->history);
        return -1;
    }
    fprintf(fp, "%d %s\n", last_num + 1, mysh->input); fclose(fp);
    return (0);
}

int func_history(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    (void) env;
    (void) parser;

    struct stat st;
    if (stat(mysh->history, &st) == -1) {
        printf("Erreur d'ouverture du fichier %s\n", mysh->history);
        return -1;
    }
    int fd = open(mysh->history, O_RDONLY);

    char *buffer = malloc(sizeof(char) * st.st_size + 1);
    read(fd, buffer, st.st_size);
    buffer[st.st_size] = '\0';

    printf("%s", buffer);

    free(buffer);
    close(fd);
    return (0);
}

char *format_return(char *str)
{
    int i = 0;
    int j = 0;
    int separator = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            separator = i;
            break;
        }
    }
    char *new_str = malloc(sizeof(char) * my_strlen(str) - (separator + 1));
    for (i = separator + 1; str[i] != '\0'; i++) {
        new_str[j] = str[i];
        j++;
    }
    new_str[my_strlen(str) - (separator + 2)] = '\0';
    return (new_str);
}

char *search_in_history(mysh_t *mysh, int nb)
{
    FILE *fp; char line[256];
    fp = fopen(mysh->history, "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", mysh->history);
        return NULL;
    }
    while (fgets(line, sizeof(line), fp)) {
        int num;
        if (sscanf(line, "%d", &num) == 1 && num == nb) {
            fclose(fp);
            return (format_return(line));
        }
    }
    fclose(fp);
    return NULL;
}

int get_number_of_line(mysh_t *mysh)
{
    FILE *fp; char line[256]; int last_num = 0;
    fp = fopen(mysh->history, "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", mysh->history);
        return -1;
    }
    while (fgets(line, sizeof(line), fp)) {
        int num;
        if (sscanf(line, "%d", &num) == 1) {
            last_num = num;
        }
    }
    fclose(fp);
    return (last_num);
}
