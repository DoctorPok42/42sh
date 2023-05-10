/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias
*/

#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "mysh.h"
#include "lists.h"

char **my_str_to_word_array(char *str, char const separator);
int my_tablen(char **tab);

int fp_check(FILE *fp)
{
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", "config/alias.txt");
        return -1;
    }
    return 0;
}

static char *check_array(char **array, char **alias_array, int i, int fd)
{
    if (strncmp(alias_array[0], array[i], strlen(alias_array[0])) == 0) {
        char *eq_pos = strchr(array[i], ' ');
        if (eq_pos != NULL) {
            char *cmd = eq_pos + 1;
            close(fd);
            return cmd;
        }
    }
    return NULL;
}

char *check_alias(mysh_t *mysh,
    env_t __attribute__((unused))*env, __attribute__((unused))parser_t *parser)
{
    int len = 0;
    char *cmd = NULL;
    char **array = NULL;
    struct stat st;
    stat("config/alias.txt", &st);
    char *buffer = malloc(sizeof(char) * (st.st_size) + 1);
    int fd = open("config/alias.txt", O_RDONLY);
    char **alias_array = my_str_to_word_array(mysh->input, '\n');
    read(fd, buffer, st.st_size);
    buffer[st.st_size] = '\0';
    array = my_str_to_word_array(buffer, '\n');
    for (; array[len][0] != '\0'; len += 1);
    for (int i = len - 1; i >= 0; i -= 1) {
        if ((cmd = check_array(array, alias_array, i, fd)) != NULL) {
            return cmd;
        }
    }
    close(fd);
    return NULL;
}

static int single_alias(mysh_t *mysh, parser_t *parser)
{
    struct stat st;
    stat("config/alias.txt", &st);
    char *buffer = malloc(sizeof(char) * (st.st_size) + 1);
    int fd = open("config/alias.txt", O_RDONLY);
    char *alias = strdup(mysh->input);
    read(fd, buffer, st.st_size);
    buffer[st.st_size] = '\0';
    if (strncmp(alias, "alias\n", 5) == 0 && my_tablen(parser->args) == 1) {
        printf("%s\n", buffer);
        return 0;
    }
    return 1;
}

int func_alias(mysh_t *mysh,
    env_t __attribute__((unused))*env, parser_t *parser)
{
    FILE *fp;
    fp = fopen("config/alias.txt", "r");
    fp_check(fp);
    if (single_alias(mysh, parser) == 0)
        return 0;
    fclose(fp);
    fp = fopen("config/alias.txt", "a");
    fp_check(fp);
    for (int i = 1; parser->args[i] != NULL; i++) {
        fprintf(fp, "%s", parser->args[i]);
        if (parser->args[i + 1] != NULL)
            fprintf(fp, " ");
    }
    fprintf(fp, "\n");
    fclose(fp);
    return (0);
}
