#ifndef __CHKSUM__
#define __CHKSUM__

#include <stdint.h>

#include "chksum/crc32.h"
#include "chksum/crc32c.h"
#include "chksum/ccitt32.h"
#include "chksum/kastanoglia.h"

typedef enum checksum_type_s {
	CRC32,
	CRC32C,
	CCITT32,
	KASTANOGLIA,
} checksum_type_t;

typedef struct checksum_table_s {
	
} checksum_table_t;

typedef struct checksum_s {
  uintmax_t       value;
  uintmax_t       start;
  uintmax_t       end;
  checksum_type_t type;
} checksum_t;

checksum_type_t chksum_init(const char* name, int poly, int init, int swapped, int bits)
{
	
}
checksum_t checksum(uint8_t* buf, uintmax_t start, uintmax_t end, checksum_type_t type)
{
	if(buf && (start < end))
	{
		switch(type)
		{
			case CRC32:
				return { chksum_crc32(buf + start, end - start), start, end, type };
			case CRC32C:
				return { chksum_crc32c(buf + start, end - start), start, end, type };
			case CCITT32:
				return { chksum_ccitt32(buf + start, end - start), start, end, type };
			case KASTAGNOLIA:
				return { chksum_kastanoglia(buf + start, end - start), start, end, type };
			default:
				break;
		}
	}
	return { (uintmax_t)-1, start, end, type };
}

#endif
