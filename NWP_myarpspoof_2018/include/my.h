/*
** EPITECH PROJECT, 2019
** MY.h
** File description:
** ARP
*/

#ifndef MY_H
#define MY_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
#include <bits/ioctls.h>

typedef struct stct_t
{
    uint8_t *dest_ip;
    uint8_t *src_ip;
    uint8_t *dest_mac;
    uint8_t *src_mac;
    uint8_t *message;
    struct sockaddr_ll dev;
    char *interf;
    int length;

} stct_t;

typedef struct sock_t
{
     uint16_t SH;
     uint16_t SP;
     uint8_t sck;
     uint8_t sck2;
     uint16_t cOP;
     uint8_t oM[6];
     uint8_t oI[4];
     uint8_t aM[6];
     uint8_t aI[4];
} sock_t;

void sendarp(stct_t packet);
int new(stct_t *packet);
void convert(char *str, uint8_t *mac);
char *memsc(int nbr);
char *addrmac(char *interface);
void receive(stct_t *packet);
uint8_t *memsi(int nbr);
stct_t init();

#endif
