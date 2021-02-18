#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ETHERNET_HEADER_SIZE 14
#define MAX_PACKET_SIZE 1000
#define TYPE_IPV4 0x0800
#define TYPE_IPV6 0x86dd
#define TYPE_ARP 0x0806
#define ICMP_MAX_LENGTH 2000
#define IP_HEADER_SIZE 20
#define HARD_TYPE_ETHER 0x001
#define PRO_TYPE_IPV4 0x008
#define ARP_REQUEST  0x001
#define ARP_REPLY 0x002
#define ETHER_ADDR_LENGTH 0x06
#define IPV4_ADDR_LENGTH 0x04

struct ether_hdr {
    uint8_t dst_addr[6];
    uint8_t src_addr[6];
    uint16_t type;
} __attribute__((__packed__));

void dump_ether(struct ether_hdr *e);