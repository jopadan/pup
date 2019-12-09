#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bin.h"
#include "pod.h"

enum pod_ident_type = { POD1 = 0,  POD2,  POD3,  POD4,  POD5,  EPD, };

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
char POD_IDENT[POD_IDENT_TYPE_SIZE][POD_IDENT_SIZE + 1] = { "\0POD1", "POD2\0", "POD3\0", "POD4\0", "POD5\0", "dtxe\0" };

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
#define POD_HEADER_AUDIT_FILE_COUNT_Size     POD_HEADER_NUMBER_SIZE
#define POD_HEADER_REVISION_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_PRIORITY_SIZE             POD_HEADER_NUMBER_SIZE
#define POD_HEADER_INDEX_OFFSET_SIZE         POD_HEADER_NUMBER_SIZE
#define POD_HEADER_SIZE_INDEX_SIZE           POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN10C                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN114                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN118                POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN11C                POD_HEADER_NUMBER_SIZE

#define POD_HEADER_POD1_SIZE (POD_HEADER_FILE_COUNT_SIZE + \
                              POD_HEADER_COMMENT_SIZE)

#define POD_HEADER_POD2_SIZE (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_CHECKSUM_SIZE + \
			      POD_HEADER_COMMENT_SIZE + \
			      POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_AUDIT_FILE_COUNT_SIZE)

#define POD_HEADER_POD3_SIZE (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_CHECKSUM_SIZE + \
			      POD_HEADER_COMMENT_SIZE + \
			      POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_AUDIT_FILE_COUNT_SIZE + \
			      POD_HEADER_REVISION_SIZE + \
			      POD_HEADER_PRIORITY_SIZE + \
			      POD_HEADER_AUTHOR_SIZE + \
			      POD_HEADER_COPYRIGHT_SIZE + \
			      POD_HEADER_INDEX_OFFSET_SIZE + \
			      POD_HEADER_UNKNOWN10C_SIZE + \
			      POD_HEADER_SIZE_INDEX_SIZE + \
			      POD_HEADER_UNKNOWN114_SIZE + \
			      POD_HEADER_UNKNOWN118_SIZE + \
			      POD_HEADER_UNKNOWN11C_SIZE)

#define POD_HEADER_POD4_SIZE (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_CHECKSUM_SIZE + \
			      POD_HEADER_COMMENT_SIZE + \
			      POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_AUDIT_FILE_COUNT_SIZE + \
			      POD_HEADER_REVISION_SIZE + \
			      POD_HEADER_PRIORITY_SIZE + \
			      POD_HEADER_AUTHOR_SIZE + \
			      POD_HEADER_COPYRIGHT_SIZE + \
			      POD_HEADER_INDEX_OFFSET_SIZE + \
			      POD_HEADER_UNKNOWN10C_SIZE + \
			      POD_HEADER_SIZE_INDEX_SIZE + \
			      POD_HEADER_UNKNOWN114_SIZE + \
			      POD_HEADER_UNKNOWN118_SIZE + \
			      POD_HEADER_UNKNOWN11C_SIZE)

#define POD_HEADER_POD5_SIZE (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_CHECKSUM_SIZE + \
			      POD_HEADER_COMMENT_SIZE + \
			      POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_AUDIT_FILE_COUNT_SIZE + \
			      POD_HEADER_REVISION_SIZE + \
			      POD_HEADER_PRIORITY_SIZE + \
			      POD_HEADER_AUTHOR_SIZE + \
			      POD_HEADER_COPYRIGHT_SIZE + \
			      POD_HEADER_INDEX_OFFSET_SIZE + \
			      POD_HEADER_UNKNOWN10C_SIZE + \
			      POD_HEADER_SIZE_INDEX_SIZE + \
			      POD_HEADER_UNKNOWN114_SIZE + \
			      POD_HEADER_UNKNOWN118_SIZE + \
			      POD_HEADER_UNKNOWN11C_SIZE + \
			      POD_HEADER_NEXT_ARCHIVE_SIZE)

#define POD_HEADER_EPD_SIZE  (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_EPD_COMMENT_SIZE + \
			      POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_VERSION_SIZE + \
			      POD_HEADER_CHECKSUM_SIZE)

const ssize_t POD_HEADER_SIZE[POD_IDENT_TYPE_SIZE] =
{
	POD_HEADER_POD1_SIZE,
	POD_HEADER_POD2_SIZE,
	POD_HEADER_POD3_SIZE,
	POD_HEADER_POD4_SIZE,
	POD_HEADER_POD5_SIZE,
	POD_HEADER_EPD_SIZE
}

