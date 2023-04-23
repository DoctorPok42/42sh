/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** memory
*/

#include <stdio.h>
#include <string.h>
#include "mysh.h"

int func_memory(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh; (void) env; (void) parser;
    FILE *fp; char line[256];
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier proc/meminfo");
        return -1;
    }
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "MemTotal"))
            printf("%s", line);
        if (strstr(line, "MemFree"))
            printf("%s", line);
        if (strstr(line, "MemAvailable"))
            printf("%s", line);
        if (strstr(line, "Buffers"))
            printf("%s", line);
        if (strstr(line, "Cached"))
            printf("%s", line);
    }
    fclose(fp); return (0);
}
