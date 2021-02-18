#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <features.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "ether.h"
#include "arp.h"
#include "tap.h"
#include "util.h"

int main(int argc, char **argv[]) {
    void *buff;
    int rsize;

    if (register_tap("tap77") < 0) {
        exit(0);
    }

    buff = malloc(MAX_PACKET_SIZE);

    for (;;) {
        rsize = read_packet(buff, MAX_PACKET_SIZE);

        struct ether_hdr *ethdr = (struct ether_hdr*)buff;

        dump_ether(ethdr);

        struct arp_packet *arp;

        if (conv_endian16(ethdr->type) == 0x0806) {
            arp = (struct arp_packet*)buff;
            dump_arp(arp);  
            handle_arp(arp);
        }

        //00:00:5e:00:53:01
        // if (type == "ARP") {
        //     struct icmp_hdr icmphdr;
        //     int icmpsize = sizeof(struct icmp_hdr) + ICMP_MAX_LENGTH;
        //     char *icmptype;
            
        //     memset(&icmphdr, 0, icmpsize);
        //     memcpy(&icmphdr, buff, icmpsize);

        //     if (!icmphdr.type) {
        //         icmptype = "Echo Reply";
        //     } else if (icmphdr.type == 8) {
        //         icmptype = "Echo Request";
        //     }

        //     for (int j = 0; j < 100; j++) {
        //         printf("%x ", *((uint8_t*)&icmphdr+j));
        //     }
        //     printf("\n\n");

        //     printf("ICMP type=0x%x(%s) code=0x%x\n", icmphdr.type, icmptype, icmphdr.code);
        // }
    }
}