/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** main.c
*/

#include "my.h"

_Bool testip(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));

    return result;
}

void build(struct sockaddr_in src_addr, struct sockaddr_in dst_addr,
           uint8_t *data, unsigned int data_size)
{
    unsigned int packet_size;
    uint8_t udp_packet[1500];
    uint8_t packet[1500];

    packet_size = build_udp_packet(src_addr, dst_addr, udp_packet,
                                   data, data_size);

    packet_size = build_ip_packet(src_addr.sin_addr, dst_addr.sin_addr,
                                  IPPROTO_UDP, packet, udp_packet, packet_size);
}

int network(char **av)
{
    int raw_sock;
    int val = 1;
    uint8_t data[1024] = "client hello";
    char *sending_data = "client hello";
    unsigned int data_size = strlen(sending_data);
    struct sockaddr_in src_addr;
    struct sockaddr_in dst_addr;

    src_addr.sin_family = AF_INET;
    src_addr.sin_port = htons(2048);
    inet_aton("192.168.0.1", &src_addr.sin_addr);
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_port = htons(atoi(av[4]));
    inet_aton(av[2], &dst_addr.sin_addr);
    if((raw_sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
        return 84;
    build(src_addr,dst_addr,data,data_size);
    setsockopt(raw_sock, IPPROTO_IP, IP_HDRINCL, &val, sizeof(val));
    send_udp_packet(raw_sock, src_addr, dst_addr, data, data_size);
    return 0;
}

int flags(int ac, char **av)
{
    if (ac != 7)
        return 84;

    if (strcmp(av[1], "-t") != 0)
        if(strcmp(av[1], "--target") != 0)
            return 84;

    if (testip(av[2]) == 0 && strcmp(av[2], "localhost") != 0) {
        printf("No such hostname: '%s'\n", av[2]);
        return 84;
    }

    if (strcmp(av[3], "-p") != 0)
        if(strcmp(av[3], "--port") != 0)
            return 84;
    if (strcmp(av[5], "-P") != 0)
        if(strcmp(av[5], "--password") != 0)
            return 84;

    return 0;
}

int main(int ac, char **av)
{
    if (flags(ac,av) == 84)
        return 84;

    if (network(av) == 84)
        return 84;

    return 0;
}
