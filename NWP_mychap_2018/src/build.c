/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** build.c
*/

#include "my.h"

unsigned int build_ip_packet(struct in_addr src_addr, struct in_addr dst_addr,
                             uint8_t protocol, uint8_t *ip_packet,
                             uint8_t *data, unsigned int data_size)
{
    struct iphdr *ip_header;

    ip_header = (struct iphdr *)ip_packet;
    ip_header->version = 4;
    ip_header->ihl = 5;
    ip_header->tos = 0;
    ip_header->tot_len = htons(20 + data_size);
    ip_header->id = 0;
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = protocol;
    ip_header->check = 0;
    ip_header->saddr = src_addr.s_addr;
    ip_header->daddr = dst_addr.s_addr;

    memcpy(ip_packet + sizeof(struct iphdr), data, data_size);

    return sizeof(struct iphdr) + data_size;
}

unsigned int build_udp_packet(struct sockaddr_in src_addr,
                              struct sockaddr_in dst_addr,
                              uint8_t *udp_packet, uint8_t *data,
                              unsigned int data_size)
{
    uint8_t pseudo_packet[1024];
    uint16_t length = 8 + data_size;
    struct udphdr *udph;
    struct pseudo_iphdr *p_iphdr = (struct pseudo_iphdr *)pseudo_packet;

    udph = (struct udphdr *)udp_packet;
    udph->source = src_addr.sin_port;
    udph->dest = dst_addr.sin_port;
    udph->len = htons(length);
    memcpy(udp_packet + 8, data, data_size);
    if(length + sizeof(struct pseudo_iphdr) > 1024)
        return 84;
    p_iphdr->source_addr = src_addr.sin_addr.s_addr;
    p_iphdr->dest_addr = dst_addr.sin_addr.s_addr;
    p_iphdr->zeros = 0;
    p_iphdr->prot = IPPROTO_UDP;
    p_iphdr->length = udph->len;
    memcpy(pseudo_packet + sizeof(struct pseudo_iphdr), udph, length);
    udph->check = checksum(pseudo_packet, sizeof(struct pseudo_iphdr) + length);
    return length;
}
