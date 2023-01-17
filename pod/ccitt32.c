#include "ccitt32.h"

static uint32_t crc_ccitt32_generic(const uint8_t* input_str, size_t num_bytes, uint32_t start_value);
static void init_crcccitt32_tab( uint32_t poly, uint32_t swapped);

static bool crc_tabccitt32_init = false;
static uint32_t crc_tabccitt32[256];


static void init_crcccitt32_tab( uint32_t poly, uint32_t swapped) {

	int i;
	int j;
	uint32_t crc;

	for (i=0; i<256; i++) {
		if(swapped) {
			crc = crc & 1 ? (crc >> 1)^poly : crc >> 1;
			for (crc=i,j=8; --j >=0 ;) {
				crc = crc & 1 ? (crc >> 1)^poly : crc >> 1;
			}
		}
		else {
			for (crc=i<<24, j=8; --j >= 0;) {
				crc = crc & 0x80000000 ? (crc << 1)^poly : crc << 1;
			}
		}
		crc_tabccitt32[i] = crc;
	}

	crc_tabccitt32_init = true;

}  /* init_crcccitt32_tab */

static uint32_t crc_ccitt32_generic(const uint8_t* input_str, size_t num_bytes, uint32_t start_value) {
	uint32_t crc;
	const unsigned char *ptr;
	size_t a;

	if(!crc_tabccitt32_init) init_crcccitt32_tab(CRC_POLY_CCITT32, 0);

	crc = start_value;
	ptr = input_str;

	if(ptr == NULL)
		return crc;

	for( a = 0; a < num_bytes; a++)
		crc = ((crc << 8)&0xffffff00) ^ crc_tabccitt32[ (((crc >> 24)&0xff) ^ *ptr++)];

	return crc;
}

uint32_t update_crc_ccitt32( uint32_t crc, unsigned char c ) {

	if ( ! crc_tabccitt32_init ) init_crcccitt32_tab(CRC_POLY_CCITT32, 0);

	return ((crc << 8)&0xffffff00) ^ crc_tabccitt32[ ((crc >> 24) ^ c) & 0xff ];

}  /* update_crc_ccitt32 */

uint32_t crc_ccitt32_ffffffff(const uint8_t* input_str, size_t num_bytes) {
	return crc_ccitt32_generic(input_str,num_bytes, CRC_START_CCITT32_FFFFFFFF);
}

