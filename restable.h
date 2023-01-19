#ifndef __RESTABLE__
#define __RESTABLE__
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "bin.h"
#include "chksum.h"
#include "audit.h"

#define META_EXT ".txt"

typedef struct resentry_s
{
  size_t entry;                 /* Resource number in source bundle file
                                   (important in case the sorting changes
				   record order) */

  char *filename;               /* File name on disk */

  char *name;                   /* Resource name */
  size_t offset;                /* Resource offset */
  size_t size;                  /* Resource size */

  size_t compressed;            /* Compressed resource size */
  size_t compression;           /* Compression metod number */
  time_t time;                  /* Additional resource attributes - time */
  size_t type;                  /* Additional resource attributes */
  size_t id;                    /* Additional resource attributes */
  checksum_t checksum;          /* Checksum */

  ssize_t copyof;               /* -1, if this resource is not a copy of another */
} resentry_t;


typedef struct restable_s
{
  char *filename;               /* Packet file name */
  char *basepath;               /* Base directory to extract or search for files */
  char *meta;                   /* Metadata file */
  FILE *file;                   /* Bundle file   */

  time_t time;                  /* file creation/mod date */
  size_t type;                  /* file type     */
  size_t id;                    /* file hash id  */
  checksum_t checksum;          /* file checksum */

  /* Resource table */
  size_t number;
  size_t maxnumber;
  resentry_t   *entries;

  /* Audit table */
  size_t audits;
  size_t maxaudits;
  auditentry_t *auditentries; 
} restable_t;

/* Create a new batch file */
bool_t rt_create(restable_t * rt, const char *filename, const char *basepath,
                 const char *meta);

/* Оpen an existing bundle file */
bool_t rt_open(restable_t * rt, const char *filename, const char *basepath,
               const char *meta);

/* Clear the current table, set the number of records in the table to number */
bool_t rt_set_number(restable_t * rt, size_t number);

/* Add a new empty entry to the list of resources, the added resource will have
 * number rt->number */
bool_t rt_add_entry(restable_t * rt);

/* Free all memory allocated by restable_t */
void rt_free(restable_t * rt);

/* Scan the rt->basepath directory, adding to the resource table
 * all names of found files. subdirs means whether to scan
 * subdirectories. If subdirectories should not be scanned, but the subdirectory
 * is found, the function will exit with an error message. */
bool_t rt_fill_entries(restable_t * rt, bool_t subdirs);

/* Create all necessary directories for extracting files */
bool_t rt_make_dirs(restable_t * rt);

/* Copy files to a batch file */
bool_t rt_add_resource(restable_t * rt, size_t i);

/* Copy resources from bundle file to separate files */
bool_t rt_align_resource(restable_t * rt, size_t i, size_t page);

/* Copy resources from bundle file to separate files */
bool_t rt_extract_resource(restable_t * rt, size_t i);

/* Print to standard output all attributes of all resources */
void rt_print_dir(restable_t * rt, FILE * file);

bool_t rt_not_save_meta(restable_t * rt);
bool_t rt_not_load_meta(restable_t * rt);

bool_t rt_set_timestamp(restable_t * rt, size_t i);
bool_t rt_get_timestamp(restable_t * rt, size_t i);

ssize_t rt_search_by_name(restable_t * rt, const char *name, bool_t same_case);
ssize_t rt_search_by_filename(restable_t * rt, const char *filename,
                              bool_t same_case);

bool_t rt_rename(restable_t * rt, unsigned long i);

bool_t rt_fix(restable_t * rt);
bool_t rt_search_equal_files(restable_t * rt);
#endif
