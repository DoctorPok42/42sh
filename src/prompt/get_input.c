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

int get_number_of_line(mysh_t *mysh);
void get_key(mysh_t *mysh, prompt_t *prompt, char caract);
void assing_buffer_to_input(mysh_t *mysh, prompt_t *prompt);
void display_prompt(mysh_t *mysh, env_t *env);

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

void delete_key(prompt_t *prompt)
{
    int selected = 0;
    if (prompt->position < strlen(prompt->buffer)) {
        memmove(&prompt->buffer[prompt->position],
                &prompt->buffer[prompt->position + 1],
                strlen(prompt->buffer) - prompt->position);

        printf("\033[K");
        fflush(stdout);

        selected = strlen(prompt->buffer) - prompt->position;

        for (size_t i = prompt->position; i < strlen(prompt->buffer); i++) {
            printf("%c", prompt->buffer[i]);
            fflush(stdout);
        }

        printf(" ");
        printf("\033[%dD", selected + 1);
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
    if (c < 32 || c > 126) return;
    prompt->buffer[prompt->position++] = c;
    if (diff == 0) write(1, &c, 1);
    if (diff > 0) {
        printf("%s", prompt->buffer + prompt->position - 1); fflush(stdout);
        for (int i = 0; i < diff; i++) {
            printf("\b"); fflush(stdout); prompt->position++;
        }
    }
    diff = 0;
}

void loop(mysh_t *mysh, prompt_t *prompt, env_t *env)
{
    while (1) {
        char c; int diff = 0; read(STDIN_FILENO, &c, 1);
        switch (c) {
            case 4: mysh->status = -42; return;
            case '\x0C':
                printf("\033[2J\033[1;1H"); fflush(stdout);
                display_prompt(mysh, env); printf("%s", prompt->buffer);
                fflush(stdout); break;
            case '\n': return;
            case 127:
            case '\b':
                back_space_key(prompt); break;
            case '\e':
                if (read(STDIN_FILENO, &c, 1) == -1) break;
                if (read(STDIN_FILENO, &c, 1) == -1) break;
                get_key(mysh, prompt, c); break;
            default:
                write_caract(prompt, c, diff); break;
        }
    }
}

void get_input(mysh_t *mysh, env_t *env)
{
    struct termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 1; new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    prompt_t *prompt = malloc(sizeof(prompt_t));
    prompt->size = 256;
    prompt->buffer = malloc(sizeof(char) * prompt->size + 1);
    for (long unsigned i = 0; i < prompt->size; i++)
        prompt->buffer[i] = '\0';
    prompt->position = 0;
    prompt->history = get_number_of_line(mysh) + 1;
    loop(mysh, prompt, env);
    assing_buffer_to_input(mysh, prompt);
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
