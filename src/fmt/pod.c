#include <stdio.h>
#include <string.h>
#include "bin.h"
#include "res.h"


typedef enum pod_ident_type_e = { POD1 = 0,  POD2,  POD3,  POD4,  POD5,  EPD, } pod_ident_type_t;

#define POD_IDENT_TYPE_SIZE (EPD + 1)

char POD_IDENT[POD_IDENT_TYPE_SIZE][5] = { "\0POD1", "POD2\0", "POD3\0", "POD4\0", "POD5\0", "dtxe\0" };

typedef struct pod_dir_entry_s {
	char* filename[POD_IDENT_TYPE_SIZE] = 
	uint32_t file_path_offset;
	uint32_t file_size;
	uint32_t file_offset;
	uint32_t file_uncompressed_size;
	uint32_t file_compression_level;
	uint32_t file_timestamp;
	uint32_t file_checksum;
} pod_dir_entry_t;

#define POD_HEADER_IDENT_SIZE 4
#define POD_HEADER_NUMBER_SIZE 4
#define POD_HEADER_IDENT_SIZE POD_HEADER_NUMBER_SIZE
#define POD_HEADER_CHECKSUM_SIZE POD_HEADER_NUMBER_SIZE
#define POD_HEADER_FILE_COUNT_SIZE POD_HEADER_NUMBER_SIZE
#define POD_HEADER_AUDIT_FILE_COUNT_Size POD_HwEADER_NUMBER_SIZE
#define POD_HEADER_REVISION_SIZE POD_HEADER_NUMBER_SIZE
#define POD_HEADER_PRIORITY_SIZE POD_HEADER_NUMBER_SIZE
#define POD_HEADER_INDEX_OFFSET_SIZE POD_HEADER_NUMBER_SIZE
#define POD_HEADER_SIZE_INDEX_SIZE POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN10C POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN114 POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN118 POD_HEADER_NUMBER_SIZE
#define POD_HEADER_UNKNOWN11C POD_HEADER_NUMBER_SIZE

#define POD_HEADER_PSEUDONAME_SIZE 12
#define POD_HEADER_SIZE (POD_HEADER_IDENT_SIZE + POD_HEADER_NUMBER_SIZE +\
	POD_HEADER_
#define COMMENT_LENGTH_POD 80
#define COMMENT_LENGTH_EPD 256
#define AUTHOR_LENGTH 80
#define COPYRIGHT_LENGTH 80
#define NEXT_ARCHIVE_LENGTH 80
#define FILENAME_LENGTH 256
#define FILENAME_LENGTH_EPD 64
#define FILENAME_LENGTH_POD 32

#define DIR_ENTRY_SIZE_POD1 40
#define DIR_ENTRY_SIZE_EPD 80
#define DIR_ENTRY_SIZE_POD2_3 20
#define DIR_ENTRY_SIZE_POD4_5 28

#define POD_ENTRY_SIZE_POD1
#define RES_IDENT "RESOURCE2xxx"
#define RES_HEADER_IDENT_SIZE 12
#define RES_HEADER_NUMBER_SIZE 4
#define RES_HEADER_PSEUDONAME_SIZE 12
#define RES_HEADER_FULLSIZE_SIZE 4
#define RES_HEADER_ZEROS_SIZE 4
#define RES_HEADER_SIZE (RES_HEADER_IDENT_SIZE + RES_HEADER_NUMBER_SIZE +\
	RES_HEADER_PSEUDONAME_SIZE + RES_HEADER_FULLSIZE_SIZE + \
	RES_HEADER_ZEROS_SIZE)

#define RES_ENTRY_NAME_SIZE 12
#define RES_ENTRY_OFFSET_SIZE 4
#define RES_ENTRY_SIZE_SIZE 4
#define RES_ENTRY_SIZE (RES_ENTRY_NAME_SIZE +  RES_ENTRY_OFFSET_SIZE + \
	RES_ENTRY_SIZE_SIZE)

bool_t is_pod(restable_t * rt)
{
  return (POD_IDENT_TYPE_SIZE > pod_type(restable_t * rt) >= 0);
}

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

bool_t pod_read_entry(FILE * file, resentry_t * re)
{
  char name[POD_ENTRY_NAME_SIZE];

  
  if (readf(file, "c4l4l4", name, &(re->offset), &(re->size)) != OK)
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

bool_t pod_read_dir(restable_t * rt)
{
  char ident[RES_HEADER_IDENT_SIZE];
  size_t number;
  size_t i;

  if (readf(rt->file, "c12l4c20", ident, &number, NULL) != OK)
  {
    fprintf(stderr, "res_read_dir: Can't read header.\n");
    return FALSE;
  }
  if (strncmp(ident, RES_IDENT, RES_HEADER_IDENT_SIZE) != 0)
  {
    fprintf(stderr, "res_read_dir: Wrong ident.\n");
    return FALSE;
  }
  if (rt_set_number(rt, number - 1) == FALSE)
  {
    fprintf(stderr, "res_read_dir: Can't resize entries.\n");
    return FALSE;
  }
  for(i = 0; i < rt->number; i++)
  {
    if (res_read_entry(rt->file, &(rt->entries[i])) == FALSE)
      return FALSE;
  }
  return TRUE;
}

bool_t pod_fill_filename(resentry_t * re)
{
  s_strcpy(&(re->filename), re->name);
  s_strlower(re->filename);
  if (re->filename == NULL)
    return FALSE;
  return TRUE;
}

bool_t pod_fill_name(resentry_t * re)
{
  s_strcpy(&(re->name), re->filename);
  s_strupper(re->name);
  if (is_dos_filename(re->name) == FALSE)
  {
    fprintf(stderr, "res_fill_name: \"%s\" is not DOS filename.\n", re->name);
    return FALSE;
  }
  return TRUE;
}

bool_t pod_prepare_dir(restable_t * rt)
{
  fseek(rt->file, RES_HEADER_SIZE + RES_ENTRY_SIZE * rt->number, SEEK_SET);
  return TRUE;
}

bool_t pod_write_dir(restable_t * rt)
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
    fprintf(stderr, "res_add_resource: Can't write header of entry #%zu.\n", i);
    s_free(&filename);
    return FALSE;
  }

  filename = NULL;
  rt->entries[i].offset = ftell(rt->file);
  s_strcpy(&filename, rt->basepath);
  s_strcat(&filename, rt->entries[i].filename);
  if (fadd(rt->file, filename, &(rt->entries[i].size)) == FALSE)
  {
    fprintf(stderr, "res_add_resource: Can't open or read file \"%s\".\n",
            filename);
    s_free(&filename);
    return FALSE;
  }
  s_free(&filename);
  return TRUE;
}
