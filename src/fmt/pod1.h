#ifndef __POD1__
#define __POD1__

#include "pod_common.h"

bool_t is_pod1(restable_t * rt);

#define POD1_SUBDIRS FALSE
#define ROD1_MERGE FALSE
#define POD1_META FALSE
#define POD1_TIME FALSE
#define PDO1_PAGE 1

bool_t pod1_read_dir(restable_t * rt);
bool_t pod1_fill_filename(resentry_t * re);

#define pod1_extract_resource rt_extract_resource

#define pod1_save_meta rt_not_save_meta
#define pod1_load_meta rt_not_load_meta

bool_t pod1_fill_name(resentry_t * re);
bool_t pod1_prepare_dir(restable_t * rt);
bool_t pod1_add_resource(restable_t * rt, size_t i);
bool_t pod1_write_dir(restable_t * rt);

#endif
