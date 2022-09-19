#include "tcp.h"
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void handle_tcp(void *buff) {

}

void dump_tcp(struct tcp_hdr *tcp) {
    printf("[TCP header]\n");
    printf("src port=%d\n", conv_endian16(tcp->src_addr));
    printf("dst port=%d\n", conv_endian16(tcp->dst_addr));
    printf("seqnum=%x\n", conv_endian32(tcp->seq_num));
    printf("ack=%d\n", conv_endian32(tcp->ack_num));
    printf("hlen=%d\n", tcp->value1 >> 4);
    printf("flags=");

    for (int i = 7; i >= 0; i--) {
        if (tcp->value2 & (1<<i)) {
            printf("1");
        } else {
            printf("-");
        }
    }
    printf("\n");

    printf("window size=%d\n", conv_endian16(tcp->window_size));
    printf("checksum=0x%x\n", conv_endian16(tcp->checksum));
    printf("up=%d\n", conv_endian16(tcp->urg_ptr));
}