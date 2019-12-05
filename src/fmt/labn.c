#include <stdio.h>
#include <string.h>
#include "bin.h"
#include "labn.h"

#define LABN_IDENT "LABN"
#define LABN_VERSION 0x00010000
#define LABN_HEADER_IDENT_SIZE 4
#define LABN_HEADER_VERSION_SIZE 4
#define LABN_HEADER_NUMBER_SIZE 4
#define LABN_HEADER_NAMES_SIZE 4

#define LABN_HEADER_SIZE (LABN_HEADER_IDENT_SIZE + LABN_HEADER_VERSION_SIZE + \
                          LABN_HEADER_NUMBER_SIZE + LABN_HEADER_NAMES_SIZE)

#define LABN_ENTRY_NAME_OFFSET_SIZE 4
#define LABN_ENTRY_OFFSET_SIZE 4
#define LABN_ENTRY_SIZE_SIZE 4
#define LABN_ENTRY_IDENT_SIZE 4

#define LABN_ENTRY_SIZE (LABN_ENTRY_NAME_OFFSET_SIZE + LABN_ENTRY_OFFSET_SIZE + \
                         LABN_ENTRY_SIZE_SIZE + LABN_ENTRY_IDENT_SIZE)

bool_t is_labn(restable_t * rt)
{
  char ident[LABN_HEADER_IDENT_SIZE];
  size_t version;

  if (readf(rt->file, "c4l4", ident, &version) != OK)
    return FALSE;
  if (strncmp(ident, LABN_IDENT, LABN_HEADER_IDENT_SIZE) != 0)
    return FALSE;
  if (version != LABN_VERSION)
    return FALSE;
  return TRUE;
}

bool_t labn_read_dir(restable_t * rt)
{
  char ident[LABN_HEADER_IDENT_SIZE];
  size_t version;
  size_t number;
  size_t names_size;
  size_t names_offset;
  size_t i;

  if (readf(rt->file, "c4l4l4l4", ident, &version, &number, &names_size) != OK)
  {
    fprintf(stderr, "labn_read_dir: Can't read header.\n");
    return FALSE;
  }
  if (strncmp(ident, LABN_IDENT, LABN_HEADER_IDENT_SIZE) != 0)
  {
    fprintf(stderr, "labn_read_dir: Wrong ident.\n");
    return FALSE;
  }
  if (version != LABN_VERSION)
  {
    fprintf(stderr, "labn_read_dir: Wrong version.\n");
    return FALSE;
  }
  if (rt_set_number(rt, number) == FALSE)
  {
    fprintf(stderr, "labn_read_dir: Can't resize entries.\n");
    return FALSE;
  }
  for(i = 0; i < rt->number; i++)
  {
    if (readf(rt->file, "l4l4l4l4", &(rt->entries[i].id), /* entry name offset */
              &(rt->entries[i].offset), &(rt->entries[i].size), &(rt->entries[i].type)) != OK)  /* entry ident */
    {
      fprintf(stderr, "labn_read_dir: Can't read entry #%zu.\n", i);
      return FALSE;
    }
    rt->entries[i].compressed = rt->entries[i].size;
  }

  names_offset = LABN_HEADER_SIZE + LABN_ENTRY_SIZE * rt->number;

  for(i = 0; i < rt->number; i++)
  {
    fseek(rt->file, names_offset + rt->entries[i].id, SEEK_SET);
    if (readf(rt->file, "sz", &(rt->entries[i].name)) != OK)
    {
      fprintf(stderr, "labn_read_dir: Can't read entry name #%zu.\n", i);
      return FALSE;
    }
    rt->entries[i].id = 0;
  }
  return TRUE;
}

bool_t labn_fill_filename(resentry_t * re)
{
  s_strcpy(&(re->filename), re->name);
  /* s_strlower(re->filename); */
  if (re->filename == NULL)
    return FALSE;
  return TRUE;
}

bool_t labn_fill_name(resentry_t * re)
{
  s_strcpy(&(re->name), re->filename);
  /* s_strupper(re->name);
     if (strlen(re->name) + 1 > LABN_ENTRY_NAME_SIZE)
     {
     fprintf(stderr, "gob_fill_name: Too long name \"%s\".\n", re->name);
     return FALSE;
     } */
  return TRUE;
}

bool_t labn_prepare_dir(restable_t * rt)
{
  size_t i;
  size_t size;

  size = LABN_HEADER_SIZE + LABN_ENTRY_SIZE * rt->number;
  for(i = 0; i < rt->number; i++)
    size += strlen(rt->entries[i].name) + 1;
  fseek(rt->file, size, SEEK_SET);
  return TRUE;
}

bool_t labn_write_dir(restable_t * rt)
{
  size_t i;
  size_t offset;
  size_t names_offset;

  offset = ftell(rt->file);
  fseek(rt->file, 0, SEEK_SET);
  if (writef(rt->file, "c4l4l4l4", LABN_IDENT, LABN_VERSION, rt->number,
             offset - LABN_HEADER_SIZE - LABN_ENTRY_SIZE * rt->number,
             offset) != OK)
  {
    fprintf(stderr, "labn_write_dir: Can't write header.\n");
    return FALSE;
  }

  names_offset = 0;
  for(i = 0; i < rt->number; i++)
  {
    if (writef(rt->file, "l4l4l4l4",
               names_offset,
               rt->entries[i].offset,
               rt->entries[i].size, rt->entries[i].type) != OK)
    {
      fprintf(stderr, "labn_write_dir: Can't write entry #%zu.\n", i);
      return FALSE;
    }
    names_offset += strlen(rt->entries[i].name) + 1;
  }
  for(i = 0; i < rt->number; i++)
    if (writef(rt->file, "sz", rt->entries[i].name) != OK)
    {
      fprintf(stderr, "labn_write_dir: Can't write entry name #%zu.\n", i);
      return FALSE;
    }
  fseek(rt->file, offset, SEEK_SET);
  return TRUE;
}
