#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bin.h"
#include "csid.h"

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

#define TAR_BLOCK_SIZE 512
#define TAR_HEADER_SIZE TAR_BLOCK_SIZE
#define TAR_ENTRY_SIZE TAR_BLOCK_SIZE
#define TAR_BLOCK_NAME_SIZE 100
#define TAR_IDENT_OFFSET 257
#define TAR_IDENT "ustar  "	/* 7 chars and a null */
#define TAR_IDENT_SIZE  6
#define TAR_VERSION "00"             /* 00 and no null */
#define TAR_VERSION_SIZE 2

enum tar_format
{
	TAR_DEFAULT_FORMAT,       /* format to be decided later */
	TAR_V7_FORMAT,		  /* old V7 tar format */
	TAR_OLDGNU_FORMAT,        /* old GNU format */
	TAR_USTAR_FORMAT,         /* POSIX.1-1988 (ustar) format */
	TAR_POSIX_FORMAT,         /* POSIX.1-2001 format */
	TAR_STAR_FORMAT,          /* Star format defined in 1994 */
	TAR_GNU_FORMAT,           /* new GNU format */
};

enum tar_typefield {
	REGTYPE          =   '0', /* regular file */
	AREGTYPE         =  '\0', /* regular file */
	LNKTYPE          =   '1', /* link */
	SYMTYPE          =   '2', /* reserved */
	CHRTYPE          =   '3', /* character special */
	BLKTYPE          =   '4', /* block special */
	DIRTYPE          =   '5', /* directory */
	FIFOTYPE         =   '6', /* FIFO special */
	CONTTYPE         =   '7', /* reserved */
	XHDTYPE          =   'x', /* Extended header referring to the next file in the archive */
	XGLTYPE          =   'g', /* Global extended header */
	GNUTYPE_DUMPDIR	 =   'D', /* names of files been in the dir at the time of the dump */
	GNUTYPE_LONGLINK =   'K', /* next file has long linkname.  */
	GNUTYPE_LONGNAME =   'L', /* next file has long name.  */
	GNUTYPE_MULTIVOL =   'M', /* continuation file started on another volume.  */
	GNUTYPE_SPARSE   =   'S', /* This is for sparse files.  */
	GNUTYPE_VOLHDR   =   'V', /* This file is a tape/volume header.  Ignore it on extraction.  */
	SOLARIS_XHDTYPE  =   'X', /* Solaris extended header */
};

enum tar_mode {
	TOEXEC           = 1 << 0, /* execute/search by other */
	TOWRITE          = 1 << 1, /* write by other */
	TOREAD           = 1 << 2, /* read by other */
	TGEXEC           = 1 << 3, /* execute/search by group */
	TGWRITE          = 1 << 4, /* write by group */
	TGREAD           = 1 << 5, /* read by group */
	TUEXEC           = 1 << 6, /* execute/search by owner */
	TUWRITE          = 1 << 7, /* write by owner */
	TUREAD           = 1 << 8, /* read by owner */
	TSVTX            = 1 << 9, /* reserved */
	TSGID            = 1 << 10, /* set GID on execution */
	TSUID            = 1 << 11, /* set UID on execution */
};

/* POSIX header.  */
struct tar_posix_header
{				    /* byte offset */
	char name[TAR_BLOCK_NAME_SIZE]; /*   0 */
	char mode[8];               /* 100 */
	char uid[8];                /* 108 */
	char gid[8];                /* 116 */
	char size[12];              /* 124 */
	char mtime[12];             /* 136 */
	char chksum[8];             /* 148 */
	char typeflag;              /* 156 */
	char linkname[100];         /* 157 */
	char magic[TAR_IDENT_SIZE]; /* 257 */
	char version[2];            /* 263 */
	char uname[32];             /* 265 */
	char gname[32];             /* 297 */
	char devmajor[8];           /* 329 */
	char devminor[8];           /* 337 */
	char prefix[155];           /* 345 */
	                            /* 500 */
};

/* tar Header Block, from POSIX 1003.1-1990.  */
union tar_block
{
  char buffer[TAR_BLOCK_SIZE];
  struct tar_posix_header header;
};

char* tar_encode_octal(char* octal, uint64_t data, size_t size)
{
	if(octal == NULL)
		return NULL;
	if(sizeof(octal) > size)
		return NULL;
	if(snprintf(octal, size, "%lo", data) < 0)
		return NULL;
	return octal;
}

