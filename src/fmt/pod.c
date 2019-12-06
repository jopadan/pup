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
#define POD_NUMBER_SIZE                      UINT32_WIDTH                  /* length of a numerical entry  */
#define POD_COMMENT_SIZE                     (UINT32_WIDTH + UINT16_WIDTH) /* comment length of POD format */
#define EPD_COMMENT_SIZE                     (UINT8_MAX + 1)               /* comment length of EPD format */
#define POD_IDENT_SIZE                       INT8_WIDTH * 4                /* file magic ident length      */
#define POD_IDENT_TYPE_SIZE                  (EPD + 1)                     /* number of POD format types   */

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
				 POD_DIR_ENTRY_CHECKSUM_SIZE)

#define POD_DIR_ENTRY_POD3_SIZE POD_DIR_ENTRY_POD2_SIZE

/* 28 bytes */
#define POD_DIR_ENTRY_POD4_SIZE (POD_DIR_ENTRY_PATH_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE + \
				 POD_DIR_ENTRY_UNCOMPRESSED_SIZE + \
				 POD_DIR_ENTRY_COMPRESSION_LEVEL_SIZE + \
				 POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				 POD_DIR_ENTRY_CHECKSUM_SIZE)

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
  char name[POD_ENTRY_NAME_SIZE];

  
  if (readf(file, "l4cN", name, &(re->offset), &(re->size)) != OK)
  {
    fprintf(stderr, "res_read_entry: Can't read entry.\n");
    return FALSE;
  }
  re->compressed = re->size;

  re->offset += RES_ENTRY_SIZE;

  s_strncpy(&(re->name), name, RES_ENTRY_NAME_SIZE);
  return TRUE;
}

bool_t pod_write_entry(FILE * file, resentry_t * re)
{
  char name[RES_ENTRY_NAME_SIZE];

  if (strlen(re->name) > RES_ENTRY_NAME_SIZE)
  {
    fprintf(stderr, "res_write_entry: Name too long for entry.\n");
    return FALSE;
  }
  strncpy(name, re->name, RES_ENTRY_NAME_SIZE);


  if (writef(file, "c12l4l4",
             name, re->offset - RES_ENTRY_SIZE, re->size) != OK)
  {
    fprintf(stderr, "res_write_entry: Can't write entry.\n");
    return FALSE;
  }
  return TRUE;
}

bool_t pod1_read_dir(restable_t * rt)
{
  pod_header_pod1_t pod_header;
  size_t i;

  if (readf(rt->file, "l4cn", 
            &pod_header.file_count,
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

  if (readf(rt->file, "cnl4cnl4l4", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                    &pod_header.checksum,
				    pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				    &pod_header.file_count, 
				    &pod_header.audit_file_count, NULL) != OK)
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

  if (readf(rt->file, "cnl4cnl4l4l4l4cncnl4l4l4l4l4l4", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                   &pod_header.checksum,
				   pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				   &pod_header.file_count, 
				   &pod_header.audit_file_count, 
				   &pod_header.revision, 
				   &pod_header.priority,
				   pod_header.author, POD_HEADER_AUTHOR_SIZE,
				   pod_header.copyright, POD_HEADER_COPYRIGHT_SIZE,
	  			   &pod_header.index_offset,
				   &pod_header.unknown10c,
                                   &pod_header.size_index,
 				   &pod_header.unknown114,
                                   &pod_header.unknown118,
                                   &pod_header.unknown11C, NULL) != OK)
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

  if (readf(rt->file, "cnl4cnl4l4l4l4cncnl4l4l4l4l4l4", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                   &pod_header.checksum,
				   pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				   &pod_header.file_count, 
				   &pod_header.audit_file_count, 
				   &pod_header.revision, 
				   &pod_header.priority,
				   pod_header.author, POD_HEADER_AUTHOR_SIZE,
				   pod_header.copyright, POD_HEADER_COPYRIGHT_SIZE,
	  			   &pod_header.index_offset,
				   &pod_header.unknown10c,
                                   &pod_header.size_index,
 				   &pod_header.unknown114,
                                   &pod_header.unknown118,
                                   &pod_header.unknown11C, NULL) != OK)
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

  if (readf(rt->file, "cnl4cnl4l4l4l4cncnl4l4l4l4l4l4", pod_header.ident, POD_HEADER_IDENT_SIZE, 
                                   &pod_header.checksum,
				   pod_header.comment, POD_HEADER_COMMENT_SIZE, 
				   &pod_header.file_count, 
				   &pod_header.audit_file_count, 
				   &pod_header.revision, 
				   &pod_header.priority,
				   pod_header.author, POD_HEADER_AUTHOR_SIZE,
				   pod_header.copyright, POD_HEADER_COPYRIGHT_SIZE,
	  			   &pod_header.index_offset,
				   &pod_header.unknown10c,
                                   &pod_header.size_index,
 				   &pod_header.unknown114,
                                   &pod_header.unknown118,
                                   &pod_header.unknown11C, NULL) != OK)
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

  if (readf(rt->file, "cncnl4l4l4", pod_header.ident, POD_HEADER_IDENT_SIZE, 
				    pod_header.comment, POD_HEADER_EPD_COMMENT_SIZE, 
				    &pod_header.file_count, 
                                    &pod_header.version,
				    &pod_header.checksum, NULL) != OK)
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
