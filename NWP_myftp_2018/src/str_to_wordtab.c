/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** str_to_wordtab.c
*/

#include "my.h"


static int char_size(char *str, char separator, int *pos)
{
    int len = 0;

    for (int i = 0; str[i] != '\0' && str[i] != separator; i++)
        len++;
    *pos = 0;
    return (len);
}

static int line_size(char *str, char spr)
{
    int i = 0;
    int line = 0;

    while (str[i] == spr)
        i++;
    while (str[i]) {
        if (str[i] == spr) {
            line++;
            while (str[i] == spr)
                i++;
            continue;
        }
        i++;
    }
    return (line);
}

char **my_str_to_wordtab(char *str, char separator)
{
    int x = 0;
    int y = 0;
    char **tab = malloc(sizeof(char *) * (line_size(str, separator) + 2));

    if (!tab)
        exit(84);
    for (int i = 0; str[i]; ) {
        tab[x] = malloc(sizeof(char) * (char_size(&str[i], separator, &y) + 1));
        if (!tab[x])
            exit(84);
        while (str[i] != '\0' && str[i] != separator)
            tab[x][y++] = str[i++];
        if (str[i] == separator)
            while (str[++i] == separator);
        tab[x++][y] = '\0';
    }
    tab[x] = NULL;
    return (tab);
}
