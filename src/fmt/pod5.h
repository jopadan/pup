#ifndef __POD5__
#define __POD5__

#include "pod_common.h"

bool_t is_pod5(restable_t * rt);

#define POD5_SUBDIRS FALSE
#define ROD5_MERGE FALSE
#define POD5_META FALSE
#define POD5_TIME FALSE
#define PDO5_PAGE 1

bool_t pod5_read_dir(restable_t * rt);
bool_t pod5_fill_filename(resentry_t * re);

#define pod5_extract_resource rt_extract_resource

#define pod5_save_meta rt_not_save_meta
#define pod5_load_meta rt_not_load_meta

bool_t pod5_fill_name(resentry_t * re);
bool_t pod5_prepare_dir(restable_t * rt);
bool_t pod5_add_resource(restable_t * rt, size_t i);
bool_t pod5_write_dir(restable_t * rt);

#endif
