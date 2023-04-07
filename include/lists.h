/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** lists
*/

#ifndef LISTS_H
    #define LISTS_H

typedef struct parser_s {
    char *cmd;
    char **args;
    struct parser_s *next;
} parser_t;

typedef struct env_s {
    char *name;
    char *value;
    struct env_s *next;
} env_t;

#endif // LISTS_H
