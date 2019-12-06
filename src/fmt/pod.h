#ifndef __RES__
#define __RES__

#include <stdio.h>
#include "restable.h"

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

bool_t is_pod2(restable_t * rt);

#define POD2_SUBDIRS FALSE
#define ROD2_MERGE FALSE
#define POD2_META FALSE
#define POD2_TIME FALSE
#define PDO2_PAGE 1

bool_t pod2_read_dir(restable_t * rt);
bool_t pod2_fill_filename(resentry_t * re);

#define pod2_extract_resource rt_extract_resource

#define pod2_save_meta rt_not_save_meta
#define pod2_load_meta rt_not_load_meta

bool_t pod2_fill_name(resentry_t * re);
bool_t pod2_prepare_dir(restable_t * rt);
bool_t pod2_add_resource(restable_t * rt, size_t i);
bool_t pod2_write_dir(restable_t * rt);

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
