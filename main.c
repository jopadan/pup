#include <stdio.h>
#include <string.h>
#include "bin.h"
#include "restable.h"
#include "meta.h"
#include "grp.h"
#include "gob.h"
#include "pak.h"
#include "viv.h"
#include "vpp.h"
#include "pack.h"
#include "pack2.h"
#include "wad23.h"
#include "resource1.h"
#include "resource2.h"
#include "dpk4.h"
#include "dat.h"
#include "dat2.h"
#include "rff.h"
#include "labn.h"
#include "csid.h"
#include "tar.h"

typedef struct plugin_s
{
  char *name;                   /* Plugin name */
  char *description;            /* Plugin description */

  bool_t subdirs;               /* Does the bundle file support subdirectories */
  bool_t merge;                 /* Does the file have separate offset and size
                                 * fields, or is one computed from the other?
                                 * TRUE - both fields are present, 
                                 * FALSE - only one of the fields is present. */
  bool_t meta;                  /* Is it necessary for this plugin to use a
                                 *  file with meta-information */
  bool_t time;                  /* Does the batch file store the last 
                                 * modification time of the file */
  size_t page;                  /* The size of the block to which it is aligned  
                                 * size of each resource */

  /* The function checks if the opened file is a batch file, format
   * supported by this plugin. */
         bool_t(*is_file) (restable_t * rt);

/* The following functions are used to unpack the bundle file */

  /* Reads the resource directory from the bundle file. In case
   * of error returns FALSE */
         bool_t(*read_dir) (restable_t * rt);

  /* Convert resource name to filename. In case of error returns
   * FALSE */
         bool_t(*fill_filename) (resentry_t * re);

  /* Extracts the specified resource from the bundle file into 
   * a separate file. */
         bool_t(*extract_resource) (restable_t * rt, size_t i);

  /* Extracts metadata from a bundle file into a separate file */
         bool_t(*save_meta) (restable_t * rt);

/* The following functions are used to create a new bundle */

  /* Populates the bundle file's metadata from a single file. */
         bool_t(*load_meta) (restable_t * rt);

  /* Convert filename to resource name. In case of error returns or
   * invalid resource name returns FALSE */
         bool_t(*fill_name) (resentry_t * re);

  /* Fill in the resource names, put the file pointer at the beginning
   * the first resource. */
         bool_t(*prepare_dir) (restable_t * rt);

  /* Writes the resource to the pack file, filling in the offset fields in
   * the offset fields along the way, size, compressed size, compression
   * type and other information which can only be found by accessing the 
   * resource file. */
         bool_t(*add_resource) (restable_t * rt, size_t i);

  /* Write the resource directory to a file. Before calling the function,
   * the pointer file must be set to the next byte after the last resource.
   * Before terminating, the function must set the pointer to the end of the
   * file */
         bool_t(*write_dir) (restable_t * rt);
} plugin_t;

