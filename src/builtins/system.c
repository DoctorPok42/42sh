/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** system
*/

#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mysh.h"

int func_help(mysh_t *mysh, env_t *env, parser_t *parser);
int func_battery(mysh_t *mysh, env_t *env, parser_t *parser);
int func_cpu(mysh_t *mysh, env_t *env, parser_t *parser);
int func_memory(mysh_t *mysh, env_t *env, parser_t *parser);
int func_network(mysh_t *mysh, env_t *env, parser_t *parser);

int launch_args(char **args)
{
    char *args_name[] = {"-h", "--help", "-b", "--battery", "-c", "--cpu",
        "-m", "--memory", "-n", "--network", NULL};
    int (*args_func[])(mysh_t *mysh, env_t *env, parser_t *parser) = {
        &func_help, &func_help,
        &func_battery, &func_battery,
        &func_cpu, &func_cpu,
        &func_memory, &func_memory,
        &func_network, &func_network
        };

    for (int i = 0; args_name[i] != NULL; i++)
        if (strcmp(args[1], args_name[i]) == 0)
            return (args_func[i](NULL, NULL, NULL));
    return (1);
}

int func_system(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    (void) env;
    struct stat st;
    if (parser->args[1] != NULL) {
        if (launch_args(parser->args) != 0)
            return (84);
        return (0);
    }
    if (stat("/sys/class/power_supply/BAT0", &st) == -1)
        return (84);
    system("echo -n \"Battery: \"; \
        cat -s /sys/class/power_supply/BAT0/capacity");
    system("echo -n \"CPU: \"; \
        cat -s /proc/cpuinfo | grep \"model name\" | head -n 1 | cut -d \":\" \
        -f 2");
    system("echo -n \"Memory: \"; \
        cat -s /proc/meminfo | grep \"MemTotal\" | cut -d \":\" -f 2");
    system("echo -n \"Network: \n\"; \
        cat -s /proc/net/protocols | egrep \"TCPv6|UDP\" | cut -d \":\" -f 2");
    return (0);
}
