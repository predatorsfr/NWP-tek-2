/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** serv.c
*/

#include "my.h"

bool serv(char **av, t_myftp *st)
{
    struct protoent *p = getprotobyname("TCP");
    struct sockaddr_in src_in;

    if (!p)
	return (false);
    src_in.sin_family = AF_INET;
    src_in.sin_port = htons(atoi(av[1]));
    src_in.sin_addr.s_addr = INADDR_ANY;
    if ((st->fd = socket(AF_INET, SOCK_STREAM, p->p_proto)) == -1)
        return (false);
    if (bind(st->fd, (const struct sockaddr *)&src_in, sizeof(src_in)) == -1
        || listen(st->fd, 42) == -1) {
        if (close(st->client_fd) == -1)
            return (false);
        return (false);
    }
    return (true);
}