typedef struct pod_header_pod1_s
{
	pod_number_t file_count;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
} pod_header_pod1_t;

typedef struct pod_header_pod2_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t checksum;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t audit_file_count;
} pod_header_pod2_t;

typedef struct pod_header_pod3_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t checksum;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t audit_file_count;
	pod_number_t revision;
	pod_number_t priority;
	pod_char_t author[POD_HEADER_AUTHOR_SIZE];
	pod_char_t copyright[POD_HEADER_COPYRIGHT_SIZE];
	pod_number_t index_offset;
	pod_number_t unknown10c;
	pod_number_t size_index;
	pod_number_t unknown114;
	pod_number_t unknown118;
	pod_number_t unknown11C;
} pod_header_pod3_t;

typedef struct pod_header_pod4_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t checksum;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t audit_file_count;
	pod_number_t revision;
	pod_number_t priority;
	pod_char_t author[POD_HEADER_AUTHOR_SIZE];
	pod_char_t copyright[POD_HEADER_COPYRIGHT_SIZE];
	pod_number_t index_offset;
	pod_number_t unknown10c;
	pod_number_t size_index;
	pod_number_t unknown114;
	pod_number_t unknown118;
	pod_number_t unknown11C;
} pod_header_pod4_t;

typedef struct pod_header_pod5_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t checksum;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t audit_file_count;
	pod_number_t revision;
	pod_number_t priority;
	pod_char_t author[POD_HEADER_AUTHOR_SIZE];
	pod_char_t copyright[POD_HEADER_COPYRIGHT_SIZE];
	pod_number_t index_offset;
	pod_number_t unknown10c;
	pod_number_t size_index;
	pod_number_t unknown114;
	pod_number_t unknown118;
	pod_number_t unknown11C;
	pod_char_t next_archive[POD_HEADER_NEXT_ARCHIVE_SIZE];
} pod_header_pod5_t;

typedef struct pod_header_epd_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_char_t comment[POD_HEADER_EPD_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t version;
	pod_number_t checksum;
} pod_header_epd_t;

/* pod_dir_entry_t element sizes */
#define POD_DIR_ENTRY_FILENAME_SIZE          256
#define POD_DIR_ENTRY_EPD_FILENAME_SIZE      64
#define POD_DIR_ENTRY_POD1_FILENAME_SIZE     32

#define POD_DIR_ENTRY_NUMBER_SIZE            POD_NUMBER_SIZE
#define POD_DIR_ENTRY_SIZE_SIZE              POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_OFFSET_SIZE            POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_PATH_OFFSET_SIZE       POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_UNCOMPRESS_SIZE        POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_COMPRESSION_LEVEL_SIZE POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_TIMESTAMP_SIZE         POD_DIR_ENTRY_NUMBER_SIZE
#define POD_DIR_ENTRY_CHECKSUM_SIZE          POD_DIR_ENTRY_NUMBER_SIZE


/* 40 bytes */
#define POD_DIR_ENTRY_POD1_SIZE (POD_DIR_ENTRY_POD1_FILENAME_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE)
/* 80 bytes */
#define POD_DIR_ENTRY_EPD_SIZE (POD_DIR_ENTRY_EPD_FILENAME_SIZE + \
                                POD_DIR_ENTRY_SIZE_SIZE + \
				POD_DIR_ENTRY_OFFSET_SIZE + \
				POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				POD_DIR_ENTRY_CHECKSUM_SIZE) 

/* 20 bytes */
#define POD_DIR_ENTRY_POD2_SIZE (POD_DIR_ENTRY_PATH_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE + \
				 POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				 POD_DIR_ENTRY_CHECKSUM_SIZE + \
				 POD_DIR_ENTRY_FILENAME_SIZE)

#define POD_DIR_ENTRY_POD3_SIZE POD_DIR_ENTRY_POD2_SIZE

/* 28 bytes */
#define POD_DIR_ENTRY_POD4_SIZE (POD_DIR_ENTRY_PATH_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE + \
				 POD_DIR_ENTRY_UNCOMPRESSED_SIZE + \
				 POD_DIR_ENTRY_COMPRESSION_LEVEL_SIZE + \
				 POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				 POD_DIR_ENTRY_CHECKSUM_SIZE + \
				 POD_DIR_ENTRY_FILENAME_SIZE)

#define POD_DIR_ENTRY_POD5_SIZE POD_DIR_ENTRY_POD4_SIZE

