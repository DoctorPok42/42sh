/*
** EPITECH PROJECT, 2022
** my_str_isalpha
** File description:
** 22
*/

int my_str_isalpha(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < 'a' || str[i] > 'z') &&
            (str[i] < '0' || str[i] > '9')) {
            return 1;
        }
    }
    return 0;
}

int my_caract_isalpha(char const str)
{
    if ((str < 'A' || str > 'Z') &&
        (str < 'a' || str > 'z')) {
        return 1;
    }
    return 0;
}
