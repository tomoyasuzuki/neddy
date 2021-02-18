#include "util.h"

uint16_t conv_endian16(uint16_t value) {
    uint16_t out;
    out = value >> 8;
    out |= value << 8;
    return out;
}

uint32_t conv_endian32(uint32_t value) {
    uint32_t out;
    out = value >> 24;
    out |= value >> 16;
    out |= value >> 8;
    out |= value << 24;
    return out;
}