const ssize_t POD_DIR_ENTRY_SIZE[POD_IDENT_TYPE_SIZE] = \
{
	POD_DIR_ENTRY_POD1_SIZE,
	POD_DIR_ENTRY_POD2_SIZE,
	POD_DIR_ENTRY_POD3_SIZE,
	POD_DIR_ENTRY_POD4_SIZE,
	POD_DIR_ENTRY_POD5_SIZE,
	POD_DIR_ENTRY_EPD_SIZE
}

typedef struct pod1_entry_s {
	pod_char_t name[POD_DIR_ENTRY_POD1_FILENAME_SIZE];
	pod_number_t size;
	pod_number_t offset;
} pod1_entry_t;

typedef struct epd_entry_s {
	pod_char_t name[POD_DIR_ENTRY_EPD_FILENAME_SIZE];
	pod_number_t size;
	pod_number_t offset;
	pod_number_t timestamp;
	pod_number_t checksum;
} epd_entry_t;

typedef struct pod2_entry_s {
	pod_number_t path_offset;
	pod_number_t size;
	pod_number_t offset;
	pod_number_t timestamp;
	pod_number_t checksum;
	pod_char_t name[POD_DIR_ENTRY_FILENAME_SIZE];
} pod2_entry_t;

typedef struct pod3_entry_s {
	pod_number_t path_offset;
	pod_number_t size;
	pod_number_t offset;
	pod_number_t timestamp;
	pod_number_t checksum;
} pod3_entry_t;

typedef struct pod4_entry_s {
	pod_number_t path_offset;
	pod_number_t size;
	pod_number_t offset;
	pod_number_t uncompressed;
	pod_number_t compression_level;
	pod_number_t timestamp;
	pod_number_t checksum;
} pod4_entry_t;

typedef struct pod5_entry_s {
	pod_number_t path_offset;
	pod_number_t size;
	pod_number_t offset;
	pod_number_t uncompressed;
	pod_number_t compression_level;
	pod_number_t timestamp;
	pod_number_t checksum;
} pod5_entry_t;

typedef struct pod_dir_entry_s {
	char* filename[POD_IDENT_TYPE_SIZE];
	uint32_t file_path_offset;
	uint32_t file_size;
	uint32_t file_offset;
	uint32_t file_uncompressed_size;
	uint32_t file_compression_level;
	uint32_t file_timestamp;
	uint32_t file_checksum;
} pod_dir_entry_t;

bool_t pod_dir_entry_write(FILE* file, pod_dir_entry_t* src, int pod_type)
{
	switch(pod_type)
	{
		case POD1:
			
		case POD2:
		case POD3:
		case POD4:
		case POD5:
		case EPD:
		default:
		break;
	}

	return FALSE;
}

pod resentry_to_pod_dir_entry(pod_dir_entry_t* src, resentry_t *re)
{
}

#define RES_ENTRY_NAME_SIZE 12
#define RES_ENTRY_OFFSET_SIZE 4
#define RES_ENTRY_SIZE_SIZE 4
#define RES_ENTRY_SIZE (RES_ENTRY_NAME_SIZE +  RES_ENTRY_OFFSET_SIZE + \
	RES_ENTRY_SIZE_SIZE)

int pod_type(restable_t * rt)
{
  char ident[4];

  if (readf(rt->file, "c4", ident) == OK)
  {
	  for(int i = 0; i < POD_IDENT_TYPE_SIZE; i++)
	  {
		  char * pod_ident = &POD_IDENT[i][0];
		  if (strncmp(ident, pod_ident, strlen(pod_ident_c)) == 0)
			  return i;
	  }
  }
  return POD1;
}

bool_t is_pod(restable_t * rt)
{
  return (POD_IDENT_TYPE_SIZE > pod_type(restable_t * rt) >= 0);
}

bool_t is_pod1(restable_t * rt)
{
  return (POD1 == pod_type(restable_t * rt) >= 0);
}

bool_t is_pod2(restable_t * rt)
{
  return (POD2 == pod_type(restable_t * rt) >= 0);
}

bool_t is_pod3(restable_t * rt)
{
  return (POD3 == pod_type(restable_t * rt) >= 0);
}

bool_t is_pod4(restable_t * rt)
{
  return (POD4 == pod_type(restable_t * rt) >= 0);
}

bool_t is_pod5(restable_t * rt)
{
  return (POD5 == pod_type(restable_t * rt) >= 0);
}

bool_t is_epd(restable_t * rt)
{
  return (EPD == pod_type(restable_t * rt) >= 0);
}


