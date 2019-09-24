/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** my.h
*/
#ifndef HEADER_H_
#define HEADER_H_

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct s_myftp {
	int fd;
	int client_fd;
	char *client_ip;
	char *line;
	char **cmd;
} t_myftp;

bool serv(char **av, t_myftp *stct);
bool client(t_myftp *stct);
void run_cmd(t_myftp *stct);
int cmd(t_myftp *stct);
char **my_str_to_wordtab(char *str, char separator);


#endif /* !HEADER_H_ */
