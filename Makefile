CC=gcc
CFLAGS_WARNING=-Wpedantic -Wall -Wextra
CFLAGS=-march=native -O3
CFLAGS+=-std=c11 -D_DEFAULT_SOURCE -D_FILE_OFFSET_BITS=64
# CFLAGS+=-O0 -g -ggdb3
CFLAGS+=-fno-omit-frame-pointer -fsanitize=address
LDFLAGS=-lz -lm -lc

all: pup

CFILES=bin.c \
       restable.c \
       grp.c \
       gob.c \
       pak.c \
       viv.c \
       vpp.c \
       pack.c \
       pack2.c \
       wad23.c \
       res.c \
       dpk4.c \
       dat.c \
       dat2.c \
       rff.c \
       labn.c \
       meta.c \
       c_zlib.c \
       c_pack2.c \
       c_lzss.c \
       c_dat.c \
       comdec.c

pup: main.c $(CFILES) Makefile
	$(CC) $(CFLAGS) -D_FILE_OFFSET_BITS=64 $(CFILES) main.c -o $@ $(LDFLAGS)

test: test.c bin.c Makefile
	$(CC) $(CFLAGS) $(CFLAGS_WARNING) bin.c test.c -o $@ $(LDFLAGS)
clean:
	rm -f pup
	rm -f test