bool_t pod1_read_entry(FILE * file, resentry_t * re)
{
  pod1_entry_t pod_entry;
  
  if (readf(file, "cnlnln", pod_entry.name, POD_DIR_ENTRY_POD1_FILENAME_SIZE,
                            &(pod_entry.size), POD_DIR_ENTRY_SIZE_SIZE,
			    &(pod_entry.offset), POD_DIR_ENTRY_OFFSET_SIZE) != OK)
  {
    fprintf(stderr, "pod1_read_entry: Can't read entry.\n");
    return FALSE;
  }
  re->size = pod_entry.size;
  re->offset = pod_entry.offset;
  re->compressed = re->size;

  re->offset += POD_DIR_ENTRY_POD1_SIZE;

  s_strncpy(&(re->name), pod_entry.name, POD_DIR_ENTRY_POD1_FILENAME_SIZE);
  return TRUE;
}

bool_t epd_read_entry(FILE * file, resentry_t * re)
{
  epd_entry_t pod_entry;
  
  if (readf(file, "cnlnln", pod_entry.name, POD_DIR_ENTRY_EPD_FILENAME_SIZE,
                            &(pod_entry.size), POD_DIR_ENTRY_SIZE_SIZE,
			    &(pod_entry.offset), POD_DIR_ENTRY_OFFSET_SIZE,
			    &(pod_entry.timestamp), POD_DIR                              _ENTRY_TIMESTAMP_SIZE,
			    &(pod_entry.checksum), POD_DIR_ENTRY_CHECKSUM_SIZE) != OK)
  {
    fprintf(stderr, "epd_read_entry: Can't read entry.\n");
    return FALSE;
  }
  re->size = pod_entry.size;
  re->offset = pod_entry.offset;
  re->time = pod_entry.timestamp;

  re->compressed = re->size;

  re->offset += POD_DIR_ENTRY_EPD_SIZE;

  s_strncpy(&(re->name), pod_entry.name, POD_DIR_ENTRY_EPD_FILENAME_SIZE);
  return TRUE;
}

bool_t pod2_read_entry(FILE * file, resentry_t * re)
{
  pod2_entry_t pod_entry;
  
  if (readf(file, "lnlnlnlnlncn", 
  			      &(pod_entry.path_offset, POD_DIR_ENTRY_PATH_OFFSET_SIZE,
                              &(pod_entry.size), POD_DIR_ENTRY_SIZE_SIZE,
			      &(pod_entry.offset), POD_DIR_ENTRY_OFFSET_SIZE,
			      &(pod_entry.timestamp), POD_DIR_ENTRY_TIMESTAMP_SIZE,
			      &(pod_entry.checksum), POD_DIR_ENTRY_CHECKSUM_SIZE,
  			      &(pod_entry.name), POD_DIR_ENTRY_FILENAME_SIZE) != OK)
  {
    fprintf(stderr, "pod1_read_entry: Can't read entry.\n");
    return FALSE;
  }

  re->size = pod_entry.size;
  re->offset = pod_entry.offset;
  re->time = pod_ent
  re->compressed = re->size;

  re->offset += POD_DIR_ENTRY_POD2_SIZE;

  s_strncpy(&(re->name), pod2_entry.name, POD_DIR_ENTRY_POD2_FILENAME_SIZE);
  return TRUE;
}

bool_t pod2_read_entry(FILE * file, resentry_t * re)
{
  pod2_entry_t pod_entry;
  
  if (readf(file, "lnlnlnlnlncn", 
  			      &(pod_entry.path_offset, POD_DIR_ENTRY_PATH_OFFSET_SIZE,
                              &(pod_entry.size), POD_DIR_ENTRY_SIZE_SIZE,
			      &(pod_entry.offset), POD_DIR_ENTRY_OFFSET_SIZE,
			      &(pod_entry.timestamp), POD_DIR_ENTRY_TIMESTAMP_SIZE,
			      &(pod_entry.checksum), POD_DIR_ENTRY_CHECKSUM_SIZE) != OD)
	
  			      &(pod_entry.name), POD_DIR_ENTRY_FILENAME_SIZE) != OK)
  {
    fprintf(stderr, "pod1_read_entry: Can't read entry.\n");
    return FALSE;
  }

  re->size = pod_entry.size;
  re->offset = pod_entry.offset;
  re->time = pod_ent
  re->compressed = re->size;

  re->offset += POD_DIR_ENTRY_POD2_SIZE;

  s_strncpy(&(re->name), pod2_entry.name, POD_DIR_ENTRY_POD2_FILENAME_SIZE);
  return TRUE;
}

