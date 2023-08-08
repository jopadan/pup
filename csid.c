#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bin.h"
#include "csid.h"

#define CSID_IDENT "CSid"

#define CSID_HEADER_IDENT_SIZE 4
#define CSID_HEADER_NUMBER_SIZE 2
#define CSID_HEADER_SIZE (CSID_HEADER_IDENT_SIZE + \
	CSID_HEADER_NUMBER_SIZE)

#define CSID_ENTRY_FILENAME_LENGTH_SIZE 1
#define CSID_ENTRY_FILENAME_SIZE 12
#define CSID_ENTRY_SIZE_SIZE 4
#define CSID_ENTRY_OFFSET_SIZE 4
#define CSID_ENTRY_SIZE (CSID_ENTRY_FILENAME_LENGTH_SIZE + \
                         CSID_ENTRY_FILENAME_SIZE + \
                         CSID_ENTRY_SIZE_SIZE + \
                         CSID_ENTRY_OFFSET_SIZE)

bool_t is_csid(restable_t * rt)
{
  char ident[CSID_HEADER_IDENT_SIZE];

  if (readf(rt->file, "c4", ident) != OK)
    return FALSE;
  if (strncmp(ident, CSID_IDENT, CSID_HEADER_IDENT_SIZE) != 0)
    return FALSE;
  return TRUE;
}

bool_t csid_fill_filename(resentry_t * re)
{
  char name[CSID_ENTRY_FILENAME_SIZE];

  if (strlen(re->name) > CSID_ENTRY_FILENAME_SIZE)
    return FALSE;
  snprintf(name, CSID_ENTRY_FILENAME_SIZE, "%s.%zu", re->name, re->type);
  s_strlower(name);
  s_strcpy(&(re->filename), name);
  if (re->filename == NULL)
    return FALSE;
  return TRUE;
}

bool_t csid_fill_name(resentry_t * re)
{
  char *ext;

  ext = NULL;

  s_name(&(re->name), re->filename, SYS_PATH_DELIM);
  s_strupper(re->name);

  s_ext(&ext, re->filename, SYS_PATH_DELIM);
  if (ext[0] != '.')
  {
    fprintf(stderr, "csid_fill_name: filename haven't extension.\n");
    re->type = 0;
  }
  else
    re->type = atoi(&(ext[1]));
  s_free(&ext);

  if (strlen(re->name) > CSID_ENTRY_FILENAME_SIZE)
  {
    fprintf(stderr, "csid_fill_name: Too long name \"%s\".\n", re->name);
    return FALSE;
  }
  return TRUE;
}

bool_t csid_prepare_dir(restable_t * rt)
{
  fseek(rt->file, CSID_HEADER_SIZE, SEEK_SET);
  return TRUE;
}

bool_t csid_write_dir(restable_t * rt)
{
  char ident[CSID_HEADER_IDENT_SIZE];
  size_t i;
  size_t offset;

  offset = ftell(rt->file);
  fseek(rt->file, 0, SEEK_SET);
  if (writef(rt->file, "c4l2", ident, rt->number) != OK)
  {
    fprintf(stderr, "csid_write_dir: Can't write header.\n");
    return FALSE;
  }
  fseek(rt->file, offset, SEEK_SET);
  for(i = 0; i < rt->number; i++)
  {
    if (writef(rt->file, "l1c12l4l4",
               CSID_ENTRY_FILENAME_SIZE,
               rt->entries[i].filename,
               rt->entries[i].size,
               rt->entries[i].offset) != OK)
    {
      fprintf(stderr, "csid_write_dir: Can't write entry #%zu.\n", i);
      return FALSE;
    }
  }
  return TRUE;
}

bool_t csid_read_dir(restable_t * rt)
{
  char ident[CSID_HEADER_IDENT_SIZE];
  uint16_t number;
  uint8_t fn_len;
  size_t i;

  if (readf(rt->file, "c4l2", ident, &number) != OK)
  {
    fprintf(stderr, "csid_read_dir: Can't read header.\n");
    return FALSE;
  }
  if ((strncmp(ident, CSID_IDENT, CSID_HEADER_IDENT_SIZE) != 0))
  {
    fprintf(stderr, "csid_read_dir: Wrong ident.\n");
    return FALSE;
  }
  if (rt_set_number(rt, number) == FALSE)
  {
    fprintf(stderr, "csid_read_dir: Can't resize entries.\n");
    return FALSE;
  }
  for(i = 0; i < rt->number; i++)
  {
    if (readf(rt->file, "l1c12l4l4",
              &(fn_len),
              &(rt->entries[i].filename),
              &(rt->entries[i].size),
              &(rt->entries[i].offset)) != OK)
    {
      fprintf(stderr, "csid_read_dir: Can't read entry #%zu.\n", i);
      return FALSE;
    }
    if (csid_fill_name(&rt->entries[i]) == FALSE)
    {
      fprintf(stderr, "csid_read_dir: Can't fill name entries.\n");
      return FALSE;
    }
    rt->entries[i].entry = i;
  }
  return TRUE;
}
