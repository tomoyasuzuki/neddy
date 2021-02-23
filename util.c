#include "util.h"
#include <byteswap.h>

uint16_t conv_endian16(uint16_t value) {
    uint16_t out;
    out = value >> 8;
    out |= value << 8;
    return out;
}

uint32_t conv_endian32(uint32_t value) {
    uint32_t out = (value>>24) & 0xff | ((value<<8)&0xff0000) |  ((value>>8)&0xff00) | ((value<<24)&0xff000000);
    return out;
}