bool_t pod1_write_entry(FILE * file, resentry_t * re)
{
  pod1_entry_t pod_entry;
  pod_entry.size = re->size;
  pod_entry.offset = re->offset;

  if (strlen(re->name) > POD_DIR_ENTRY_POD1_FILENAME_SIZE)
  {
    fprintf(stderr, "pod1_write_entry: Name too long for entry.\n");
    return FALSE;
  }
  strncpy(pod_entry.name, re->name, POD_DIR_ENTRY_POD1_FILENAME_SIZE);

  if (writef(file, "cnlnln",
             pod_entry.name, POD_DIR_ENTRY_POD1_FILENAME_SIZE,
	     re->size, re->offset - POD1_ENTRY_SIZE) != OK)
  {
    fprintf(stderr, "pod1_write_entry: Can't write entry.\n");
    return FALSE;
  }
  return TRUE;
}


bool_t epd_write_entry(FILE * file, resentry_t * re)
{
  eod_entry_t pod_entry;
  pod_entry.size = re->size;
  pod_entry.offset = re->offset;
  pod_entry.timestamp = re->time ? re->time : POD_ENTRY_TIMESTAMP_DEFAULT;
  pod_entry.checksum = POD_ENTRY_CHECKSUM_DEFAULT;

  if (strlen(re->name) > POD_DIR_ENTRY_EPD_FILENAME_SIZE)
  {
    fprintf(stderr, "epd_write_entry: Name too long for entry.\n");
    return FALSE;
  }
  strncpy(pod_entry.name, re->name, POD_DIR_ENTRY_EPD_FILENAME_SIZE);

  if (writef(file, "cnlnln",
             pod_entry.name, POD_DIR_ENTRY_EPD_FILENAME_SIZE,
	     re->size, re->offset - EPD_ENTRY_SIZE) != OK)
  {
    fprintf(stderr, "epd_write_entry: Can't write entry.\n");
    return FALSE;
  }
  return TRUE;
}

bool_t pod2_write_entry(FILE * file, resentry_t * re)
{
  pod2_entry_t pod_entry;
  pod_entry.path_offset;
  pod_entry.size = re->size;
  pod_entry.offset = re->offset;
  pod_entry.timestamp = re->time ? re->time : POD_ENTRY_TIMESTAMP_DEFAULT;
  pod_entry.checksum = POD_ENTRY_CHECKSUM_DEFAULT;
  if (strlen(re->name) > POD_DIR_ENTRY_FILENAME_SIZE)
  {
    fprintf(stderr, "pod2_write_entry: Name too long for entry.\n");
    return FALSE;
  }
  strncpy(pod_entry.name, re->name, POD_DIR_ENTRY_EPD_FILENAME_SIZE);

  if (writef(file, "cnlnlnln",
             pod_entry.name, POD_DIR_ENTRY_FILENAME_SIZE,
	     re->size, re->offset - POD2_ENTRY_SIZE) != OK)
  {
    fprintf(stderr, "pod2_write_entry: Can't write entry.\n");
    return FALSE;
  }
  return TRUE;
}

