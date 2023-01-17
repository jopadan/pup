#ifndef __EPD__
#define __EPD__

#include "pod_common.h"

bool_t is_epd(restable_t * rt);

#define EPD_SUBDIRS FALSE
#define EPD_MERGE FALSE
#define EPD_META FALSE
#define EPD_TIME FALSE
#define EPD_PAGE 1

bool_t epd_read_dir(restable_t * rt);
bool_t epd_fill_filename(resentry_t * re);

#define epd_extract_resource rt_extract_resource

#define epd_save_meta rt_not_save_meta
#define epd_load_meta rt_not_load_meta

bool_t epd_fill_name(resentry_t * re);
bool_t epd_prepare_dir(restable_t * rt);
bool_t epd_add_resource(restable_t * rt, size_t i);
bool_t epd_write_dir(restable_t * rt);

#endif
