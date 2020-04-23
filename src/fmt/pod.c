#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bin.h"
#include "pod.h"
typedef struct resentry_s
{
  size_t entry;                 /* Номер ресурса в исходном файле-пачки
                                   (важно на случай, если сортировка поменяет
                                   порядок записей) */

  char *filename;               /* Имя файла на диске */

  char *name;                   /* Имя ресурса */
  size_t offset;                /* Смещение ресурса */
  size_t size;                  /* Размер ресурса */

  size_t compressed;            /* Сжатый размер ресурса */
  size_t compression;           /* Номер метода сжатия */

  time_t time;                  /* Дополнительные атрибуты ресурса - время */
  size_t type;                  /* Дополнительные атрибуты ресурса */
  size_t id;                    /* Дополнительные атрибуты ресурса */

  ssize_t copyof;               /* -1, если этот ресурс не является копиеей другого,
                                   иначе - номер ресурса-оригинала */
} resentry_t;

typedef struct restable_s
{
  char *filename;               /* Имя файла-пачки */
  char *basepath;               /* Базовый каталог для извлечения или поиска файлов */
  char *meta;                   /* Файл с мета-данными */
  FILE *file;                   /* Файл-пачка */

  size_t number;                /* Количество ресурсов в таблице */
  size_t maxnumber;             /* Максимальное количество ресурсов в таблице,
                                 * которое можно разместить в entries, не выполняя вызов realloc */

  resentry_t *entries;          /* Таблица ресурсов */
} restable_t;


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
			pod1_write_entry(file, src);
		case POD2:
			pod2_write_entry(file, src);
		case POD3:
			pod3_write_entry(file, src);
		case POD4:
			pod4_write_entry(file, src);
		case POD5:
			pod5_write_entry(file, src);
		case POD6:
			pod6_write_entry(file, src);
		case EPD:
			epd_write_entry(file, src);
		default:
		break;
	}

	return FALSE;
}
pod_char_t* pod_type_to_file_ext(int pod_type)
{
	switch(pod_type)
	{
		case EPD:
			return "EPD";
		default:
			return "POD";
	}

	return FALSE;
}

bool_t resentry_to_pod_dir_entry(pod_dir_entry_t* dst, resentry_t *res)
{
	if(!dst)
		return false;

	strncpy(dst->filename, res->filename, POD_FILENAME_SIZE);
	dst->file_path_offset = res->file
	dst->file_size = res->compressed;
	dst->file_offset = res->offset;
	dst->file_uncompressed_size = res->size;
	dst->file_compression_level = res->compression
	dst->file_timestamp = res->time;
	// FIXME TODO implement checksum algorithm Adler32, Fletcher or Jeff M
	dst->file_checksum = 0;
	dst->type = atoi(pod_type_to_file_ext(pod_type));
	dst->id = id 
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

