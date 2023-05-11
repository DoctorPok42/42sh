/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** asign
*/

#include <string.h>
#include "mysh.h"
#include "prompt.h"

void assing_buffer_to_input(mysh_t *mysh, prompt_t *prompt)
{
    if (prompt->buffer != NULL) {
        mysh->input = strdup(prompt->buffer);
        free(prompt->buffer);
        prompt->buffer = NULL;
        free(prompt);
        return;
    } else {
        mysh->input = strdup("");
        free(prompt->buffer);
        prompt->buffer = NULL;
        free(prompt);
        return;
    }
}
