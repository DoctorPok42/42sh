/*
** EPITECH PROJECT, 2023
** mysh2
** File description:
** errors
*/

#include "mysh.h"
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int my_strlen(char const *str);

int error_handling(int status)
{
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGFPE) {
            write(2, "Floating exception", 19);
        } else {
            char *sig = strsignal(WTERMSIG(status));
            write(2, sig, my_strlen(sig));
        }
        if (WCOREDUMP(status))
            write(2, " (core dumped)", 15);
        write(2, "\n", 1);
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSTOPPED(status))
        return WSTOPSIG(status);
    return status;
}
