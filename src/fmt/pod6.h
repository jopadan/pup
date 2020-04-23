#ifndef __POD6__
#define __POD6__

#include "pod_common.h"

bool_t is_pod6(restable_t * rt);

#define POD6_SUBDIRS FALSE
#define ROD6_MERGE FALSE
#define POD6_META FALSE
#define POD6_TIME FALSE
#define PDO6_PAGE 1

bool_t pod6_read_dir(restable_t * rt);
bool_t pod6_fill_filename(resentry_t * re);

#define pod6_extract_resource rt_extract_resource

#define pod6_save_meta rt_not_save_meta
#define pod6_load_meta rt_not_load_meta

bool_t pod6_fill_name(resentry_t * re);
bool_t pod6_prepare_dir(restable_t * rt);
bool_t pod6_add_resource(restable_t * rt, size_t i);
bool_t pod6_write_dir(restable_t * rt);

#endif