plugin_t plugins[] = {
  {
   "grp",
   "GRP-files of Duke Nukem 3D, Witchaven, Redneck Rampage, Shadow Warrior",
   GRP_SUBDIRS,
   GRP_MERGE,
   GRP_META,
   GRP_TIME,
   GRP_PAGE,
   &is_grp,

   &grp_read_dir,
   &grp_fill_filename,
   &grp_extract_resource,

   &grp_save_meta,
   &grp_load_meta,

   &grp_fill_name,
   &grp_prepare_dir,
   &grp_add_resource,
   &grp_write_dir},
  {
   "gob",
   "GOB-files of Star Wars: Dark Forces",
   GOB_SUBDIRS,
   GOB_MERGE,
   GOB_META,
   GOB_TIME,
   GOB_PAGE,
   &is_gob,

   &gob_read_dir,
   &gob_fill_filename,
   &gob_extract_resource,

   &gob_save_meta,
   &gob_load_meta,

   &gob_fill_name,
   &gob_prepare_dir,
   &gob_add_resource,
   &gob_write_dir},
  {
   "pak",
   "PAK-files of Dune II: The Building of a Dynasty",
   PAK_SUBDIRS,
   PAK_MERGE,
   PAK_META,
   PAK_TIME,
   PAK_PAGE,
   &is_pak,

   &pak_read_dir,
   &pak_fill_filename,
   &pak_extract_resource,

   &pak_save_meta,
   &pak_load_meta,

   &pak_fill_name,
   &pak_prepare_dir,
   &pak_add_resource,
   &pak_write_dir},
  {
   "viv",
   "VIV-files of the Need For the Speed 3: Hot Pursuit",
   VIV_SUBDIRS,
   VIV_MERGE,
   VIV_META,
   VIV_TIME,
   VIV_PAGE,
   &is_viv,

   &viv_read_dir,
   &viv_fill_filename,
   &viv_extract_resource,

   &viv_save_meta,
   &viv_load_meta,

   &viv_fill_name,
   &viv_prepare_dir,
   &viv_add_resource,
   &viv_write_dir},
  {
   "vpp",
   "VPP-files of Red Faction, The Punisher, Summoner",
   VPP_SUBDIRS,
   VPP_MERGE,
   VPP_META,
   VPP_TIME,
   VPP_PAGE,
   &is_vpp,

   &vpp_read_dir,
   &vpp_fill_filename,
   &vpp_extract_resource,

   &vpp_save_meta,
   &vpp_load_meta,

   &vpp_fill_name,
   &vpp_prepare_dir,
   &vpp_add_resource,
   &vpp_write_dir},
  {
   "pack",
   "PAK-files of Quake, Quake II, Half-Life, Heretic 2, MDK 2",
   PACK_SUBDIRS,
   PACK_MERGE,
   PACK_META,
   PACK_TIME,
   PACK_PAGE,
   &is_pack,

   &pack_read_dir,
   &pack_fill_filename,
   &pack_extract_resource,

   &pack_save_meta,
   &pack_load_meta,

   &pack_fill_name,
   &pack_prepare_dir,
   &pack_add_resource,
   &pack_write_dir},
  {
   "pack2",
   "PAK-files of Daikatana",
   PACK2_SUBDIRS,
   PACK2_MERGE,
   PACK2_META,
   PACK2_TIME,
   PACK2_PAGE,
   &is_pack2,

   &pack2_read_dir,
   &pack2_fill_filename,
   &pack2_extract_resource,

   &pack2_save_meta,
   &pack2_load_meta,

   &pack2_fill_name,
   &pack2_prepare_dir,
   &pack2_add_resource,
   &pack2_write_dir},
  {
   "wad2",
   "WAD-file of Quake",
   WAD23_SUBDIRS,
   WAD23_MERGE,
   WAD23_META,
   WAD23_TIME,
   WAD23_PAGE,
   &is_wad2,

   &wad23_read_dir,
   &wad23_fill_filename,
   &wad23_extract_resource,

   &wad23_save_meta,
   &wad23_load_meta,

   &wad23_fill_name,
   &wad23_prepare_dir,
   &wad23_add_resource,
   &wad2_write_dir},
  {
   "wad3",
   "WAD-files of Half-Life",
   WAD23_SUBDIRS,
   WAD23_MERGE,
   WAD23_META,
   WAD23_TIME,
   WAD23_PAGE,
   &is_wad3,

   &wad23_read_dir,
   &wad23_fill_filename,
   &wad23_extract_resource,

   &wad23_save_meta,
   &wad23_load_meta,

   &wad23_fill_name,
   &wad23_prepare_dir,
   &wad23_add_resource,
   &wad3_write_dir},
  {
   "resource1",
   "RES-file of Armored Fist 2",
   RESOURCE1_SUBDIRS,
   RESOURCE1_MERGE,
   RESOURCE1_META,
   RESOURCE1_TIME,
   RESOURCE1_PAGE,
   &is_resource1,

   &resource1_read_dir,
   &resource1_fill_filename,
   &resource1_extract_resource,

   &resource1_save_meta,
   &resource1_load_meta,

   &resource1_fill_name,
   &resource1_prepare_dir,
   &resource1_add_resource,
   &resource1_write_dir},
  {
   "resource2",
   "RES-file of Comanche 3",
   RESOURCE2_SUBDIRS,
   RESOURCE2_MERGE,
   RESOURCE2_META,
   RESOURCE2_TIME,
   RESOURCE2_PAGE,
   &is_resource2,

   &resource2_read_dir,
   &resource2_fill_filename,
   &resource2_extract_resource,

   &resource2_save_meta,
   &resource2_load_meta,

   &resource2_fill_name,
   &resource2_prepare_dir,
   &resource2_add_resource,
   &resource2_write_dir},
  {
   "dpk4",
   "DPK-file of Starmageddon 2",
   DPK4_SUBDIRS,
   DPK4_MERGE,
   DPK4_META,
   DPK4_TIME,
   DPK4_PAGE,
   &is_dpk4,

   &dpk4_read_dir,
   &dpk4_fill_filename,
   &dpk4_extract_resource,

   &dpk4_save_meta,
   &dpk4_load_meta,

   &dpk4_fill_name,
   &dpk4_prepare_dir,
   &dpk4_add_resource,
   &dpk4_write_dir},
  {
   "dat",
   "DAT-files of Fallout",
   DAT_SUBDIRS,
   DAT_MERGE,
   DAT_META,
   DAT_TIME,
   DAT_PAGE,
   &is_dat,

   &dat_read_dir,
   &dat_fill_filename,
   &dat_extract_resource,

   &dat_save_meta,
   &dat_load_meta,

   &dat_fill_name,
   &dat_prepare_dir,
   &dat_add_resource,
   &dat_write_dir},
  {
   "dat2",
   "DAT-files of Fallout 2",
   DAT2_SUBDIRS,
   DAT2_MERGE,
   DAT2_META,
   DAT2_TIME,
   DAT2_PAGE,
   &is_dat2,

   &dat2_read_dir,
   &dat2_fill_filename,
   &dat2_extract_resource,

   &dat2_save_meta,
   &dat2_load_meta,

   &dat2_fill_name,
   &dat2_prepare_dir,
   &dat2_add_resource,
   &dat2_write_dir},
  {
   "rff20",
   "RFF-files of Blood, version 2.0",
   RFF_SUBDIRS,
   RFF_MERGE,
   RFF_META,
   RFF_TIME,
   RFF_PAGE,
   &is_rff20,

   &rff_read_dir,
   &rff_fill_filename,
   &rff_extract_resource,

   &rff_save_meta,
   &rff_load_meta,

   &rff_fill_name,
   &rff_prepare_dir,
   &rff_add_resource,
   &rff20_write_dir},
  {
   "rff30",
   "RFF-files of Blood, version 3.0",
   RFF_SUBDIRS,
   RFF_MERGE,
   RFF_META,
   RFF_TIME,
   RFF_PAGE,
   &is_rff30,

   &rff_read_dir,
   &rff_fill_filename,
   &rff_extract_resource,

   &rff_save_meta,
   &rff_load_meta,

   &rff_fill_name,
   &rff_prepare_dir,
   &rff_add_resource,
   &rff30_write_dir},
  {
   "rff31",
   "RFF-files of Blood, version 3.1",
   RFF_SUBDIRS,
   RFF_MERGE,
   RFF_META,
   RFF_TIME,
   RFF_PAGE,
   &is_rff31,

   &rff_read_dir,
   &rff_fill_filename,
   &rff_extract_resource,

   &rff_save_meta,
   &rff_load_meta,

   &rff_fill_name,
   &rff_prepare_dir,
   &rff_add_resource,
   &rff31_write_dir},
  {
   "labn",
   "LABN-files of Outlaws",
   LABN_SUBDIRS,
   LABN_MERGE,
   LABN_META,
   LABN_TIME,
   LABN_PAGE,
   &is_labn,

   &labn_read_dir,
   &labn_fill_filename,
   &labn_extract_resource,

   &labn_save_meta,
   &labn_load_meta,

   &labn_fill_name,
   &labn_prepare_dir,
   &labn_add_resource,
   &labn_write_dir},
  {
   "csid",
   "BIN-file of Chasm: The Rift",
   CSID_SUBDIRS,
   CSID_MERGE,
   CSID_META,
   CSID_TIME,
   CSID_PAGE,
   &is_csid,

   &csid_read_dir,
   &csid_fill_filename,
   &csid_extract_resource,

   &csid_save_meta,
   &csid_load_meta,

   &csid_fill_name,
   &csid_prepare_dir,
   &csid_add_resource,
   &csid_write_dir},
  {
   "tar",
   "TAR-files POSIX GNU format",
   TAR_SUBDIRS,
   TAR_MERGE,
   TAR_META,
   TAR_TIME,
   TAR_PAGE,
   &is_tar,

   &tar_read_dir,
   &tar_fill_filename,
   &tar_extract_resource,

   &tar_save_meta,
   &tar_load_meta,

   &tar_fill_name,
   &tar_prepare_dir,
   &tar_add_resource,
   &tar_write_dir}
};

