/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** run.c
*/

#include "my.h"

static bool pswd(t_myftp *st, char *user)
{
    int rd;

    st->line = malloc(sizeof(char) * 50000);
    if ((rd = read(st->client_fd, st->line, 5000)) < 0)
        return (false);
    if (st->line)
        st->cmd = my_str_to_wordtab(st->line, ' ');
    if (!strncasecmp(st->cmd[0], "PASS", 4)) {
        if (!strncasecmp(user, "Anonymous", 9)) {
            write(st->client_fd, "230 User logged in proceed.\r\n", 29);
            return true;
        }
    }
    else if (strncasecmp(user, "Anonymous", 9)) {
        write(st->client_fd, "530 Login incorrect.\r\n", 22);
        return false;
    }
    return false;
}

static bool connect_cmd(t_myftp *st)
{
    if (!strncasecmp(st->cmd[0], "USER", 4)) {
        if (st->cmd[1] && isalnum(st->cmd[1][0])) {
            write(st->client_fd, "331 Please specify the password.\r\n", 34);
            return ((pswd(st, st->cmd[1])) ? true : false);
        }
        write(st->client_fd, "530 Permission denied.\n", 23);
        return (false);
    }
    write(st->client_fd, "530 Please login with USER and PASS.\n", 37);
    return (false);
}

void run_cmd(t_myftp *st)
{
    if (connect_cmd(st) == true)
        return;
    if (!strncasecmp(st->cmd[0], "NOOP", 4) && strlen(st->cmd[0]) < 7) {
        write(st->client_fd, "200 NOOP ok.\n", 13);
        return;
    }
    if (!strncasecmp(st->cmd[0], "help", 4) && strlen(st->cmd[0]) < 7) {
        write(st->client_fd,
              "214-The following commands are recognized."
              "\n214 Help OK.\n", 56);
        return;
    }
    cmd(st);
}
