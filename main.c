#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <features.h>
#include <stdint.h>

#define ETHERNET_HEADER_SIZE 14
#define MAX_PACKET_SIZE 1000
#define TYPE_IPV4 0x0800
#define TYPE_IPV6 0x86dd
#define TYPE_ARP 0x0806

struct ether_hdr {
    uint8_t dst_addr[6];
    uint8_t src_addr[6];
    uint16_t type;
};

int main(int argc, char **argv[]) {
    int tapfd;
    struct ifreq ifr;
    void *buff;
    int rsize;

    if ((tapfd = open("/dev/net/tun", O_RDWR)) < 0) {
        perror("error");
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_ifru.ifru_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, "tap77", IFNAMSIZ);
    
    if (ioctl(tapfd, TUNSETIFF, &ifr) < 0) {
        perror("error");
    }

    buff = malloc(MAX_PACKET_SIZE);

    for (;;) {
        rsize = read(tapfd, buff, MAX_PACKET_SIZE);

        struct ether_hdr *ethdr = malloc(ETHERNET_HEADER_SIZE);
        memcpy(ethdr, buff, ETHERNET_HEADER_SIZE);

        uint16_t first = ethdr->type << 8;
        uint16_t second = ethdr->type >> 8;
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

        printf("Read %d bytes type=0x%04x(=%s)\n", rsize, first, type);
        printf("dst addr=%x:%x:%x:%x:%x:%x\n", 
                ethdr->dst_addr[0],
                ethdr->dst_addr[1],
                ethdr->dst_addr[2],
                ethdr->dst_addr[3],
                ethdr->dst_addr[4],
                ethdr->dst_addr[5]);
        printf("src addr=%x:%x:%x:%x:%x:%x\n", 
                ethdr->src_addr[0],
                ethdr->src_addr[1],
                ethdr->src_addr[2],
                ethdr->src_addr[3],
                ethdr->src_addr[4],
                ethdr->src_addr[5]);
    }
}