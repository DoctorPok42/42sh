/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** main
*/

#include <unistd.h>
#include "mysh.h"
#include "lists.h"

int put_in_history(mysh_t *mysh);
int mysh_loop(mysh_t *mysh, env_t *env_list);
char *my_strcat(char *dest, char const *src);
env_t *put_in_env(char **tab, env_t *env_list);
void check_config(mysh_t *mysh, env_t *env_list);
void free_struct(mysh_t *mysh, env_t *env_list);

void launch_shell(mysh_t *mysh, env_t *env_list)
{
    while (mysh->status != -42 && mysh->status != -84) {
        mysh->status = mysh_loop(mysh, env_list);
        if (mysh->status != -42 && mysh->input != NULL &&
            mysh->input[0] != '\n' && mysh->input[0] != '\0')
            put_in_history(mysh);
    }
}

void init_struct(mysh_t *mysh)
{
    mysh->status = 0;
    mysh->github = NULL;
    mysh->input = NULL;
}

int main(int ac, char **av, char **env)
{
    (void) ac; (void) av;
    mysh_t *mysh = malloc(sizeof(mysh_t));
    env_t *env_list = malloc(sizeof(env_t));
    if (env[0] != NULL) {
        mysh->no_env = false;
        put_in_env(env, env_list);
    } else {
        env_list->name = NULL; env_list->value = NULL; env_list->next = NULL;
        mysh->no_env = true;
    }

    init_struct(mysh);

    if (mysh->no_env == false)
        check_config(mysh, env_list);
    launch_shell(mysh, env_list);
    if (mysh->status == -42)
        my_putstr("exit\n");
    free_struct(mysh, env_list);
    return 0;
}
