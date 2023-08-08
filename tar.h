#ifndef __TAR__
#define __TAR__

#include <stdio.h>
#include "restable.h"

bool_t is_tar(restable_t * rt);

#define TAR_SUBDIRS FALSE
#define TAR_MERGE TRUE
#define TAR_META FALSE
#define TAR_TIME FALSE
#define TAR_PAGE 1

bool_t tar_read_dir(restable_t * rt);
bool_t tar_fill_filename(resentry_t * re);

#define tar_extract_resource rt_extract_resource

#define tar_save_meta rt_not_save_meta
#define tar_load_meta rt_not_load_meta

bool_t tar_fill_name(resentry_t * re);
bool_t tar_prepare_dir(restable_t * rt);

#define tar_add_resource rt_add_resource

bool_t tar_write_dir(restable_t * rt);

#endif
