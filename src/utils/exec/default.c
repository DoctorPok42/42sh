/*
** EPITECH PROJECT, 2023
** mysh2
** File description:
** default
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

int launch_default(env_t *env, parser_t *parser, int status)
{
    pid_t pid; char **path_slice = parsing_path(env);
    parser->cmd = check_pass(parser, path_slice);
    if ((pid = fork()) == -1) {
        perror("Fork failed. \n");
        free(path_slice); return -1;
    }
    if (pid == 0) {
        if (parser->cmd == NULL) {
            free(path_slice); return 127;
        }
        if ((status = execve(parser->cmd, parser->args, env_tab(env))) == -1) {
            perror(parser->cmd);
            free(path_slice); return -1;
        }
    }
    waitpid(pid, &status, WUNTRACED);
    status = error_handling(status);
    free(path_slice); return status;
    return status;
}
