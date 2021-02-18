#include "ether.h"

void dump_ether(struct ether_hdr *e) {
    printf("dst addr=%x:%x:%x:%x:%x:%x\n", 
            e->dst_addr[0],
            e->dst_addr[1],
            e->dst_addr[2],
            e->dst_addr[3],
            e->dst_addr[4],
            e->dst_addr[5]);
    printf("src addr=%x:%x:%x:%x:%x:%x\n", 
            e->src_addr[0],
            e->src_addr[1],
            e->src_addr[2],
            e->src_addr[3],
            e->src_addr[4],
            e->src_addr[5]);

    uint16_t first = e->type << 8;
    uint16_t second = e->type >> 8;
    first |= second;

    char *type;
    if (first == TYPE_IPV4) {
        type = "IPv4";
    } else if (first == TYPE_ARP) {
        type = "ARP";
    } else if (first == TYPE_IPV6) {
        type = "IPv6";
    } else {
        type = "Unknown";
    }

    printf("type=0x%x(=%s)\n", first, type);
}