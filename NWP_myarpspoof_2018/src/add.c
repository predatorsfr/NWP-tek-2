/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** getter.c
*/

#include "my.h"

char *addrmac(char *c)
{
    char mac;
    char add[9] = "/address";
    char sys[16] = "/sys/class/net/";
    char *retMac = malloc(strlen("11:11:11:11:11:11") + 1);
    char *mal = malloc(strlen(sys) + strlen(add) + strlen(c) + 1);

    strcpy(mal, sys);
    strcat(mal, c);
    strcat(mal, add);
    FILE *f = fopen(mal, "r");
    for(int i = 0; (mac = fgetc(f)) != EOF; i++)
        retMac[i] = mac;
    fclose(f);
    return (retMac);
}

char *addrip(char *c)
{
    int sock;
    struct ifreq trap;
    char *ipaddr = malloc(strlen("000.000.000.000") + 1);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    trap.ifr_addr.sa_family = AF_INET;
    strncpy(trap.ifr_name, c, IFNAMSIZ - 1);
    ioctl(sock, SIOCGIFADDR, &trap);
    close(sock);
    strcpy(ipaddr, inet_ntoa(((struct sockaddr_in *)&trap.ifr_addr)->sin_addr));
    return (ipaddr);
}

void convert(char *str, uint8_t *mac)
{
    int nb[6];

    if( 6 == sscanf(str, "%x:%x:%x:%x:%x:%x%*c", &nb[0], &nb[1], &nb[2],
                    &nb[3], &nb[4], &nb[5])) {
        for( int i = 0; i < 6; ++i )
            mac[i] = (uint8_t) nb[i];
    }
}
