#ifndef __CSID__
#define __CSID__

#include <stdio.h>
#include "restable.h"

bool_t is_csid(restable_t * rt);

#define CSID_SUBDIRS FALSE
#define CSID_MERGE TRUE
#define CSID_META FALSE
#define CSID_TIME FALSE
#define CSID_PAGE 1

bool_t csid_read_dir(restable_t * rt);
bool_t csid_fill_filename(resentry_t * re);

#define csid_extract_resource rt_extract_resource

#define csid_save_meta rt_not_save_meta
#define csid_load_meta rt_not_load_meta

bool_t csid_fill_name(resentry_t * re);
bool_t csid_prepare_dir(restable_t * rt);

#define csid_add_resource rt_add_resource

bool_t csid_write_dir(restable_t * rt);

#endif
