#include "tap.h"
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

struct tap {
    int fd;
    char *name;
    uint8_t ipaddr[4];
    uint8_t hwaddr[6];
};

struct tap *tap;

int register_tap(char *tapname) {
    struct ifreq ifr;

    tap = malloc(sizeof(struct tap));

    if ((tap->fd = open("/dev/net/tun", O_RDWR)) < 0) {
        perror("open tun device");
        free(tap);
        return -1;
    }

    ifr.ifr_ifru.ifru_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, tapname, IFNAMSIZ);
    
    if (ioctl(tap->fd, TUNSETIFF, &ifr) < 0) {
        perror("ioctl TUNSETIFF");
        free(tap);
        return -1;
    }

    uint8_t ip[4] = {10, 0, 0, 2};
    memcpy(tap->ipaddr, &ip, 4);
    uint8_t hw[6] = {0x0, 0x0, 0x5e, 0x0, 0x53, 0x01};
    memcpy(tap->hwaddr, &hw, 6);

    tap->name = tapname;

    return 1;
}

int read_packet(void *buff, int size) {
    return read(tap->fd, buff, size);
}

int write_packet(void *buff, int size) {
    return write(tap->fd, buff, size);
}

int get_tapfd() {
    return tap->fd;
}

uint8_t *get_tap_hwaddr() {
    return (uint8_t*)tap->hwaddr;
}

uint8_t *get_tap_ipaddr() {
    return (uint8_t*)tap->ipaddr;
}