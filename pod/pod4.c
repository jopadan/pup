#include "pod4.h"

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
/* 28 bytes */
#define POD_DIR_ENTRY_POD4_SIZE (POD_DIR_ENTRY_PATH_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE + \
				 POD_DIR_ENTRY_UNCOMPRESSED_SIZE + \
				 POD_DIR_ENTRY_COMPRESSION_LEVEL_SIZE + \
				 POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				 POD_DIR_ENTRY_CHECKSUM_SIZE + \
				 POD_DIR_ENTRY_FILENAME_SIZE)

#define POD_DIR_ENTRY_POD4_FILENAME_SIZE     POD_DIR_ENTRY_FILENAME_SIZE
/* POD4 header data structure */
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

/* POD4 entry data structure */
typedef struct pod4_entry_s {
	pod_number_t path_offset;
	pod_number_t size;
	pod_number_t offset;
	pod_number_t uncompressed;
	pod_number_t compression_level;
	pod_number_t timestamp;
	pod_number_t checksum;
} pod4_entry_t;


bool_t is_pod4(restable_t * rt)
{
  return (POD4 == pod_type(rt) >= 0);
}

bool_t pod4_read_dir(restable_t * rt)
{
}
bool_t pod4_fill_filename(resentry_t * re)
{
}
bool_t pod4_fill_name(resentry_t * re)
{
}
bool_t pod4_prepare_dir(restable_t * rt)
{
}
bool_t pod4_add_resource(restable_t * rt, size_t i)
{
}
bool_t pod4_write_dir(restable_t * rt)
{
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

