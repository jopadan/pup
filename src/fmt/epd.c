#include "epd.h"

#define POD_HEADER_EPD_SIZE  (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_EPD_COMMENT_SIZE + \
			      POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_VERSION_SIZE + \
			      POD_HEADER_CHECKSUM_SIZE)

/* 80 bytes */
#define POD_DIR_ENTRY_EPD_SIZE (POD_DIR_ENTRY_EPD_FILENAME_SIZE + \
                                POD_DIR_ENTRY_SIZE_SIZE + \
				POD_DIR_ENTRY_OFFSET_SIZE + \
				POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				POD_DIR_ENTRY_CHECKSUM_SIZE) 

#define POD_DIR_ENTRY_EPD_FILENAME_SIZE      64

/* EPD header data structure */
typedef struct pod_header_epd_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_char_t comment[POD_HEADER_EPD_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t version;
	pod_number_t checksum;
} pod_header_epd_t;

/* EPD entry data structure */
typedef struct epd_entry_s {
	pod_char_t name[POD_DIR_ENTRY_EPD_FILENAME_SIZE];
	pod_number_t size;
	pod_number_t offset;
	pod_number_t timestamp;
	pod_number_t checksum;
} epd_entry_t;

bool_t is_epd(restable_t * rt)
{
  return (EPD == pod_type(rt) >= 0);
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
