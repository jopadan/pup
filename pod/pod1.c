#include "pod1.h"

#define POD_HEADER_POD1_SIZE (POD_HEADER_FILE_COUNT_SIZE + \
                              POD_HEADER_COMMENT_SIZE)

/* 40 bytes */
#define POD_DIR_ENTRY_POD1_SIZE (POD_DIR_ENTRY_POD1_FILENAME_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE)

#define POD_DIR_ENTRY_POD1_FILENAME_SIZE     32

/* POD1 header data structure */
typedef struct pod_header_pod1_s
{
	pod_number_t file_count;
	pod_char_t comment[POD_HEADER_COMMENT_SIZE];
} pod_header_pod1_t;

/* POD1 entry data structure */
typedef struct pod1_entry_s {
	pod_char_t name[POD_DIR_ENTRY_POD1_FILENAME_SIZE];
	pod_number_t size;
	pod_number_t offset;
} pod1_entry_t;

bool_t is_pod1(restable_t * rt)
{
  return (POD1 == pod_type(rt) >= 0);
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
