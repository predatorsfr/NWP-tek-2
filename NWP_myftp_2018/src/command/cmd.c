/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** cmd.c
*/

#include "my.h"

static bool pwd(t_myftp *st)
{
    char *str = NULL;

    str = getcwd(str, 4096);
    if (!str)
        return (false);
    write(st->client_fd, "257 \"", 5);
    write(st->client_fd, str, strlen(str));
    write(st->client_fd, "\"\n", 2);
    return (true);
}

static int cmd2(t_myftp *st)
{
    int  del;

    if (!(strncasecmp(st->cmd[0], "DELE", 4))) {
        del = remove(st->cmd[1]);
        if(del == 0)
            write(st->client_fd, "250 Directory successfully changed.\r\n", 37);
        else
            write(st->client_fd, "550 Failed to delete file.\r\n", 27);
        return (0);
    }
    if (!(strncasecmp(st->cmd[0], "PWD", 3))) {
        if (!pwd(st))
            write(st->client_fd, "530 Path does not exist.\r\n", 25);
        return (0);
    } else
        write(st->client_fd, "500 Unknow command.\r\n", 20);
    printf("%s\n", st->cmd[0]);
    return (0);
}

int cmd(t_myftp *st)
{
    if (!strncasecmp(st->cmd[0], "QUIT", 4) && strlen(st->cmd[0]) < 7) {
        write(st->client_fd, "221 Goodbye.\r\n", 13);
        if (close(st->client_fd) == -1)
            return (84);
        else
            return (0);
    }
    if (!(strncasecmp(st->cmd[0], "CDUP", 4))) {
        write(st->client_fd, "250 Directory successfully changed.\r\n", 37);
        return (0);
    }
    if ((!(strncasecmp(st->cmd[0], "CWD", 3)) && st->cmd[1])) {
        if (chdir(st->cmd[1]) < 0)
            write(st->client_fd, "550 Failed to change directory.\r\n", 33);
        else
            write(st->client_fd, "250 directory successfully changed.\r\n", 37);
        return (0);
    } else
        cmd2(st);
    return (0);
}
