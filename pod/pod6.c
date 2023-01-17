#include "pod6.h"

#define POD_HEADER_POD6_SIZE (POD_HEADER_IDENT_SIZE + \
                              POD_HEADER_FILE_COUNT_SIZE + \
			      POD_HEADER_VERSION_SIZE + \
			      POD_HEADER_INDEX_OFFSET_SIZE + \
			      POD_HEADER_SIZE_INDEX_SIZE)
/* 24 bytes */
#define POD_DIR_ENTRY_POD6_SIZE (POD_DIR_ENTRY_PATH_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_SIZE_SIZE + \
                                 POD_DIR_ENTRY_OFFSET_SIZE + \
                                 POD_DIR_ENTRY_UNCOMPRESSED_SIZE + \
                                 POD_DIR_ENTRY_COMPRESSION_LEVEL_SIZE + \
                                 POD_DIR_ENTRY_ZERO_SIZE)

#define POD_DIR_ENTRY_POD6_FILENAME_SIZE     POD_DIR_ENTRY_FILENAME_SIZE
/* POD6 header data structure */
typedef struct pod_header_pod6_s
{
	pod_char_t ident[POD_HEADER_IDENT_SIZE];
	pod_number_t file_count;
	pod_number_t version;
	pod_number_t index_offset;
	pod_number_t size_index;
} pod_header_pod6_t;

/* POD6 entry data structure */
typedef struct pod6_entry_s {
	pod_number_t path_offset; /* names = &(SEEK_SET + name_offset + header.names_offset] */
	pod_number_t size;
	pod_number_t offset;
	pod_number_t uncompressed;
	pod_number_t compression_level;
	pod_number_t zero;
} pod6_entry_t;

bool_t is_pod6(restable_t * rt)
{
  return (POD6 == pod_type(rt) >= 0);
}
bool_t pod6_read_dir(restable_t * rt)
{
	pod_header_pod6_t pod_header;
	if(readf(rt->file "cnlnlnlnln", pod_header.ident, POD_HEADER_IDENT_SIZE,
			&pod_header.file_count, POD_HEADER_FILE_COUNT_SIZE,
			&pod_header.version, POD_HEADER_VERSION_SIZE,
			&pod_header.info_offset, POD_HEADER_
}
inline ssize_t pod6_header_names_offset(pod_header_pod6_t* header)
{
	if(header == NULL)
	{
    		fprintf(stderr, "pod6_header_names_offset: header == NULL.\n");
		return FALSE;
	}
	return header.index_offset + (POD_DIR_ENTRY_POD6_SIZE * header.file_count);
}

inline bool_t pod6_entry_name(restable_t* rt, pod6_header_t* header, pod6_entry_t* entry)
{
	ssize_t names_offset = pod6_header_names_offset(header) + entry->path_offset;
	seekf(rt->file, names_offset, SEEK_SET);
	if(readf(rt->file, "cn", entry->name, POD_DIR_ENTRY_POD6_NAME_SIZE) != OK)
	{
		fprintf(stderr, "pod6_entry_name: Can't read entry at offset \"%d\" of file \"%s\".\n",
				names_offset, rt->file);
		return FALSE;
	}
	return TRUE; 
}
