/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** send.c
*/

#include "my.h"

int send_udp_packet(int raw_sock, struct sockaddr_in src_addr,
                    struct sockaddr_in dst_addr, uint8_t *data,
                    unsigned int data_size)
{
    unsigned int packet_size;
    unsigned int ip_payload_size;
    uint8_t packet[1500];

    memset(packet, 0, 1500);
    ip_payload_size = build_udp_packet(src_addr, dst_addr,
                                       packet + sizeof(struct iphdr),
                                       data, data_size);

    packet_size = build_ip_packet(src_addr.sin_addr, dst_addr.sin_addr,
                                  IPPROTO_UDP, packet,
                                  packet + sizeof(struct iphdr),
                                  ip_payload_size);

    if(sendto(raw_sock, packet, packet_size, 0,
              (struct sockaddr *)&dst_addr, sizeof(dst_addr)) < 0)
        return 84;
    return 0;
}
