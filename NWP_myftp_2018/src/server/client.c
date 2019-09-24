/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** run_s.c
*/

#include "my.h"

static bool run(t_myftp *st)
{
    int rd;

    while (1) {
        st->line = malloc(sizeof(char) * 50000);
        if ((rd = read(st->client_fd, st->line, 5000)) < 0)
            return (false);
        st->cmd = my_str_to_wordtab(st->line, ' ');
        run_cmd(st);
    }
    return (true);
}

bool client(t_myftp *st)
{
    int pid = -1;
    struct sockaddr_in src;
    socklen_t src_in_size = sizeof(src);

    while (1) {
        if ((st->client_fd = accept(st->fd, (struct sockaddr *)&src,
                                    &src_in_size)) == -1)
            return (false);
        st->client_ip = inet_ntoa(src.sin_addr);
        if ((pid = fork()) == 0) {
            write(st->client_fd, "220 (MyFTP)\n", 12);
            if (!run(st))
                exit(84);
            exit(0);
        }
        if (close(st->client_fd) == -1)
            return (false);
    }
    return (true);
}
