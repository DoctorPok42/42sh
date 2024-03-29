/*
** EPITECH PROJECT, 2022
** my_put_nbr
** File description:
** 03
*/

#include <unistd.h>

void my_putchar(char c);

void my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb > 9) {
        my_put_nbr(nb / 10);
        my_put_nbr(nb % 10);
    } else {
        my_putchar((nb + '0'));
    }
}
