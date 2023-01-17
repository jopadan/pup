#ifndef __POD__
#define __POD__

#include <stdio.h>
#include "restable.h"

bool_t is_pod(restable_t * rt);

#define POD_SUBDIRS FALSE
#define POD_MERGE FALSE
#define POD_META FALSE
#define POD_TIME FALSE
#define POD_PAGE 1

bool_t pod_read_dir(restable_t * rt);
bool_t pod_fill_filename(resentry_t * re);

#define pod_extract_resource rt_extract_resource

#define pod_save_meta rt_not_save_meta
#define pod_load_meta rt_not_load_meta

bool_t pod_fill_name(resentry_t * re);
bool_t pod_prepare_dir(restable_t * rt);
bool_t pod_add_resource(restable_t * rt, size_t i);
bool_t pod_write_dir(restable_t * rt);

#endif
