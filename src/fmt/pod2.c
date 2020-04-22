#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "pod_common.h"
#include "pod2.h"

#define POD_HEADER_POD2_SIZE (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_CHECKSUM_SIZE + \
			      POD_HEADER_COMMENT_SIZE + \
			      POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_AUDIT_FILE_COUNT_SIZE)


/* 20 bytes */
#define POD_DIR_ENTRY_POD2_SIZE (POD_DIR_ENTRY_PATH_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE + \
				 POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				 POD_DIR_ENTRY_CHECKSUM_SIZE + \
				 POD_DIR_ENTRY_FILENAME_SIZE)

#define POD_DIR_ENTRY_POD2_FILENAME_SIZE     POD_DIR_ENTRY_FILENAME_SIZE
/* POD2 header data structure */
typedef struct pod_header_pod2_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t checksum;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
	pod_number_t file_count;
	pod_number_t audit_file_count;
} pod_header_pod2_t;

/* POD2 entry data structure */
typedef struct pod2_entry_s {
	pod_number_t path_offset;
	pod_number_t size;
	pod_number_t offset;
	pod_number_t timestamp;
	pod_number_t checksum;
	pod_char_t name[POD_DIR_ENTRY_FILENAME_SIZE];
} pod2_entry_t;

typedef struct pod2_audit_entry_s
{
	pod_char_t 
	pod_number_t checksum;
	pod_char_t 

} pod2_audit_entry_t;


bool_t is_pod2(restable_t * rt)
{
  return (POD2 == pod_type(rt) >= 0);
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

bool_t pod2_read_dir(restable_t * rt)
{
	
}
bool_t pod2_fill_filename(resentry_t * re)
{
}

bool_t pod2_fill_name(resentry_t * re)
{
}
bool_t pod2_prepare_dir(restable_t * rt)
{
}
bool_t pod2_add_resource(restable_t * rt, size_t i)
{
}
bool_t pod2_write_dir(restable_t * rt)
{
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

