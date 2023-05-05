/*
** EPITECH PROJECT, 2023
** 42
** File description:
** prompt
*/

#ifndef PROMPT_H_
    #define PROMPT_H_

    #include <stdlib.h>

    typedef struct {
        size_t size;
        size_t position;
        char *buffer;
        int history;
    } prompt_t;

#endif /* !PROMPT_H_ */
