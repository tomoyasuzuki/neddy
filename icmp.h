#pragma once
#include <stdint.h>

#define ICMP_ECHO_REQUEST 0x008
#define ICMP_ECHO_REPLY 0x0
#define ICMP_CODE 0x0
#define ICMP_MAX_DATA_SIZE 0x0
#define ICMP_OFFSET 34

struct icmp_hdr {
    uint8_t type;
    uint8_t code;  
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence_num;
    uint8_t data[ICMP_MAX_DATA_SIZE];
};

void handle_icmp(void *buff);
void dump_icmp(struct icmp_hdr *icmp);