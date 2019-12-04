#ifndef __LABN__
#define __LABN__

#include <stdio.h>
#include "restable.h"

bool_t is_labn(restable_t * rt);

#define LABN_SUBDIRS FALSE
#define LABN_MERGE TRUE
#define LABN_META FALSE
#define LABN_TIME FALSE
#define LABN_PAGE 1

bool_t labn_read_dir(restable_t * rt);
bool_t labn_fill_filename(resentry_t * re);

#define labn_extract_resource rt_extract_resource

#define labn_save_meta rt_not_save_meta
#define labn_load_meta rt_not_load_meta

bool_t labn_fill_name(resentry_t * re);
bool_t labn_prepare_dir(restable_t * rt);

#define labn_add_resource rt_add_resource
bool_t labn_write_dir(restable_t * rt);

#endif
