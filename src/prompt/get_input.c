/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_input
*/

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "mysh.h"
#include "prompt.h"

int get_number_of_line(void);
void get_key(prompt_t *prompt, char caract);

void back_space_key(prompt_t *prompt)
{
    int selected = 0;
    if (prompt->position > 0) {
        memmove(&prompt->buffer[prompt->position - 1],
            &prompt->buffer[prompt->position],
            strlen(prompt->buffer) - prompt->position + 1);

        prompt->position--;
        printf("\033[D");
        printf("\033[K");
        fflush(stdout);

        selected = strlen(prompt->buffer) - prompt->position;

        for (size_t i = prompt->position; i < strlen(prompt->buffer); i++) {
            printf("%c", prompt->buffer[i]);
            fflush(stdout);
        }
        printf("\033[%dD", selected);
        fflush(stdout);
    }
}

void write_caract(prompt_t *prompt, char c, int diff)
{
    if (prompt->position == prompt->size - 1) {
        prompt->size *= 2;
        prompt->buffer = realloc(prompt->buffer, prompt->size);
    }
    if (prompt->position < strlen(prompt->buffer)) {
        diff = strlen(prompt->buffer) - prompt->position;
        memmove(prompt->buffer + prompt->position + 1,
                prompt->buffer + prompt->position,
                prompt->size - prompt->position);
    }
    prompt->buffer[prompt->position++] = c;
    if (diff == 0) {
        putchar(c); fflush(stdout);
    } if (diff > 0) {
        printf("%s", prompt->buffer + prompt->position - 1); fflush(stdout);
        for (int i = 0; i < diff; i++) {
            printf("\b"); fflush(stdout); prompt->position++;
        }
    }
    diff = 0;
}

void loop(mysh_t *mysh, prompt_t *prompt)
{
    while (1) {
        char c;
        int diff = 0;
        read(STDIN_FILENO, &c, 1);
        switch (c) {
            case 4:
                mysh->status = -42; return;
            case '\n':
                return;
            case 127:
            case '\b':
                back_space_key(prompt); break;
            case '\e':
                if (read(STDIN_FILENO, &c, 1) == -1) break;
                if (read(STDIN_FILENO, &c, 1) == -1) break;
                get_key(prompt, c); break;
            default:
                write_caract(prompt, c, diff); break;
        }
    }
}

void get_input(mysh_t *mysh)
{
    struct termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 1; new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    prompt_t *prompt = malloc(sizeof(prompt_t));
    prompt->size = 256;
    prompt->buffer = malloc(sizeof(char) * prompt->size);
    for (long unsigned i = 0; i < prompt->size; i++)
        prompt->buffer[i] = '\0';
    prompt->position = 0;
    prompt->history = get_number_of_line() + 1;
    loop(mysh, prompt);
    mysh->input = strdup(prompt->buffer);
    free(prompt->buffer);
    free(prompt);
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
