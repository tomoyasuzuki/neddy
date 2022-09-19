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
#include "icmp.h"
#include "ip.h"
#include "tap.h"
#include "util.h"
#include "tcp.h"

int main(int argc, char **argv[]) {
    void *buff;
    int rsize;

    if (register_tap("tap77") < 0) {
        exit(0);
    }

    buff = malloc(MAX_PACKET_SIZE);

    for (;;) {
        rsize = read_packet(buff, MAX_PACKET_SIZE);
        printf("read %d bytes\n", rsize);

        struct ether_hdr *ethdr = (struct ether_hdr*)buff;

        dump_ether(ethdr);

        switch (conv_endian16(ethdr->type)) {
        case TYPE_ARP:
            dump_arp((struct arp_packet*)buff);
            handle_arp((struct arp_packet*)buff);
            break;
        case TYPE_IPV4:
            dump_ip((struct ip_hdr*)(buff+14));
            dump_tcp((struct tcp_hdr*)(buff+34));
            break;
        default:
            break;
        }
    }
}