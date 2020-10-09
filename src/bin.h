#ifndef __BIN__
#define __BIN__
#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <fcntl.h>

typedef enum bool_e
{
  FALSE = 0,
  TRUE = !FALSE
} bool_t;

typedef struct buf_s
{
  uint8_t *p;
  size_t offset;
  size_t size;
} buf_t;

typedef enum binrw_error_e
{
  OK,                           /* Successfull completion */
  NOMEM_ERROR,                  /* Failed to allocate memory */
  READ_ERROR,                   /* Read error occurred */
  WRITE_ERROR,                  /* Write error occured */
  ARG_ERROR,                    /* Invalid argument passed */
  FORMAT_ERROR                  /* Error in format string */
} binrw_error_t;

#define SYS_PATH_DELIM	'/'
#define SYS_PATH_SDELIM	"/"

bool_t fextract(const char *dst_filename, FILE * src, size_t size);
bool_t fadd(FILE * dst, const char *src_filename, size_t * psize);

void *loadfile(const char *filename, size_t * psize);
bool_t savefile(const char *filename, const void *data, size_t size);

void *loadblock(FILE * file, size_t size);
bool_t saveblock(FILE * file, void *data, size_t size);

size_t align(size_t size, size_t page);
size_t padsize(size_t size, size_t page);

size_t fsize(FILE * file);
size_t filesize(const char *filename);

void s_free(char **pt);
bool_t s_let(char **t, char *s);

char *sn_strcpy(const char *s);
char *sn_strncpy(const char *s, size_t l);
char *sn_strcat(const char *s0, const char *s1);
char *sn_strncat(const char *s0, const char *s1, size_t l);

bool_t s_strcpy(char **pt, const char *s);
bool_t s_strncpy(char **pt, const char *s, size_t l);
bool_t s_strcat(char **pt, const char *s);
bool_t s_strncat(char **pt, const char *s, size_t l);

char *snv_sprintf(const char *format, va_list vl);
bool_t s_sprintf(char **s, const char *format, ...);

bool_t is_prefix(const char *s, const char *prefix);
bool_t is_suffix(const char *s, const char *suffix);

bool_t cut_prefix(char *s, const char *prefix);
bool_t cut_suffix(char *s, const char *suffix);

/* Мaybe you should delete? */
bool_t s_cut_prefix(char **pt, const char *s, const char *prefix);
bool_t s_cut_suffix(char **pt, const char *s, const char *suffix);

bool_t s_strlower(char *s);
bool_t s_strupper(char *s);

bool_t s_strnlower(char *s, size_t n);
bool_t s_strnupper(char *s, size_t n);

char *sn_uppath(const char *filename, char path_delim);
char *sn_path(const char *filename, char path_delim);
char *sn_pathname(const char *filename, char path_delim);
char *sn_name(const char *filename, char path_delim);
char *sn_nameext(const char *filename, char path_delim);
char *sn_ext(const char *filename, char path_delim);

bool_t s_uppath(char **uppath, const char *filename, char path_delim);
bool_t s_path(char **path, const char *filename, char path_delim);
bool_t s_pathname(char **pathname, const char *filename, char path_delim);
bool_t s_name(char **name, const char *filename, char path_delim);
bool_t s_nameext(char **nameext, const char *filename, char path_delim);
bool_t s_ext(char **ext, const char *filename, char path_delim);

bool_t mkpath(const char *path, mode_t mode);

bool_t is_dos_filename(const char *filename);

bool_t is_equal_files(const char *filename0, const char *filename1);
bool_t is_equal_blocks(FILE * file, size_t offset0, size_t offset1,
                       size_t size);

char *binrw_strerror(binrw_error_t error);

/* Reads a Little Endian number between 1 and 4 bytes. */
binrw_error_t readl(FILE * file, size_t * pnum, size_t len);

/* Reads a Big Endian number between 1 and 4 bytes. */
binrw_error_t readb(FILE * file, size_t * pnum, size_t len);

/* Writes a Little Endian number between 1 and 4 bytes,
 * in case the transmitted number cannot be presented
 * as the specified number of bytes, fails. */
binrw_error_t writel(FILE * file, size_t num, size_t len);

/* Writes Big Endian number between 1 and 4 bytes,
 * in case the transmitted number cannot be presented
 * as the specified number of bytes, fails. */
binrw_error_t writeb(FILE * file, size_t num, size_t len);

/* Reads the specified number of bytes into the buffer. If the pointer
 * per buffer - NULL, reads bytes "to nowhere".*/
binrw_error_t readc(FILE * file, uint8_t * buf, size_t len);

/* Writes the specified number of bytes into the buffer. If the pointer
 * per buffer - NULL, writes new bytes.*/
binrw_error_t writec(FILE * file, uint8_t * buf, size_t len);

/* Reads a line of the specified size from the. If previous
 * buffer is not NULL, freed allocated buffer of
 * required size. The read data is padded with a zero
 * byte. If pointer to pointer to string is NULL,
 * the line is read "to nowhere". */
binrw_error_t readsn(FILE * file, char **s, size_t len);

/* Writes a string of the specified size to the file. If the string length
 * is greater than the specified value, the function terminates with an error. */
binrw_error_t writesn(FILE * file, char *s, size_t len);

/* Reads a Pascal-string from file. Previous buffer,
 * if it is not NULL, freed, allocated buffer of 
 * required size. The read data is padded with a zero
 * byte. If pointer to pointer to string is NULL,
 * the line is read "to nowhere". */
binrw_error_t readsp(FILE * file, char **s);

/* Writes a Pascal-string to the file. If string length
 * greater than 255 or pointer to string is NULL, function
 * fails. */
binrw_error_t writesp(FILE * file, char *s);

/* Reads and ASCIIZ-string from the file. Previous buffer,
 * if it is not NULL, freed, allocated buffer of
 * required size. The read data is padded with a zero
 * byte. If pointer to pointer to string is NULL,
 * the line is read "to nowhere". */
binrw_error_t readsz(FILE * file, char **s);

/* Writes an ASCIIZ-string to the file, If pointer to string
 * is NULL, the function returns with an error. */
binrw_error_t writesz(FILE * file, char *s);

binrw_error_t readf(FILE * file, char *format, ...);

binrw_error_t writef(FILE * file, char *format, ...);

binrw_error_t unpackl(buf_t * buf, size_t * pnum, size_t len);

binrw_error_t unpackb(buf_t * buf, size_t * pnum, size_t len);

binrw_error_t packl(buf_t * buf, size_t num, size_t len);

binrw_error_t packb(buf_t * buf, size_t num, size_t len);

binrw_error_t unpackc(buf_t * buf, uint8_t * bytes, size_t len);

binrw_error_t packc(buf_t * buf, uint8_t * bytes, size_t len);

binrw_error_t unpacksn(buf_t * buf, char **s, size_t len);

binrw_error_t packsn(buf_t * buf, char *s, size_t len);

binrw_error_t unpacksp(buf_t * buf, char **s);

binrw_error_t packsp(buf_t * buf, char *s);

binrw_error_t unpacksz(buf_t * buf, char **s);

binrw_error_t packsz(buf_t * buf, char *s);

binrw_error_t unpackf(buf_t * buf, char *format, ...);

binrw_error_t packf(buf_t * buf, char *format, ...);

void strtrim(char *s, const char *trim);

binrw_error_t scans(FILE * file, char **s, const char *terms, int *term);

time_t dos2unix_timestamp(const size_t timestamp);
time_t unix2dos_timestamp(const time_t timestamp);
bool_t s_time(char **p, const time_t timestamp);
#endif
