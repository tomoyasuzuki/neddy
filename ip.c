#include "ip.h"
#include "util.h"

void dump_ip(struct ip_hdr *ip) {
    printf("[IP header]\n");
    printf("version & header_len=0x%x\n", ip->value1);
    printf("tos=0x%x\n", ip->tos);
    printf("data_len=0x%x\n", conv_endian16(ip->data_len));
    printf("id=0x%x\n", conv_endian16(ip->id));
    printf("flag & offset=0x%x\n", conv_endian16(ip->value2));
    printf("src addr=%d.%d.%d.%d\n",
            ip->src_addr[0],
            ip->src_addr[1],
            ip->src_addr[2],
            ip->src_addr[3]);
    printf("dst addr=%d.%d.%d.%d\n",
            ip->dst_addr[0],
            ip->dst_addr[1],
            ip->dst_addr[2],
            ip->dst_addr[3]);
}