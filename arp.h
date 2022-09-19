#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ether.h"

struct arp_packet {
    struct ether_hdr ethdr;
    uint16_t hard;
    uint16_t pro;
    uint8_t hard_len;
    uint8_t pro_len;
    uint16_t opcode;
    uint8_t sha[ETHER_ADDR_LENGTH];
    uint8_t spa[IPV4_ADDR_LENGTH];
    uint8_t tha[ETHER_ADDR_LENGTH];
    uint8_t tpa[IPV4_ADDR_LENGTH];
} __attribute__((__packed__));

int handle_arp(struct arp_packet *arp);
int arp_reply(struct arp_packet *request);
void dump_arp(struct arp_packet *arp);