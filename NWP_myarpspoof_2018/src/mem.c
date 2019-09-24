/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** initialize.c
*/

#include "my.h"

char *memsc(int nbr)
{
    int n = nbr * sizeof(char);
    void *mem = (char *)malloc(n);

    if (mem == NULL)
        exit(1);
    memset(mem, 0, nbr * sizeof(char));
    return (mem);

}

uint8_t *memsi(int nbr)
{
    int n = nbr * sizeof(uint8_t);
    void *mem = (uint8_t *)malloc(n);

    if (mem == NULL)
        exit(1);
    memset(mem, 0, nbr * sizeof(uint8_t));
    return (mem);

}

stct_t init(char *interf)
{
    stct_t sck;

    sck.dest_ip = memsc(INET_ADDRSTRLEN);
    sck.src_ip = memsc(INET_ADDRSTRLEN);
    sck.message = memsi(IP_MAXPACKET);
    sck.dest_mac = memsi(6);
    sck.src_mac = memsi(6);
    sck.interf = memsc(40);
    memset(&sck.dev, 0, sizeof(sck.dev));
    strcpy(sck.interf, interf);
    return (sck);
}
