#include "pod3.h"

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
/* 20 bytes */
#define POD_DIR_ENTRY_POD3_SIZE (POD_DIR_ENTRY_PATH_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
				 POD_DIR_ENTRY_OFFSET_SIZE + \
				 POD_DIR_ENTRY_TIMESTAMP_SIZE + \
				 POD_DIR_ENTRY_CHECKSUM_SIZE + \
				 POD_DIR_ENTRY_FILENAME_SIZE)

#define POD_DIR_ENTRY_POD3_FILENAME_SIZE     POD_DIR_ENTRY_FILENAME_SIZE

/* POD3 header data structure */
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

/* POD3 entry data structure */
typedef struct pod3_entry_s {
	pod_number_t path_offset;
	pod_number_t size;
	pod_number_t offset;
	pod_number_t timestamp;
	pod_number_t checksum;
} pod3_entry_t;

bool_t is_pod3(restable_t * rt)
{
  return (POD3 == pod_type(rt) >= 0);
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

  if (addfile(rt->file, filename, &(rt->entries[i].size)) == FALSE)
  {
    fprintf(stderr, "pod_add_resource: Can't open or read file \"%s\".\n",
            filename);
    s_free(&filename);
    return FALSE;
  }

  s_free(&filename);
  return TRUE;
}
