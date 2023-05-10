/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** arrows
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mysh.h"
#include "prompt.h"

char *search_in_history(int nb);
int get_number_of_line(void);
int my_strlen(char *str);
void delete_key(prompt_t *prompt);

void erase_line(prompt_t *prompt)
{
    for (size_t i = 0; i < prompt->position; i++) {
        printf("\b \b");
        fflush(stdout);
    }
    prompt->position = 0;
}

void move_cursor(prompt_t *prompt, char caract)
{
    if (caract == 'C' && prompt->position < strlen(prompt->buffer)) {
        printf("\033[1C");
        fflush(stdout);
        prompt->position++;
    }
    if (caract == 'D' && prompt->position > 0) {
        printf("\b");
        fflush(stdout);
        prompt->position--;
    }
}

void navigate_in_history_top(prompt_t *prompt)
{
    if (prompt->history > 0) {
        prompt->history--;
        erase_line(prompt);
        prompt->buffer = search_in_history(prompt->history);
        if (prompt->buffer == NULL) {
            prompt->history = 0;
            fflush(stdout);
            return;
        }
        prompt->position = strlen(prompt->buffer);
        printf("%s", prompt->buffer);
        fflush(stdout);
    }
}

void navigate_in_history_bottom(prompt_t *prompt)
{
    if (prompt->history <= get_number_of_line()) {
        prompt->history++;
        erase_line(prompt);
        prompt->buffer = search_in_history(prompt->history);
        if (prompt->buffer == NULL) {
            prompt->history = get_number_of_line() + 1;
            fflush(stdout);
            return;
        }
        prompt->position = strlen(prompt->buffer);
        printf("%s", prompt->buffer);
        fflush(stdout);
    }
}

void get_key(prompt_t *prompt, char caract)
{
    switch (caract) {
        case 'A':
            navigate_in_history_top(prompt);
            break;
        case 'B':
            navigate_in_history_bottom(prompt);
            break;
        case 'C':
        case 'D':
            move_cursor(prompt, caract);
            break;
        case '3':
            if (read(0, &caract, 1) == 1 && caract == '~')
                delete_key(prompt);
            break;
    }
}