uint64_t tar_decode_octal(char *data, size_t size) {
    uint8_t *currentPtr = (uint8_t*) data + size;
    uint64_t sum = 0;
    uint64_t currentMultiplier = 1;
    uint8_t *checkPtr = currentPtr;

    for (; checkPtr >= (uint8_t *) data; checkPtr--) {
        if ((*checkPtr) == 0 || (*checkPtr) == ' ') {
            currentPtr = checkPtr - 1;
        }
    }
    for (; currentPtr >= (uint8_t *) data; currentPtr--) {
        sum += (*currentPtr - 48) * currentMultiplier;
        currentMultiplier *= 8;
    }
    return sum;
}

enum tar_format tar_ident(union tar_block * block)
{
	if(strncmp(block->header.magic, TAR_IDENT, TAR_IDENT_SIZE - 1) == 0)
		return TAR_POSIX_FORMAT;
	if(strncmp(&block->buffer[TAR_IDENT_OFFSET], TAR_IDENT, TAR_IDENT_SIZE + 1) == 0)
		return TAR_OLDGNU_FORMAT;
	return TAR_DEFAULT_FORMAT;
}

size_t tar_file_size(union tar_block * block)
{
	return tar_decode_octal(block->header.size, sizeof(block->header.size));
}

bool_t tar_checksum_verify(union tar_block * block)
{
	uint64_t     unsigned_sum = 0;
	 int64_t       signed_sum = 0;
	uint64_t reference_chksum = 0;
	    char      orig_chksum[8];
         int16_t                i = 0;

	memcpy(orig_chksum, block->header.chksum, 8);
	memset(block->header.chksum, ' ', 8);

	for(; i < TAR_BLOCK_SIZE; i++)
	{
		unsigned_sum += ((uint8_t *) block->buffer)[i];
		  signed_sum += (( int8_t *) block->buffer)[i];
	}
	memcpy(block->header.chksum, orig_chksum, 8);
	reference_chksum = tar_decode_octal(orig_chksum, 12);
	return (reference_chksum == unsigned_sum || (int64_t)reference_chksum == signed_sum) ? TRUE : FALSE;
}

static time_t tar_time(union tar_block *block)
{
	return tar_decode_octal(block->header.mtime, 12);
}


bool_t is_tar(restable_t * rt)
{
  union tar_block block;
  size_t offset = ftell(rt->file);
  bool_t res = FALSE;

  fseek(rt->file, 0, SEEK_SET);

  if (readf(rt->file, "c512", block.buffer) == OK)
  {
	if(tar_ident(&block) > 0)
		res = TRUE;
  }
  else
  {
  	fprintf(stderr, "is_tar: could not read block.\n");
	res = FALSE;
  }

  fseek(rt->file, offset, SEEK_SET);
  return res;
}

bool_t tar_fill_filename(resentry_t * re)
{
  char name[TAR_BLOCK_NAME_SIZE] = { '\0' };

  if(re->name == NULL)
  	re->name = strdup(name);
  if (strlen(re->name) > TAR_BLOCK_NAME_SIZE - 5)
    return FALSE;
  snprintf(name, TAR_BLOCK_NAME_SIZE, "%s.%zu", re->name, re->type);
  s_strlower(name);
  s_strcpy(&(re->filename), name);
  if (re->filename == NULL)
    return FALSE;
  return TRUE;
}

bool_t tar_fill_name(resentry_t * re)
{
  char *ext;

  ext = NULL;

  s_name(&(re->name), re->filename, SYS_PATH_DELIM);
  s_strupper(re->name);

  s_ext(&ext, re->filename, SYS_PATH_DELIM);
  if (ext[0] != '.')
  {
    fprintf(stderr, "tar_fill_name: filename has no extension.\n");
    re->type = 0;
  }
  else
    re->type = atoi(&(ext[1]));
  s_free(&ext);

  if (strlen(re->name) > TAR_BLOCK_NAME_SIZE)
  {
    fprintf(stderr, "tar_fill_name: name too long \"%s\".\n", re->name);
    return FALSE;
  }
  return TRUE;
}

bool_t tar_prepare_dir(restable_t * rt)
{
  fseek(rt->file, TAR_HEADER_SIZE, SEEK_SET);
  return TRUE;
}

