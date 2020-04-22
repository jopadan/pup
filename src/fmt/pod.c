#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bin.h"
#include "pod.h"

bool_t pod_dir_entry_write(FILE* file, pod_dir_entry_t* src, int pod_type)
{
	switch(pod_type)
	{
		case POD1:
		case POD2:
		case POD3:
		case POD4:
		case POD5:
		case POD6:
		case EPD:
		default:
		break;
	}

	return FALSE;
}

pod resentry_to_pod_dir_entry(pod_dir_entry_t* src, resentry_t *re)
{
}

/* still copy of RES format
#define POD_ENTRY_NAME_SIZE 12
#define POD_ENTRY_OFFSET_SIZE 4
#define POD_ENTRY_SIZE_SIZE 4
#define POD_ENTRY_SIZE (POD_ENTRY_NAME_SIZE +  POD_ENTRY_OFFSET_SIZE + \
	POD_ENTRY_SIZE_SIZE)
*/

bool_t pod_fill_name(resentry_t* re)
{
  s_strcpy(&(re->name), re->filename);
  s_strupper(re->name);
  if (is_dos_filename(re->name) == FALSE)
  {
    fprintf(stderr, "pod_fill_name: \"%s\" is not DOS filename.\n", re->name);
    return FALSE;
  }
  return TRUE;
}

bool_t pod_prepare_dir(restable_t * rt)
{
  fseek(rt->file, POD_HEADER_SIZE + POD_DIR_ENTRY_SIZE * rt->number, SEEK_SET);
  return TRUE;
}

bool_t pod_add_resource(restable_t * rt, size_t i)
{
  char *filename;

  if (writec(rt->file, NULL, RES_ENTRY_SIZE) != OK)
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

