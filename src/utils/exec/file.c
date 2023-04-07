/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** pipe
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "mysh.h"
#include "lists.h"

char **env_tab(env_t *env);
int error_handling(int status);
char **parsing_path(env_t *env);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *check_pass(parser_t *parser, char **path_slice);

static int launch_second_process(env_t *env, parser_t *parser, int link[2],
    char **path_slice)
{
    pid_t pid2; int status = 0;
    if ((pid2 = fork()) == -1) {
        perror("Fork failed. \n"); return 2;
    }
    if (pid2 == 0) {
        parser->cmd = check_pass(parser, path_slice);
        if (parser->cmd == NULL) return 1;
        if ((link[1] = open(parser->next->next->cmd, O_RDONLY)) < 0) {
            perror(parser->next->next->cmd); return 1;
        }
        dup2(link[1], STDIN_FILENO); close(link[1]);

        if ((status = execve(parser->cmd, parser->args, env_tab(env))) == -1) {
            perror(parser->cmd); return status;
        }
    }
    close(link[0]); close(link[1]);
    waitpid(pid2, &status, WUNTRACED);
    status = error_handling(status);
    return status;
}

int launch_file(env_t *env, parser_t *parser, int status)
{
    if (parser->next->next == NULL || parser->next->next->cmd == NULL ||
        parser->next->next->cmd[0] == '\0' ||
        parser->next->next->cmd[0] == ' ') {
        my_putstr("Invalid null command.\n"); return 1;
    }
    int link[2]; char **path_slice =
        parsing_path(env);

    if (pipe(link) == -1) {
        perror("Pipe failed. \n"); return 1;
    }

    status = launch_second_process(env, parser, link, path_slice);
    close(link[0]);
    close(link[1]);
    return status;
}
