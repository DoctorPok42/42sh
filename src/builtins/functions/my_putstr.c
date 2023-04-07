/*
** EPITECH PROJECT, 2022
** my_putstr
** File description:
** 05
*/

#include <unistd.h>

void my_putstr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        write(1, &str[i], 1);
    }
}
