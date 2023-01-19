#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bin.h"
#include "pod.h"

#include <termpod/termpod.h>

#define POD_ENTRY_NAME_SIZE 12
#define POD_ENTRY_OFFSET_SIZE 4
#define POD_ENTRY_SIZE_SIZE 4
#define POD_ENTRY_SIZE (POD_ENTRY_NAME_SIZE +  POD_ENTRY_OFFSET_SIZE + \
	POD_ENTRY_SIZE_SIZE)

bool_t is_pod(restable_t * rt)
{
	return pod_file_is_pod(rt->filename) ? TRUE : FALSE;
}
/*
typedef struct pod_dir_entry_s {
	pod_char_t* filename[POD_FILENAME_SIZE];
	pod_number_t file_path_offset;
	pod_number_t file_size;
	pod_number_t file_offset;
	pod_number_t file_uncompressed_size;
	pod_number_t file_compression_level;
	pod_number_t file_timestamp;
	pod_number_t file_checksum;
} pod_dir_entry_t;

bool_t pod_dir_entry_write(FILE* file, pod_dir_entry_t* src, int pod_type)
{
	switch(pod_type)
	{
		case POD1:
			pod1_write_dir(file, src);
		case POD2:
			pod2_write_dir(file, src);
		case POD3:
			pod3_write_dir(file, src);
		case POD4:
			pod4_write_dir(file, src);
		case POD5:
			pod5_write_dir(file, src);
		case POD6:
			pod6_write_dir(file, src);
		case EPD:
			epd_write_dir(file, src);
		default:
		break;
	}

	return FALSE;
}
*/

bool_t pod_fill_name(resentry_t * re)
{
  char *ext = NULL;

  s_strcpy(&(re->name), re->filename);
  s_strupper(re->name);
  if (is_dos_filename(re->name) == FALSE)
  {
    fprintf(stderr, "pod_fill_name: \"%s\" is not DOS filename.\n", re->name);
    return FALSE;
  }
  return TRUE;

  s_name(&(re->name), re->filename, SYS_PATH_DELIM);
  s_strupper(re->name);

  s_ext(&ext, re->filename, SYS_PATH_DELIM);
  if (ext[0] != '.')
  {
    fprintf(stderr, "pod_fill_name: filename has no extension.\n");
    re->type = 0;
  }
  else
    re->type = atoi(&(ext[1]));
  s_free(&ext);

  if (strlen(re->name) > POD_ENTRY_NAME_SIZE)
  {
    fprintf(stderr, "pod_fill_name: Too long name \"%s\".\n", re->name);
    return FALSE;
  }
  return TRUE;
}

bool_t resentry_to_pod_dir_entry(pod_dir_entry_t* dst, resentry_t *re)
{
	if(!dst)
		return FALSE;

	for(int i = 0; i < POD_IDENT_TYPE_SIZE; i++)
	{
		pod_number_t len = POD_FILENAME_SIZE[i];
		dst->filename[i] = calloc(len, sizeof(pod_char_t));
		strncpy(dst->filename[i], re->filename, len);
	}

/*
	dst->file_path_offset = re->filename
	dst->file_size = re->compressed;
	dst->file_offset = re->offset;
	dst->file_uncompressed_size = re->size;
	dst->file_compression_level = re->compression
	dst->file_timestamp = re->time;
	dst->file_checksum = pod_crc(re->offset);

	dst->id = id 
*/
	return TRUE;
}

bool_t pod_prepare_dir(restable_t * rt)
{
//  fseek(rt->file, POD_HEADER_SIZE[i] + POD_DIR_ENTRY_SIZE[i] * rt->number, SEEK_SET);
  return TRUE;
}

bool_t pod_add_resource(restable_t * rt, size_t i)
{
  char *filename;

  if (writec(rt->file, NULL, POD_ENTRY_SIZE) != OK)
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

bool_t pod_read_dir(restable_t * rt)
{
	if(!rt)
		return FALSE;

	return TRUE;
}
bool_t pod_fill_filename(resentry_t * re)
{
	if(!re)
		return FALSE;

	return TRUE;
}

bool_t pod_write_dir(restable_t * rt)
{
	if(!rt)
		return FALSE;

	return TRUE;
}
