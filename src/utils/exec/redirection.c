/*
** EPITECH PROJECT, 2023
** mysh2
** File description:
** reedirections
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"
#include "lists.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int my_strlen(char *str);
char **env_tab(env_t *env);
int error_handling(int status);
char **parsing_path(env_t *env);
int my_strcmp(char const *s1, char const *s2);
char *check_pass(parser_t *parser, char **path_slice);

int write_in_file(parser_t *parser, char *buff, int *link)
{
    int fd;
    struct stat st;
    read(link[0], buff, 4096);
    if (stat(parser->next->cmd, &st) == -1) {
        fd = open(parser->next->cmd, O_WRONLY | O_CREAT, S_IRWXU);
    }

    if (my_strcmp(parser->cmd, ">>") == 0) {
        fd = open(parser->next->cmd, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
    } else {
        fd = open(parser->next->cmd, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    }

    if (write(fd,  buff, my_strlen(buff)) == -1) {
        perror("Write failed. \n"); return 1;
    }

    close(fd);
    return 0;
}

int launch_redirection(env_t *env, parser_t *parser, int status)
{
    (void)(env); int link[2]; pid_t pid1; char buff[4096];
    if (parser->next->next == NULL || parser->next->next->cmd == NULL ||
        parser->next->next->cmd[0] == '\0' ||
        parser->next->next->cmd[0] == ' ') {
        my_putstr("Invalid null command.\n"); return 1;
    } char **path_slice = parsing_path(env);
    parser->cmd = check_pass(parser, path_slice);
    if (parser->cmd == NULL) return 1;
    if (pipe(link) == -1) { perror("Pipe failed. \n"); return 1;
    }
    if ((pid1 = fork()) == -1) { perror("Fork failed. \n"); return 2;
    } if (pid1 == 0) {
        dup2(link[1], STDOUT_FILENO); close(link[0]);
        if ((status = execve(parser->cmd, parser->args, env_tab(env))) == -1) {
            perror(parser->cmd); return status;
        }
    }
    waitpid(pid1, &status, WUNTRACED);
    if (write_in_file(parser->next, buff, link) != 0) return 1;
    free(path_slice); status = error_handling(status); return status;
}
