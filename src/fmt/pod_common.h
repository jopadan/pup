#ifndef __POD_COMMON__
#define __POD_COMMON__

#include <stdint.h>

enum pod_ident_type = { POD1 = 0, POD2, POD3, POD4, POD5, POD6, EPD, POD_IDENT_TYPE_SIZE };

/* main variable type sizes of POD file formats                                                            */
typedef uint32_t                             pod_number_t
typedef int8_t                               pod_char_t
#define POD_NUMBER_SIZE                      UINT32_WIDTH                  /* length of a numerical entry   */
#define POD_COMMENT_SIZE                     (UINT32_WIDTH + UINT16_WIDTH) /* comment length of POD format  */
#define EPD_COMMENT_SIZE                     (UINT8_MAX + 1)               /* comment length of EPD format  */
#define POD_IDENT_SIZE                       INT8_WIDTH * 4                /* file magic ident length       */
#define POD_IDENT_TYPE_SIZE                  (EPD + 1)                     /* number of POD format types    */
#define POD_HEADER_CHECKSUM_DEFAULT          0x44424247                    /* default checksum of POD file  */
#define POD_ENTRY_CHECKSUM_DEFAULT           0x20444542                    /* default checksum of POD entry */
#define POD_ENTRY_TIMESTAMP_DEFAULT          0x42494720                    /* default timestamp of POD entry */
#define POD_HEADER_UNKNOWN10C_DEFAULT        0x58585858			   /* default value of unknown10c   */

/* map pod ident type enum id to file magic ident null terminated string */
char POD_IDENT[POD_IDENT_TYPE_SIZE][POD_IDENT_SIZE + 1] = { "\0POD1", "POD2\0", "POD3\0", "POD4\0", "POD5\0", "POD6\0", "dtxe\0" };

/* pod_header_t element sizes */
#define POD_HEADER_NUMBER_SIZE               POD_NUMBER_SIZE
#define POD_HEADER_COMMENT_SIZE              POD_COMMENT_SIZE
#define POD_HEADER_EPD_COMMENT_SIZE          EPD_COMMENT_SIZE
#define POD_HEADER_IDENT_SIZE                POD_IDENT_SIZE
#define POD_HEADER_NEXT_ARCHIVE_SIZE         POD_HEADER_COMMENT_SIZE
#define POD_HEADER_AUTHOR_SIZE               POD_HEADER_COMMENT_SIZE
#define POD_HEADER_COPYRIGHT_SIZE            POD_HEADER_COMMENT_SIZE
#define POD_HEADER_CHECKSUM_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_FILE_COUNT_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_AUDIT_FILE_COUNT_SIZE     POD_HEADER_NUMBER_SIZE
#define POD_HEADER_REVISION_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_VERSION_SIZE              POD_HEADER_NUMBER_SIZE
#define POD_HEADER_PRIORITY_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_INDEX_OFFSET_SIZE         POD_HEADER_NUMBER_SIZE
#define POD_HEADER_SIZE_INDEX_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_NAME_COUNT_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN10C                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN114                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN118                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN11C                POD_HEADER_NUMBER_SIZE

#define POD_DIR_ENTRY_FILENAME_SIZE          256
#define POD_DIR_ENTRY_NUMBER_SIZE            POD_NUMBER_SIZE
#define POD_DIR_ENTRY_SIZE_SIZE              POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_OFFSET_SIZE            POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_PATH_OFFSET_SIZE       POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_UNCOMPRESS_SIZE        POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_COMPRESSION_LEVEL_SIZE POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_TIMESTAMP_SIZE         POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_CHECKSUM_SIZE          POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_ZERO_SIZE              POD_DIR_ENTRY_NUMBER_SIZE

const ssize_t POD_HEADER_SIZE[POD_IDENT_TYPE_SIZE] =
{
	POD_HEADER_POD1_SIZE,
	POD_HEADER_POD2_SIZE,
	POD_HEADER_POD3_SIZE,
	POD_HEADER_POD4_SIZE,
	POD_HEADER_POD5_SIZE,
	POD_HEADER_POD6_SIZE,
	POD_HEADER_EPD_SIZE,
}

const ssize_t POD_DIR_ENTRY_SIZE[POD_IDENT_TYPE_SIZE] =
{
	POD_DIR_ENTRY_POD1_SIZE,
	POD_DIR_ENTRY_POD2_SIZE,
	POD_DIR_ENTRY_POD3_SIZE,
	POD_DIR_ENTRY_POD4_SIZE,
	POD_DIR_ENTRY_POD5_SIZE,
	POD_DIR_ENTRY_POD6_SIZE,
	POD_DIR_ENTRY_EPD_SIZE,
}

typedef struct pod_dir_entry_s {
	pod_char_t* filename[POD_IDENT_TYPE_SIZE];
	pod_number_t file_path_offset;
	pod_number_t file_size;
	pod_number_t file_offset;
	pod_number_t file_uncompressed_size;
	pod_number_t file_compression_level;
	pod_number_t file_timestamp;
	pod_number_t file_checksum;
} pod_dir_entry_t;

int pod_type(restable_t * rt)
{
  char ident[4];

  if (readf(rt->file, "c4", ident) == OK)
  {
	  for(int i = 0; i < POD_IDENT_TYPE_SIZE; i++)
	  {
		  char * pod_ident = &POD_IDENT[i][0];
		  if (strncmp(ident, pod_ident, strlen(pod_ident)) == 0)
			  return i;
	  }
  }
  return POD1;
}

bool_t is_pod(restable_t * rt)
{
  return (POD_IDENT_TYPE_SIZE > pod_type(rt) >= 0);
}

#endif
