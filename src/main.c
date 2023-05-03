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

int main(int ac, char **av, char **env)
{
    (void) ac; (void) av;
    mysh_t *mysh = malloc(sizeof(mysh_t));
    env_t *env_list = malloc(sizeof(env_t)); mysh->status = 0;
    if (env[0] != NULL) {
        put_in_env(env, env_list);
    } else {
        env_list->name = NULL; env_list->value = NULL; env_list->next = NULL;
        mysh->no_env = true;
    }

    while (mysh->status != -42) {
        mysh->status = mysh_loop(mysh, env_list);
        if (mysh->status != -42 && mysh->input != NULL &&
            mysh->input[0] != '\n')
            put_in_history(mysh);
    }

    my_putstr("exit\n");
    free (mysh);
    return 0;
}