bool_t pod1_read_dir(restable_t * rt)
{
  pod_header_pod1_t pod_header;
  size_t i;

  if (readf(rt->file, "lncn", 
            &pod_header.file_count, POD_HEADER_FILE_COUNT_SIZE,
            pod_header.comment, POD_HEADER_COMMENT_SIZE , NULL) != OK)
  {
    fprintf(stderr, "pod1_read_dir: Can't read header.\n");
    return FALSE;
  }

  if (rt_set_number(rt, pod_header.file_count - 1) == FALSE)
  {
    fprintf(stderr, "pod1_read_dir: Can't resize entries.\n");
    return FALSE;
  }
  for(i = 0; i < rt->number; i++)
  {
    if (pod1_read_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  return TRUE;
}

bool_t pod2_read_dir(restable_t * rt)
{
  pod_header_pod2_t pod_header;
  size_t i;

  if (readf(rt->file, "cnlncnlnln", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                    &pod_header.checksum, POD_HEADER_CHECKSUM_SIZE,
				    pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				    &pod_header.file_count, POD_HEADER_FILE_COUNT_SIZE,
				    &pod_header.audit_file_count, POD_HEADER_AUDIT_FILE_COUNT_SIZE, NULL) != OK)
  {
    fprintf(stderr, "pod2_read_dir: Can't read header.\n");
    return FALSE;
  }

  if (rt_set_number(rt, pod_header.file_count - 1) == FALSE)
  {
    fprintf(stderr, "pod2_read_dir: Can't resize entries.\n");
    return FALSE;
  }

  for(i = 0; i < rt->number; i++)
  {
    if (pod2_read_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  return TRUE;
}

bool_t pod3_read_dir(restable_t * rt)
{
  pod_header_pod3_t pod_header;
  size_t i;

  if (readf(rt->file, "cnlncnlnlnlnlncncnlnlnlnlnlnln", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                   &pod_header.checksum, POD_HEADER_CHECKSUM_SIZE,
				   pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				   &pod_header.file_count, POD_HEADER_FILE_COUNT_SIZE,
				   &pod_header.audit_file_count, POD_HEADER_AUDIT_FILE_COUNT_SIZE,
				   &pod_header.revision, POD_HEADER_REVISION_SIZE,
				   &pod_header.priority, POD_HEADER_PRIORITY_SIZE,
				   pod_header.author, POD_HEADER_AUTHOR_SIZE,
				   pod_header.copyright, POD_HEADER_COPYRIGHT_SIZE,
	  			   &pod_header.index_offset, POD_HEADER_INDEX_OFFSET_SIZE,
				   &pod_header.unknown10c, POD_HEAER_UNKNOWN10C_SIZE,
                                   &pod_header.size_index, POD_HEADER_SIZE_INDEX_SIZE,
 				   &pod_header.unknown114, POD_HEADER_UNKNOWN114_SIZE,
                                   &pod_header.unknown118, POD_HEADER_UNKNOWN118_SIZE,
                                   &pod_header.unknown11C, POD_HEADER_UNKNOWN11C_SIZE, NULL) != OK)
  {
    fprintf(stderr, "pod3_read_dir: Can't read header.\n");
    return FALSE;
  }

  if (rt_set_number(rt, pod_header.file_count - 1) == FALSE)
  {
    fprintf(stderr, "pod3_read_dir: Can't resize entries.\n");
    return FALSE;
  }

  for(i = 0; i < rt->number; i++)
  {
    if (pod3_read_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  return TRUE;
}

bool_t pod4_read_dir(restable_t * rt)
{
  pod_header_pod4_t pod_header;
  size_t i;

  if (readf(rt->file, "cnlncnlnlnlnlncncnlnlnlnlnlnln", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                   &pod_header.checksum, POD_HEADER_CHECKSUM_SIZE,  
				   pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				   &pod_header.file_count, POD_HEADER_FILE_COUNT_SIZE,
				   &pod_header.audit_file_count, POD_HEADER_AUDIT_FILE_COUNT_SIZE,
				   &pod_header.revision, POD_HEADER_REVISION_SIZE,
				   &pod_header.priority, POD_HEADER_PRIORITY_SIZE,
				   pod_header.author, POD_HEADER_AUTHOR_SIZE,
				   pod_header.copyright, POD_HEADER_COPYRIGHT_SIZE,
	  			   &pod_header.index_offset, POD_HEADER_INDEX_OFFSET_SIZE,
				   &pod_header.unknown10c, POD_HEADER_UNKNOWN10C_SIZE,
                                   &pod_header.size_index, POD_HEADER_SIZE_INDEX_SIZE,
 				   &pod_header.unknown114, POD_HEADER_UNKNOWN114_SIZE,
                                   &pod_header.unknown118, POD_HEADER_UNKNOWN118_SIZE,
                                   &pod_header.unknown11C, POD_HEADER_UNKNOWN11C_SIZE, NULL) != OK)
  {
    fprintf(stderr, "pod4_read_dir: Can't read header.\n");
    return FALSE;
  }

  if (rt_set_number(rt, pod_header.file_count - 1) == FALSE)
  {
    fprintf(stderr, "pod4_read_dir: Can't resize entries.\n");
    return FALSE;
  }

  for(i = 0; i < rt->number; i++)
  {
    if (pod4_read_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  return TRUE;
}

bool_t pod5_read_dir(restable_t * rt)
{
  pod_header_pod5_t pod_header;
  size_t i;

  if (readf(rt->file, "cnlncnlnlnlnlncncnlnlnlnlnlnlncn", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                   &pod_header.checksum, POD_HEADER_CHECKSUM_SIZE, 
				   pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				   &pod_header.file_count, POD_HEADER_FILE_COUNT_SIZE,
				   &pod_header.audit_file_count, POD_HEADER_AUDIT_FILE_COUNT_SIZE,
				   &pod_header.revision, POD_HEADER_REVISION_SIZE,
				   &pod_header.priority, POD_HEADER_PRIORITY_SIZE,
				   pod_header.author, POD_HEADER_AUTHOR_SIZE,
				   pod_header.copyright, POD_HEADER_COPYRIGHT_SIZE,
	  			   &pod_header.index_offset, POD_HEADER_INDEX_OFFSET_SIZE,
				   &pod_header.unknown10c, POD_HEADER_UNKNOWN10C_SIZE,
                                   &pod_header.size_index, POD_HEADER_SIZE_INDEX_SIZE,
 				   &pod_header.unknown114, POD_HEADER_UNKNOWN114_SIZE,
                                   &pod_header.unknown118, POD_HEADER_UNKNOWN118_SIZE,
                                   &pod_header.unknown11C, POD_HEADER_UNKNOWN11C_SIZE, 
				   &pod_header.next_archive, POD_HEADER_NEXT_ARCHIVE_SIZE, NULL) != OK)
  {
    fprintf(stderr, "pod5_read_dir: Can't read header.\n");
    return FALSE;
  }

  if (rt_set_number(rt, pod_header.file_count - 1) == FALSE)
  {
    fprintf(stderr, "pod5_read_dir: Can't resize entries.\n");
    return FALSE;
  }

  for(i = 0; i < rt->number; i++)
  {
    if (pod5_read_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  return TRUE;
}

bool_t epd_read_dir(restable_t * rt)
{
  pod_header_epd_t pod_header;
  size_t i;

  if (readf(rt->file, "cncnlnlnln", pod_header.ident, POD_HEADER_IDENT_SIZE, 
				    pod_header.comment, POD_HEADER_EPD_COMMENT_SIZE, 
				    &pod_header.file_count, POD_HEADER_FILE_COUNT_SIZE,
                                    &pod_header.version, POD_HEADER_VERSION_SIZE,
				    &pod_header.checksum, POD_HEADER_CHECKSUM_SIZE, NULL) != OK)
  {
    fprintf(stderr, "epd_read_dir: Can't read header.\n");
    return FALSE;
  }

  if (rt_set_number(rt, pod_header.file_count - 1) == FALSE)
  {
    fprintf(stderr, "epd_read_dir: Can't resize entries.\n");
    return FALSE;
  }

  for(i = 0; i < rt->number; i++)
  {
    if (epd_read_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  return TRUE;
}

bool_t pod_fill_name(resentry_t* re)
{
  s_strcpy(&(re->name), re->filename);
  s_strupper(re->name);
  if (is_dos_filename(re->name) == FALSE)
  {
    fprintf(stderr, "pod_fill_name: \"%s\" is not DOS filename.\n", re->name);
    return FALSE;
  }
  return TRUE;
}

bool_t pod_prepare_dir(restable_t * rt)
{
  fseek(rt->file, POD_HEADER_SIZE + POD_DIR_ENTRY_SIZE * rt->number, SEEK_SET);
  return TRUE;
}

bool_t pod1_write_dir(restable_t * rt)
{
  size_t i;
  size_t offset;

  offset = ftell(rt->file);
  fseek(rt->file, 0, SEEK_SET);
  if (writef(rt->file, "c12l4b4b4b4l4z4",
             RES_IDENT,
             rt->number + 1,
             0x7F91A2F8,
             0xADDEEDAC,
             0xADDEEDAC, rt->entries[0].offset - RES_ENTRY_SIZE) != OK)
  {
    fprintf(stderr, "grp_read_dir: Can't write header.\n");
    return FALSE;
  }
  for(i = 0; i < rt->number; i++)
  {
    if (res_write_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  for(i = 0; i < rt->number - 1; i++)
  {
    fseek(rt->file, rt->entries[i].offset - RES_ENTRY_SIZE, SEEK_SET);
    if (res_write_entry(rt->file, &(rt->entries[i + 1])) == FALSE)
      return FALSE;
  }
  fseek(rt->file, rt->entries[rt->number - 1].offset - RES_ENTRY_SIZE,
        SEEK_SET);
  if (res_write_entry(rt->file, &(rt->entries[0])) == FALSE)
    return FALSE;
  fseek(rt->file, offset, SEEK_SET);
  return TRUE;
}

bool_t pod_add_resource(restable_t * rt, size_t i)
{
  char *filename;

  if (writec(rt->file, NULL, RES_ENTRY_SIZE) != OK)
  {
    fprintf(stderr, "pod_add_resource: Can't write header of entry #%zu.\n", i);
    s_free(&filename);
    return FALSE;
  }

  filename = NULL;
  rt->entries[i].offset = ftell(rt->file);
  s_strcpy(&filename, rt->basepath);
  s_strcat(&filename, rt->entries[i].filename);
  if (fadd(rt->file, filename, &(rt->entries[i].size)) == FALSE)
  {
    fprintf(stderr, "pod_add_resource: Can't open or read file \"%s\".\n",
            filename);
    s_free(&filename);
    return FALSE;
  }
  s_free(&filename);
  return TRUE;
}

bool_t pod3_read_header(restable *rt, pod3_header_t* header)
{
  if(readf(rt->file, "cnlncnlnlnlnlncncnlnlnlnlnlnln", header->ident, POD_HEADER_IDENT_SIZE,
                                                       &(header->checksum), POD_HEADER_CHECKSUM_SIZE,
						       header->comment, POD_HEADER_COMMENT_SIZE,
						       &(header->file_count), POD_HEADER_FILE_COUNT_SIZE,
						       &(header->audit_file_count), POD_HEADER_AUDIT_FILE_COUNT_SIZE,
						       &(header->revision), POD_HEADER_REVISION_SIZE,
						       &(header->priority), POD_HEADER_PRIORITY_SIZE,
						       header->author, POD_HEADER_AUTHOR_SIZE,
						       header->copyright, POD_HEADER_AUTHOR_SIZE,
						       &(header->index_offset, POD_HEADER_INDEX_OFFSET_SIZE,
						       &(header->unknown10c), POD_HEADER_UNKNOWN10C_SIZE,
						       &(header->size_index), POD_HEADER_SIZE_INDEX_SIZE,
						       &(header->unknown114), POD_HEADER_UNKNOWN114_SIZE,
						       &(header->unknown118), POD_HEADER_UNKNOWN118_SIZE,
						       &(header->unknown11c), POD_HEADER_UNKNOWN11C_SIZE) != OK))
  	return FALSE;
  return TRUE;
}

bool_t pod3_add_resource(restable_t * rt, size_t i)
{
  char *filename;
  pod3_header_t header;

  if (writec(rt->file, NULL, RES_ENTRY_SIZE) != OK)
  {
    fprintf(stderr, "pod_add_resource: Can't write header of entry #%zu.\n", i);
    s_free(&filename);
    return FALSE;
  }

typedef struct pod_header_pod3_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t checksum;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t audit_file_count;
	pod_number_t revision;
	pod_number_t priority;
	pod_char_t author[POD_HEADER_AUTHOR_SIZE];
	pod_char_t copyright[POD_HEADER_COPYRIGHT_SIZE];
	pod_number_t index_offset;
	pod_number_t unknown10c;
	pod_number_t size_index;
	pod_number_t unknown114;
	pod_number_t unknown118;
	pod_number_t unknown11C;
} pod_header_pod3_t;

  
  if (pod3_header_read(rt, header) == FALSE)
  {
  	fprintf(stderr, "pod3_header_read: Can't read header of POD3 file \"%s\".\n", 
	        rt->file.filename);
	return FALSE;
  }

  rt->set_number(rt, header.file_count);
  seekf(rt->file, header->index_offset + (i * DIR_ENTRY_SIZE), SEEK_SET);
  if(readf(rt->file, "ln", header->entries[i].path_offset, POD_HEADER_PATH_OFFSET_SIZE) != OK)
  {
  	fprintf(stderr, "readf: Can't read path_offset of POD3 entry \"%s\".\n",
		rt->file.filename);
	return FALSE;
  }

  seekf(rt->file, header->index_offset + (header->file_count * DIR_ENTRY_SIZE) + header->entries[i].path_offset, SEEK_SET);
  if(readf(rt->file, "cn", header->entries[i].filename, POD_DIR_ENTRY_FILENAME_SIZE) != OK)
  {
  	fprintf(stderr, "readf: Can't read filename of POD3 entry of file \"%s\".\n",
	        rt->file.filename);
  }


  filename = NULL;
  rt->entries[i].offset = ftell(rt->file);
  s_strcpy(&filename, rt->basepath);
  s_strcat(&filename, rt->entries[i].filename);

  if (fadd(rt->file, filename, &(rt->entries[i].size)) == FALSE)
  {
    fprintf(stderr, "pod_add_resource: Can't open or read file \"%s\".\n",
            filename);
    s_free(&filename);
    return FALSE;
  }

  s_free(&filename);
  return TRUE;
}
