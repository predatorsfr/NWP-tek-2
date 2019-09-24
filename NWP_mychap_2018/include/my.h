/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** my.h
*/
#ifndef HEADER_H_
#define HEADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdint.h>

struct pseudo_iphdr
{
    uint32_t source_addr;
    uint32_t dest_addr;
    uint8_t zeros;
    uint8_t prot;
    uint16_t length;
};

uint16_t checksum(uint8_t *data, unsigned int size);
unsigned int build_udp_packet(struct sockaddr_in src_addr,
                              struct sockaddr_in dst_addr, uint8_t *udp_packet,
                              uint8_t *data, unsigned int data_size);
unsigned int build_ip_packet(struct in_addr src_addr,
                             struct in_addr dst_addr, uint8_t protocol, uint8_t *ip_packet,
                             uint8_t *data, unsigned int data_size);
int send_udp_packet(int raw_sock, struct sockaddr_in src_addr,
                    struct sockaddr_in dst_addr, uint8_t *data, unsigned int data_size);

#endif /* !HEADER_H_ */
