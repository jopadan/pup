#include <stdlib.h>
#include "comdec.h"

comdec_t comdec_zlib = { &zlib_dsize, &zlib_compress, &zlib_decompress };
comdec_t comdec_pack2 = { &pack2_dsize, &pack2_compress, &pack2_decompress };
comdec_t comdec_lzss = { &lzss_dsize, &lzss_compress, &lzss_decompress };
comdec_t comdec_dat = { &dat_dsize, &dat_compress, &dat_decompress };

bool_t c_addfile(FILE * dst, const char *src_filename, size_t * size,
              size_t * compressed, comdec_t * comdec, int level)
{
  void *s;
  void *d;

  if (dst == NULL)
  {
    fprintf(stderr, "c_addfile: dst == NULL.\n");
    return FALSE;
  }
  if (src_filename == NULL)
  {
    fprintf(stderr, "c_addfile: src_filename == NULL.\n");
    return FALSE;
  }
  if (size == NULL)
  {
    fprintf(stderr, "c_addfile: size == NULL.\n");
    return FALSE;
  }
  if (compressed == NULL)
  {
    fprintf(stderr, "c_addfile: compressed == NULL.\n");
    return FALSE;
  }
  if (comdec == NULL)
  {
    fprintf(stderr, "c_addfile: comdec == NULL.\n");
    return FALSE;
  }
  if ((level < 0) || (level > 9))
  {
    fprintf(stderr, "c_addfile: wrong level.\n");
    return FALSE;
  }
  *compressed = 0;
  s = loadfile(src_filename, size);
  if (*size == 0)
    return TRUE;
  if (s == NULL)
  {
    fprintf(stderr, "c_addfile: loadfile failed.\n");
    return FALSE;
  }
  if (level != 0)
  {
    *compressed = comdec->dsize(*size);
    d = malloc(*compressed);
    if (d != NULL)
    {
      if (comdec->compress(s, *size, d, compressed, level) == FALSE)
      {
        fprintf(stderr,
                "c_addfile: compression failed, trying to add uncompressed data.\n");
        free(d);
        *compressed = *size;
      }
      else if (*compressed >= *size)
      {
        fprintf(stderr,
                "c_addfile: compression not effective, trying to add uncompressed data.\n");
        free(d);
        *compressed = *size;
      }
      else
      {
        free(s);
        s = d;
      }
    }
    else
    {
      fprintf(stderr,
              "c_addfile: can't get memory for compression, trying to add uncompressed data.\n");
      *compressed = *size;
    }
  }
  else
    *compressed = *size;
  if (saveblock(dst, s, *compressed) == FALSE)
  {
    fprintf(stderr, "c_addfile: saveblock failed.\n");
    free(s);
    return FALSE;
  }
  free(s);
  if (*compressed == *size)
    *compressed = 0;
  return TRUE;
}

bool_t c_extractfile(const char *dst_filename, FILE * src, size_t size,
                  size_t compressed, comdec_t * comdec)
{
  void *s;
  void *d;
  FILE *file;

  if (dst_filename == NULL)
  {
    fprintf(stderr, "c_extractfile: dst_filename == NULL.\n");
    return FALSE;
  }
  if (src == NULL)
  {
    fprintf(stderr, "c_extractfile: src == NULL.\n");
    return FALSE;
  }
  if (size == 0)
  {
    file = fopen(dst_filename, "wb");
    if (file == NULL)
    {
      fprintf(stderr, "c_extractfile: Can't extract empty file.\n");
      return FALSE;
    }
    fclose(file);
    return TRUE;
  }
  if (comdec == NULL)
  {
    fprintf(stderr, "c_extractfile: comdec == NULL.\n");
    return FALSE;
  }

  if (compressed == 0)
    s = loadblock(src, size);
  else
    s = loadblock(src, compressed);
  if (s == NULL)
  {
    fprintf(stderr, "c_extractfile: loadblock failed.\n");
    return FALSE;
  }

  if (compressed != 0)
  {
    d = malloc(size);
    if (d == NULL)
    {
      fprintf(stderr, "c_extractfile: can't get memory for decompression.\n");
      free(s);
      return FALSE;
    }
    if (comdec->decompress(s, compressed, d, size) == FALSE)
    {
      fprintf(stderr, "c_extractfile: decompression failed.\n");
      free(s);
      free(d);
      return FALSE;
    }
    free(s);
    s = d;
  }

  if (savefile(dst_filename, s, size) == FALSE)
  {
    fprintf(stderr, "c_extractfile: savefile failed.\n");
    free(s);
    return FALSE;
  }
  free(s);
  return TRUE;
}
