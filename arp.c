#include "arp.h"
#include "util.h"
#include "tap.h"
#include <string.h>

int handle_arp(struct arp_packet *arp) {
    switch (conv_endian16(arp->opcode)) {
    case ARP_REQUEST:
        if (arp_reply(arp) < 0) {
            printf("fail: arp_reply\n");
            return -1;
        }
        break;
    case ARP_REPLY:
        break;
    default:
        break;
    }
}

int arp_reply(struct arp_packet *request) {
    struct arp_packet arp;
    int wsize;

    memset(&arp, 0, sizeof(arp));
    
    arp.hard = 0x100;
    arp.pro = 0x008;
    arp.hard_len = ETHER_ADDR_LENGTH;
    arp.pro_len = IPV4_ADDR_LENGTH;
    arp.opcode = 0x0200;
    memcpy(arp.sha, get_tap_hwaddr(), 6);
    memcpy(arp.spa, get_tap_ipaddr(), 4);

    // setup ethernet header
    memcpy(&arp.ethdr.dst_addr, request->sha, ETHER_ADDR_LENGTH);
    memcpy(&arp.ethdr.src_addr, arp.sha, ETHER_ADDR_LENGTH);
    arp.ethdr.type = 0x0608;

    memcpy(&arp.tha, request->sha, ETHER_ADDR_LENGTH);
    memcpy(&arp.tpa, request->spa, IPV4_ADDR_LENGTH);
    
    dump_ether(&(arp.ethdr));
    dump_arp(&arp);

    if ((wsize = write_packet(&arp, sizeof(arp))) < 0) {
        return -1;
    }

    printf("write %d bytes\n", wsize);

    return 1;
}

void dump_arp(struct arp_packet *arp) {
    printf("hard_type=%x ", conv_endian16(arp->hard));
    printf("len %x\n", arp->hard_len);
    printf("pro_type=%x ", conv_endian16(arp->pro));
    printf("len %x\n", arp->pro_len);
    printf("opcode=0x%x(=%s)\n",
            conv_endian16(arp->opcode), 
            conv_endian16(arp->opcode) == ARP_REQUEST ? "REQUEST" : "REPLY");
    printf("sha=%x:%x:%x:%x:%x:%x\n",
            arp->sha[0],
            arp->sha[1],
            arp->sha[2],
            arp->sha[3],
            arp->sha[4],
            arp->sha[5]);
    printf("spa=%d:%d:%d:%d\n",
            arp->spa[0],
            arp->spa[1],
            arp->spa[2],
            arp->spa[3]);
    printf("tha=%x:%x:%x:%x:%x:%x\n",
            arp->tha[0],
            arp->tha[1],
            arp->tha[3],
            arp->tha[3],
            arp->tha[4],
            arp->tha[5]);
    printf("tpa=%d:%d:%d:%d\n",
            arp->tpa[0],
            arp->tpa[1],
            arp->tpa[2],
            arp->tpa[3]);
}