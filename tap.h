#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int register_tap(char *tapname);
int read_packet(void *buff, int size);
int write_packet(void *buff, int size);
int get_tapfd();
uint8_t *get_tap_hwaddr();
uint8_t *get_tap_ipaddr();