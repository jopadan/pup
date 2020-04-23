#ifndef __POD3__
#define __POD3__

#include "pod_common.h"

bool_t is_pod3(restable_t * rt);

#define POD3_SUBDIRS FALSE
#define ROD3_MERGE FALSE
#define POD3_META FALSE
#define POD3_TIME FALSE
#define PDO3_PAGE 1

bool_t pod3_read_dir(restable_t * rt);
bool_t pod3_fill_filename(resentry_t * re);

#define pod3_extract_resource rt_extract_resource

#define pod3_save_meta rt_not_save_meta
#define pod3_load_meta rt_not_load_meta

bool_t pod3_fill_name(resentry_t * re);
bool_t pod3_prepare_dir(restable_t * rt);
bool_t pod3_add_resource(restable_t * rt, size_t i);
bool_t pod3_write_dir(restable_t * rt);

#endif
