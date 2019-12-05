#ifndef __RES__
#define __RES__

#include <stdio.h>
#include "restable.h"

bool_t is_res(restable_t * rt);

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
#define RES_SUBDIRS FALSE
#define RES_MERGE FALSE
#define RES_META FALSE
#define RES_TIME FALSE
#define RES_PAGE 1

bool_t res_read_dir(restable_t * rt);
bool_t res_fill_filename(resentry_t * re);

#define res_extract_resource rt_extract_resource

#define res_save_meta rt_not_save_meta
#define res_load_meta rt_not_load_meta

bool_t res_fill_name(resentry_t * re);
bool_t res_prepare_dir(restable_t * rt);
bool_t res_add_resource(restable_t * rt, size_t i);
bool_t res_write_dir(restable_t * rt);

#endif
