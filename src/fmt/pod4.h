#ifndef __POD4__
#define __POD4__

#include "pod_common.h"

bool_t is_pod4(restable_t * rt);

#define POD4_SUBDIRS FALSE
#define ROD4_MERGE FALSE
#define POD4_META FALSE
#define POD4_TIME FALSE
#define PDO4_PAGE 1

bool_t pod4_read_dir(restable_t * rt);
bool_t pod4_fill_filename(resentry_t * re);

#define pod4_extract_resource rt_extract_resource

#define pod4_save_meta rt_not_save_meta
#define pod4_load_meta rt_not_load_meta

bool_t pod4_fill_name(resentry_t * re);
bool_t pod4_prepare_dir(restable_t * rt);
bool_t pod4_add_resource(restable_t * rt, size_t i);
bool_t pod4_write_dir(restable_t * rt);

#endif