#define NUM_PLUGINS (sizeof(plugins) / sizeof(plugin_t))

plugin_t *detect_plugin(restable_t * rt)
{
  size_t i;

  for(i = 0; i < NUM_PLUGINS; i++)
  {
    fseek(rt->file, 0, SEEK_SET);
    if (plugins[i].is_file(rt) == TRUE)
    {
      fseek(rt->file, 0, SEEK_SET);
      fprintf(stdout, "Autodetected plugin:\t%s.\n", plugins[i].name);
      return &(plugins[i]);
    }
  }
  fprintf(stderr, "Can't autodetect appropriate plugin.\n");
  return NULL;
}

plugin_t *select_plugin(const char *name)
{
  size_t i;

  for(i = 0; i < NUM_PLUGINS; i++)
  {
    if (strcmp(plugins[i].name, name) == 0)
    {
      fprintf(stdout, "Selected plugin:\t%s.\n", plugins[i].name);
      return &(plugins[i]);
    }
  }
  fprintf(stderr, "Unsupported plugin:\t%s.\n", name);
  return NULL;
}

void list_plugins(void)
{
  size_t i;

  fprintf(stdout, "Supported plugins:\n");
  for(i = 0; i < NUM_PLUGINS; i++)
    fprintf(stderr, "%-9s - %s\n", plugins[i].name, plugins[i].description);
}

