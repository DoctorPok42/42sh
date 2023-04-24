/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** pipe
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"
#include "lists.h"
#include <stdlib.h>

char **env_tab(env_t *env);
int error_handling(int status);
char **parsing_path(env_t *env);
char *check_pass(parser_t *parser, char **path_slice);

static int launch_second_process(env_t *env, parser_t *parser, int link[2],
    char **path_slice)
{
    parser->next->next->cmd = check_pass(parser->next->next, path_slice);
    if (parser->next->next->cmd == NULL) return 1;
    pid_t pid2; int status = 0;
    if ((pid2 = fork()) == -1) {
        perror("Fork failed. \n"); return 2;
    }
    if (pid2 == 0) {
        dup2(link[0], STDIN_FILENO); close(link[0]); close(link[1]);
        if ((status = execve(parser->next->next->cmd, parser->next->next->args,
            env_tab(env))) == -1) {
            perror(parser->next->next->cmd); return status;
        }
    }
    close(link[0]); close(link[1]);
    waitpid(pid2, &status, WUNTRACED);
    status = error_handling(status);
    return status;
}

int launch_pipe(env_t *env, parser_t *parser, int status)
{
    if (parser->next->next == NULL || parser->next->next->cmd == NULL ||
        parser->next->next->cmd[0] == '\0' ||
        parser->next->next->cmd[0] == ' ') {
        my_putstr("Invalid null command.\n"); return 1;
    } int link[2]; pid_t pid1; char **path_slice =
        parsing_path(env); parser->cmd = check_pass(parser, path_slice);
    if (parser->cmd == NULL) return 1;
    if (pipe(link) == -1) { perror("Pipe failed. \n"); return 1;
    }
    if ((pid1 = fork()) == -1) { perror("Fork failed. \n"); return 2;
    }
    if (pid1 == 0) {
        dup2(link[1], STDOUT_FILENO); close(link[0]); close(link[1]);
        if ((status = execve(parser->cmd, parser->args, env_tab(env))) == -1) {
            perror(parser->cmd); return status;
        }
    }
    status = launch_second_process(env, parser, link, path_slice);
    close(link[0]); close(link[1]); waitpid(pid1, &status, WUNTRACED);
    status = error_handling(status); return status;
}
