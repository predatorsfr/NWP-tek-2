/*
** EPITECH PROJECT, 2019
** RSD64
** File description:
** checksum.c
*/

#include "my.h"

uint16_t checksum(uint8_t *data, unsigned int size)
{
    unsigned int i;
    int sum = 0;
    uint16_t *p = (uint16_t *)data;

    for(i = 0; i < size; i += 2)
        sum += *(p++);

    uint16_t carry = sum >> 16;
    uint16_t tmp = 0x0000ffff & sum;
    uint16_t res = ~(tmp + carry);

    return res;
}
