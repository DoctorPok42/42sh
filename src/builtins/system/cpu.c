/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** cpu
*/

#include <stdio.h>
#include <string.h>
#include "mysh.h"

int func_cpu(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    (void) env;
    (void) parser;

    FILE *fp;
    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", "/proc/cpuinfo");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "model name"))
            printf("%s", line);
        if (strstr(line, "cpu MHz"))
            printf("%s", line);
    }
    fclose(fp);
    return (0);
}