bool_t pack(const plugin_t * p, const char *filename, const char *path,
            const char *meta)
{
  restable_t rt;
  size_t i;
  size_t j;

  if (p == NULL)
  {
    fprintf(stderr, "You must specify plugin.\n");
    return FALSE;
  }
  /* Create a new batch file */
  if (rt_create(&rt, filename, path, meta) == FALSE)
    return FALSE;
  if (p->meta == TRUE)
  {
    /* Load file list and meta information from meta file */
    if (p->load_meta(&rt) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  else
  {
    /* Scan directories, populate file table */
    if (rt_fill_entries(&rt, p->subdirs) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  /* Get resource names from filenames */
  for(i = 0; i < rt.number; i++)
  {
    if (rt.entries[i].name != NULL)
      continue;
    if (p->fill_name(&(rt.entries[i])) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  if (p->merge == TRUE)
    rt_search_equal_files(&rt);
  /* Calculate the offset of the first resource */
  if (p->prepare_dir(&rt) == FALSE)
  {
    rt_free(&rt);
    return FALSE;
  }
  /* Reading files and saving as resources */
  for(i = 0; i < rt.number; i++)
  {
    fprintf(stderr, "Packed %zu/%zu\r", i, rt.number);
    if (rt.entries[i].copyof != -1)
    {
      j = rt.entries[i].copyof;
      rt.entries[i].offset = rt.entries[j].offset;
      rt.entries[i].size = rt.entries[j].size;
      rt.entries[i].compressed = rt.entries[j].compressed;
      rt.entries[i].compression = rt.entries[j].compression;
      rt.entries[i].type = rt.entries[j].type;
      continue;
    }
    if (p->add_resource(&rt, i) == FALSE)
    {
      fprintf(stderr, "pack: Can't add resource #%zu.\n", i);
      rt_free(&rt);
      return FALSE;
    }
    if (rt_align_resource(&rt, i, p->page) == FALSE)
    {
      fprintf(stderr, "pack: Can't align resource #%zu.\n", i);
      rt_free(&rt);
      return FALSE;
    }
    if (p->time == TRUE)
      if (rt_get_timestamp(&rt, i) == FALSE)
      {
        fprintf(stderr, "pack: Can't get time of resource #%zu.\n", i);
        rt_free(&rt);
        return FALSE;
      }
  }
  fprintf(stderr, "Packing finished.  \n");
  /* Write resource directory */
  if (p->write_dir(&rt) == FALSE)
  {
    rt_free(&rt);
    return FALSE;
  }
  rt_free(&rt);
  return TRUE;
}

bool_t unpack(const plugin_t * p, const char *filename, const char *path,
              const char *meta)
{
  restable_t rt;
  size_t i;

  /* Read resources and save as files */
  if (rt_open(&rt, filename, path, meta) == FALSE)
    return FALSE;
  /* If plugin is not specified, try to define it */
  if (p == NULL)
    p = detect_plugin(&rt);
  /* If it was not possible to determine, we quit */
  if (p == NULL)
  {
    rt_free(&rt);
    return FALSE;
  }
  /* Read the resource directory from the bundle file */
  if (p->read_dir(&rt) == FALSE)
  {
    rt_free(&rt);
    return FALSE;
  }
  /* Find duplicate resources and resource overlap errors */
  for(i = 0; i < rt.number; i++)
  {
    if (rt.entries[i].filename != NULL)
      continue;
    if (p->fill_filename(&(rt.entries[i])) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  /* Print resource information to standard output */
  if (rt_fix(&rt) == FALSE)
  {
    fprintf(stderr, "unpack: rt_fix failed.\n");
    rt_free(&rt);
    return FALSE;
  }
  /* Сreate directories needed to extract files */
  if (p->subdirs == TRUE)
  {
    if (rt_make_dirs(&rt) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  else
  {
    if (mkpath(rt.basepath, 0777) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  /* Uploading meta information if uploading is supported by the plugin */
  if (p->meta == TRUE)
    if (p->save_meta(&rt) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  /* Read resources and save as R files */
  for(i = 0; i < rt.number; i++)
  {
    fprintf(stderr, "Unpacked %zu/%zu\r", i, rt.number);
    if (p->extract_resource(&rt, i) == FALSE)
    {
      fprintf(stderr, "unpack: Can't extract resource #%zu.\n", i);
      rt_free(&rt);
      return FALSE;
    }
    if (p->time == TRUE)
      if (rt_set_timestamp(&rt, i) == FALSE)
      {
        fprintf(stderr, "unpack: Can't set time of resource #%zu.\n", i);
        rt_free(&rt);
        return FALSE;
      }
  }
  fprintf(stderr, "Unpacking finished.    \n");
  rt_free(&rt);
  return TRUE;
}

bool_t print(const plugin_t * p, const char *filename)
{
  restable_t rt;
  size_t i;

  /* Opening the bundle file */
  if (rt_open(&rt, filename, NULL, NULL) == FALSE)
    return FALSE;
  /* If the plugin is not specified, try to determine */
  if (p == NULL)
    p = detect_plugin(&rt);
  /* If it was not possible to determine - exit */
  if (p == NULL)
  {
    rt_free(&rt);
    return FALSE;
  }
  /* Read the resource directory from the bundle file */
  if (p->read_dir(&rt) == FALSE)
  {
    rt_free(&rt);
    return FALSE;
  }
  /* Fill in file names from resource names */
  for(i = 0; i < rt.number; i++)
  {
    if (rt.entries[i].filename != NULL)
      continue;
    if (p->fill_filename(&(rt.entries[i])) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  /* Find duplicate resources and resource overlap errors */
  if (rt_fix(&rt) == FALSE)
  {
    fprintf(stderr, "unpack: rt_fix failed.\n");
    rt_free(&rt);
    return FALSE;
  }
  /* Printing resource information to standard output */
  rt_print_dir(&rt, stdout);
  rt_free(&rt);
  return TRUE;
}

bool_t savemeta(const plugin_t * p, const char *filename, const char *meta)
{
  restable_t rt;
  size_t i;

  /* Open the bundle file */
  if (rt_open(&rt, filename, NULL, meta) == FALSE)
    return FALSE;
  /* If the plugin is not specified, we try to determine */
  if (p == NULL)
    p = detect_plugin(&rt);
  /* If it was not possible to determine, exit */
  if (p == NULL)
  {
    rt_free(&rt);
    return FALSE;
  }
  /* If the plugin does not support uploading meta information, the exit */
  if (p->meta == FALSE)
  {
    fprintf(stderr, "savemeta: This plugin does not support metadata.\n");
    rt_free(&rt);
    return FALSE;
  }
  /* Reading the resource directory from the bundle file */
  if (p->read_dir(&rt) == FALSE)
  {
    rt_free(&rt);
    return FALSE;
  }
  /* Fill in file names from resource names  */
  for(i = 0; i < rt.number; i++)
  {
    if (rt.entries[i].filename != NULL)
      continue;
    if (p->fill_filename(&(rt.entries[i])) == FALSE)
    {
      rt_free(&rt);
      return FALSE;
    }
  }
  if (p->save_meta(&rt) == FALSE)
  {
    fprintf(stderr, "savemeta: Can't save metadata.\n");
    rt_free(&rt);
    return FALSE;
  }
  rt_free(&rt);
  return TRUE;
}

typedef enum pup_mode_e
{
  NONE,
  PACK,
  UNPACK,
  PRINT,
  SAVEMETA,
  LIST
} pup_mode_t;

int main(int carg, char *varg[])
{
  ssize_t i;
  char *filename;
  char *dir;
  char *metafile;
  pup_mode_t mode;
  plugin_t *p;

  filename = NULL;
  dir = NULL;
  metafile = NULL;
  mode = NONE;
  p = NULL;

  for(i = 1; i < carg; i++)
  {
    if (strcmp(varg[i], "--plugin") == 0)
    {
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        p = select_plugin(varg[i]);
    }
    else if (strcmp(varg[i], "--pack") == 0)
    {
      mode = PACK;
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        filename = varg[i];
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        dir = varg[i];
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        metafile = varg[i];
    }
    else if (strcmp(varg[i], "--unpack") == 0)
    {
      mode = UNPACK;
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        filename = varg[i];
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        dir = varg[i];
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        metafile = varg[i];
    }
    else if (strcmp(varg[i], "--print") == 0)
    {
      mode = PRINT;
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        filename = varg[i];
    }
    else if (strcmp(varg[i], "--savemeta") == 0)
    {
      mode = SAVEMETA;
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        filename = varg[i];
      i++;
      if ((i < carg) && (strncmp(varg[i], "--", 2) != 0))
        metafile = varg[i];
    }
    else if (strcmp(varg[i], "--list") == 0)
      mode = LIST;
    else
    {
      fprintf(stderr, "Unknown option: %s\n", varg[i]);
      return 1;
    }
  }

  if ((filename == NULL) &&
      ((mode == PACK) || (mode == UNPACK) || (mode == PRINT) ||
       (mode == SAVEMETA)))
  {
    fprintf(stderr, "You must specify filename for this mode.\n");
    return 2;
  }
  if ((metafile == NULL) && (mode == SAVEMETA))
  {
    fprintf(stderr, "You must specify metafile for this mode.\n");
    return 2;
  }

  if (mode == LIST)
    list_plugins();
  else if (mode == PACK)
  {
    if (pack(p, filename, dir, metafile) == FALSE)
      return 3;
  }
  else if (mode == UNPACK)
  {
    if (unpack(p, filename, dir, metafile) == FALSE)
      return 4;
  }
  else if (mode == SAVEMETA)
  {
    if (savemeta(p, filename, metafile) == FALSE)
      return 5;
  }
  else if (mode == PRINT)
  {
    if (print(p, filename) == FALSE)
      return 7;
  }
  else
  {
    fprintf(stdout, "Usage: pup --list\n"
            "       pup --plugin <plugin> --pack <file> [<dir> [<meta>]]\n"
            "       pup [--plugin <plugin>] --unpack <file> [<dir> [<meta>]]\n"
            "       pup [--plugin <plugin>] --savemeta <file> [<meta>]\n"
            "       pup [--plugin <plugin>] --print <file>\n"
            "Options:\n"
            "       --plugin <plugin>\t\t - specify certain plugin\n");
    fprintf(stdout, "Modes:\n"
            "       --list\t\t\t\t - list of all supported plugins\n"
            "       --pack <file> [<dir> [<meta>]]\t - packing dir to specified file\n"
            "       --unpack <file> [<dir> [<meta>]]\t - unpacking specified file to dir\n"
            "       --savemeta <file> [<meta>]\t - only save metadata to specified metafile\n"
            "       --print <file>\t\t\t - print technical information to stdout\n");
    return 8;
  }
  return 0;
}
