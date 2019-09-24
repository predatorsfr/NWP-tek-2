/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** main.c
*/

#include "my.h"

int main(int ac, char **av)
{
    char *er1 = "USAGE: ./myftp port path";
    char *er2 = "port is the port number on which the server socket listens";
    char *er3 = "path is the path to the home directory for the Anonymous user";
    t_myftp st;

    if (ac != 3 || strcmp(av[1], "-help") == 0) {
        fprintf(stderr, "%s\n\t%s\n\t%s\n", er1, er2, er3 );
	return (84);
    } else {
        if (!serv(av, &st))
            return (84);
        else if (!client(&st))
            return (84);
        if (close(st.fd) == -1)
            return (84);
    }
    return (0);
}
