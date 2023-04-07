/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** cd
*/

#include "mysh.h"
#include "unistd.h"
#include "sys/stat.h"

int my_strncmp(char const *s1, char const *s2, int n);
int my_strlen(char const *str);
char *get_env(env_t *env, char *find);

static int test_args(char **args)
{
    struct stat sb;

    stat(args[1], &sb);

    if (access(args[1], F_OK) == -1) {
        my_putstr(args[1]);
        my_putstr(": No such file or directory.\n");
        return (1);
    }

    if (S_ISDIR(sb.st_mode) == 0) {
        my_putstr(args[1]);
        my_putstr(": Not a directory.\n");
        return (1);
    }
    return (0);
}

static int go_home(mysh_t *mysh, env_t *env, char *home)
{
    char *pwd = get_env(env, "PWD");

    if (chdir(home) == -1) {
        my_putstr(home);
        my_putstr(": No such file or directory.\n");
        return (1);
    }
    func_setenv(mysh, env, &(parser_t){
        .cmd = "setenv", .args = (char *[]){"setenv", "PWD", home, NULL}});
    func_setenv(mysh, env, &(parser_t){
        .cmd = "setenv", .args = (char *[]){"setenv", "OLDPWD", pwd, NULL}});
    return (0);
}

static int chack_args(mysh_t *mysh, env_t *env , char **args)
{
    char *pwd = get_env(env, "PWD");
    char *oldpwd = get_env(env, "OLDPWD");
    if (args[1] == NULL || args[1][0] == '\0') {
        if (go_home(mysh, env, get_env(env, "HOME")) == 1)
            return (1);
        return (0);
    }
    if (chdir(oldpwd) == -1) {
        my_putstr(oldpwd); my_putstr(": No such file or directory.\n");
        return 0;
    }
    func_setenv(mysh, env, &(parser_t){
        .cmd = "setenv", .args = (char *[]){"setenv", "PWD", oldpwd, NULL}});
    func_setenv(mysh, env, &(parser_t){
        .cmd = "setenv", .args = (char *[]){"setenv", "OLDPWD", pwd, NULL}});
    return 0;
}

int func_cd(mysh_t *mysh, env_t *env, parser_t *parser)
{
    char **args = parser->args;
    if (args[1] == NULL || args[1][0] == '-' || args[1][0] == '\0') {
        chack_args(mysh, env, args); return (0);
    }
    if (test_args(args) == 1) return (1);
    char *buff = NULL; size_t size = 0; char *pwd = getcwd(buff, size);
    char **old_arg = malloc(sizeof(char *) * 3);
    old_arg[0] = "setenv"; old_arg[1] = "OLDPWD"; old_arg[2] = pwd;
    if (chdir(args[1]) == -1) {
        my_putstr(args[1]); my_putstr(": No such file or directory.\n");
        return (0);
    }
    func_setenv(mysh, env, &(parser_t){
        .cmd = "setenv", .args = (char *[]){"setenv", "OLDPWD", pwd, NULL}
    });
    pwd = getcwd(buff, size);
    func_setenv(mysh, env, &(parser_t){
        .cmd = "setenv", .args = (char *[]){"setenv", "PWD", pwd, NULL}
    });
    return (0);
}
