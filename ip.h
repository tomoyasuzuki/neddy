#pragma once
#include <stdint.h>

struct ip_hdr {
    uint8_t value1;
    uint8_t tos;
    uint16_t data_len;
    uint16_t id;
    uint16_t value2;
    uint8_t ttl;
    uint8_t pro_num;
    uint16_t checksum;
    uint8_t src_addr[4];
    uint8_t dst_addr[4];
    uint8_t buff[100];
};

void dump_ip(struct ip_hdr *ip);