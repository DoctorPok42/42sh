/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** network
*/

#include <stdio.h>
#include <string.h>
#include "mysh.h"

int func_network(mysh_t *mysh, env_t *env, parser_t *parser)
{
    (void) mysh;
    (void) env;
    (void) parser;

    system("echo \"Ip address: \" && ip addr | grep inet | grep -v inet6 | \
        grep -v ' 127.' | cut -d ' ' -f 6 | cut -d '/' -f 1");
    system("echo \"Mac address: \" && ip addr | grep ether | cut -d ' ' -f 6");
    system("echo \"-----------------------\"");
    system("cat /proc/net/dev");
    return (0);
}
