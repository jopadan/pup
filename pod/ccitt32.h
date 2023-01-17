#ifndef __CCITT32__
#define __CCITT32__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define CRC_START_CCITT32_FFFFFFFF 0xFFFFFFFFul
#define CRC_POLY_CCITT32 0x04C11DB7ul

uint32_t crc_ccitt32_ffffffff(const uint8_t* input_string, size_t num_bytes);
uint32_t update_crc_ccitt32(uint32_t crc, uint8_t c);

#endif
