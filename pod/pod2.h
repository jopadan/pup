#ifndef __POD2__
#define __POD2__

#include "pod.h"

bool_t is_pod2(restable_t * rt);

#define POD2_SUBDIRS FALSE
#define POD2_MERGE FALSE
#define POD2_META FALSE
#define POD2_TIME FALSE
#define POD2_PAGE 1

bool_t pod2_read_dir(restable_t * rt);
bool_t pod2_fill_filename(resentry_t * re);

#define pod2_extract_resource rt_extract_resource

#define pod2_save_meta rt_not_save_meta
#define pod2_load_meta rt_not_load_meta

bool_t pod2_fill_name(resentry_t * re);
bool_t pod2_prepare_dir(restable_t * rt);
bool_t pod2_add_resource(restable_t * rt, size_t i);
bool_t pod2_write_dir(restable_t * rt);


#endif
