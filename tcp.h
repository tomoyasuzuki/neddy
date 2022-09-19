#pragma once
#include <stdint.h>

struct tcp_hdr {
    uint16_t src_addr;
    uint16_t dst_addr;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t value1;
    uint8_t value2;
    uint16_t window_size;
    uint16_t checksum;
    uint16_t urg_ptr;
};

void handle_tcp(void *buff);
void dump_tcp(struct tcp_hdr *tcp);