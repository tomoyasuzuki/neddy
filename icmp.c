#include "icmp.h"
#include "util.h"
#include "ether.h"
#include "ip.h"
#include "string.h"
#include "tap.h"

void icmp_reply(void *buff) {
    printf("== ICMP echo reply ==\n");
    
    struct ether_hdr *ether = (struct ether_hdr*)buff;
    void *tmp = malloc(ETHER_ADDR_LENGTH);
    memcpy(tmp, ether->dst_addr, ETHER_ADDR_LENGTH);
    memcpy(ether->dst_addr, ether->src_addr, ETHER_ADDR_LENGTH);
    memcpy(ether->src_addr, tmp, ETHER_ADDR_LENGTH);

    struct ip_hdr *ip = (struct ip_hdr*)((char*)ether + 14);
    memset(tmp, 0, ETHER_ADDR_LENGTH);
    memcpy(tmp, ip->dst_addr, IPV4_ADDR_LENGTH);
    memcpy(ip->dst_addr, ip->src_addr, IPV4_ADDR_LENGTH);
    memcpy(ip->src_addr, tmp, IPV4_ADDR_LENGTH);

    struct icmp_hdr *icmp = (struct icmp_hdr*)((char*)ip + 20);
    icmp->type = 0x0;
    icmp->sequence_num += 1;

    dump_ether(ether);
    dump_ip(ip);
    dump_icmp(icmp);

    printf("=====================\n");

    int wsize = 0;

    if ((wsize = write_packet(buff, 98)) < 0) {
        perror("write packet");
        exit(1);
    }

    printf("[ICMP echo reply] write packet %d bytes\n", wsize);
}

void handle_icmp(void *buff) {
    struct icmp_hdr *icmp = (struct icmp_hdr*)(buff + 34);
    dump_icmp(icmp);
    if (icmp->type == 0x008) {
        icmp_reply(buff);
    }
}

void dump_icmp(struct icmp_hdr *icmp) {
    printf("[ICMP header]\n");
    printf("type=0x%x\n", icmp->type);
    printf("code=0x%x\n", icmp->code);
    printf("checksum=0x%x\n", conv_endian16(icmp->checksum));
    printf("identifier=0x%x\n", conv_endian16(icmp->identifier));
    printf("sequence_num=0x%x\n", conv_endian16(icmp->sequence_num));
}