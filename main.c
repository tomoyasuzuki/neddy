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

struct ether_hdr {
    uint8_t dst_addr[6];
    uint8_t src_addr[6];
    uint16_t type;
};

int main(int argc, char **argv[]) {
    // open tap devide
    int tapfd = open("/dev/net/tun", O_RDWR);
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_ifru.ifru_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, "tap77", IFNAMSIZ);
    if (ioctl(tapfd, TUNSETIFF, &ifr) < 0) {
        perror("error");
    }

    void *buff = malloc(1000);
    // read packets
    for (;;) {
        int size = read(tapfd, buff, 1000);
        struct ether_hdr *ethdr = malloc(14);
        memcpy(ethdr, buff, 14);
        uint16_t first = ethdr->type << 8;
        uint16_t second = ethdr->type >> 8;
        first |= second;
        // 00001000 00000110
        printf("0x%04x\n", first);
        char *type;
        if (first == 0x0800) {
            type = "IPv4";
        } else if (first == 0x0806) {
            type = "ARP";
        } else {
            type = "Unknown";
        }

        printf("Read %d bytes type=0x%04x(=%s)\n", size, first, type);

        for (int i = 0; i < 14; i++) {
            printf("%x ", *((uint8_t*)buff+i));
        }
        printf("\n");
    }
    // 10.0.0.1/24 
    // parse packet and check protocol number and from address;
}