bool_t tar_posix_block(restable_t * rt, union tar_block * block, size_t * count, bool_t * long_name)
{
        char name[PATH_MAX] = { '\0' };
	time_t time  = 0;
	size_t size  = 0;
	size_t pos   = 0;
	size_t pad   = 0;

	/* verify checksum */
	if(tar_checksum_verify(block) == FALSE)
		return FALSE;

	/* get time */ 
	time = tar_time(block);

	/* support prefix */
	if(strlen(block->header.prefix) > 0)
	{
		strcpy(name, block->header.prefix);
		name[strlen(name)] = '/';
	}
	strcpy(&name[strlen(name)], block->header.name);

	switch(block->header.typeflag)
	{
		case 0:
		case REGTYPE:
			if(*long_name == TRUE)
			{
				strncpy( &name[0], block->header.name, TAR_BLOCK_NAME_SIZE );
				if(readf(rt->file, "c512", block->buffer) != OK)
				{
					return FALSE;
				}
				*long_name = FALSE;
				(*count)++;
			}
			size = tar_file_size(block);
			pos  = ((*count) + 1) * TAR_BLOCK_SIZE;
			pad  = (TAR_BLOCK_SIZE - (size % TAR_BLOCK_SIZE)) % TAR_BLOCK_SIZE;
			/* add entry */
			if(rt_add_entry(rt) == FALSE)
			{
				printf("Error: rt_add_entry\n");
				return FALSE;
			}
			printf("count: %zu pos: %zu skip: %zu\n", *count, pos, size + pad);
			rt->entries[rt->number].filename = strdup(name);
			rt->entries[rt->number].size = size;
			rt->entries[rt->number].offset = pos;
			rt->entries[rt->number].time = time;
			if(tar_fill_name(&rt->entries[rt->number]) == FALSE)
			{
				return FALSE;
			}

			/* skip data */
                        fseek(rt->file, pos + size + pad, SEEK_SET);
			(*count) += ((size + pad) / TAR_BLOCK_SIZE);

			break;
		case DIRTYPE:
			/* add entry */
			if(rt_add_entry(rt) == FALSE)
			{
				return FALSE;
			}
			rt->entries[rt->number].filename = strdup(name);
			rt->entries[rt->number].time = time;
			if(tar_fill_name(&rt->entries[rt->number]) == FALSE)
			{
				return FALSE;
			}
			break;
		case GNUTYPE_LONGNAME:
			*long_name = TRUE;
			break;
		default:
			break;
	

	}
	return TRUE;
}

bool_t tar_write_dir(restable_t * rt)
{
  union tar_block zero_block = { 0 };
  size_t i;
  size_t offset = ftell(rt->file);
  fseek(rt->file, 0, SEEK_SET);
  for(i = 0; i < rt->number; i++)
  {
  	union tar_block current_block = { 0 };
  	strncpy(current_block.header.name, rt->entries[i].filename, TAR_BLOCK_NAME_SIZE - 1);
	if(tar_encode_octal(current_block.header.size, rt->entries[i].size, 12) == NULL || tar_encode_octal(current_block.header.mtime, rt->entries[i].time, 12) == NULL)
		return FALSE;
	current_block.header.typeflag = rt->entries[i].filename[strlen(rt->entries[i].filename)] == SYS_PATH_DELIM ? DIRTYPE : REGTYPE;
	writef(rt->file, "c512", current_block);
	fseek(rt->file, rt->entries[i].size + (TAR_BLOCK_SIZE - (rt->entries[i].size % TAR_BLOCK_SIZE)) % TAR_BLOCK_SIZE, SEEK_SET);
  }
  writef(rt->file, "c512", zero_block);
  fseek(rt->file, offset, SEEK_SET);
  return TRUE;
}

bool_t tar_read_dir(restable_t * rt)
{
  union tar_block current_block = { 0 };
  union tar_block zero_block = { 0 };
  size_t i;
  bool_t long_name;

  for(i = 0; readf(rt->file, "c512", current_block.buffer) == OK; i++)
  {
  	if(memcmp(current_block.buffer, zero_block.buffer, TAR_BLOCK_SIZE) == 0)
		break;

	enum tar_format format = tar_ident(&current_block);
	switch(format)
	{
		case TAR_POSIX_FORMAT:
			if(tar_posix_block(rt, &current_block, &i, &long_name) == FALSE)
			{
			  fprintf(stderr, "tar_read_dir: failed reading posix block.\n");
			  return FALSE;
			}
			break;
		case TAR_OLDGNU_FORMAT:
			break;
		case TAR_GNU_FORMAT:
			break;
		case TAR_V7_FORMAT:
			break;
		case TAR_USTAR_FORMAT:
			break;
		case TAR_STAR_FORMAT:
			break;
		case TAR_DEFAULT_FORMAT:
		default:
			fprintf(stderr, "tar_read_dir: Wrong ident.\n");
			return FALSE;
	}
  }
  return TRUE;
}
