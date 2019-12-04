#!/bin/sh

# apt-get install libc6-dev zlib1g-dev

rm test
gcc bin.c test.c -o test -std=c99 -Wpedantic -Wall -Wextra
./test
gcc bin.c restable.c grp.c gob.c pak.c viv.c vpp.c pack.c pack2.c wad23.c res.c dpk4.c dat.c dat2.c rff.c labn.c meta.c c_zlib.c c_pack2.c c_lzss.c c_dat.c comdec.c main.c -D_FILE_OFFSET_BITS=64 -I/usr/include/ -L/usr/lib/ -lz -std=c99 -Wpedantic -Wall -Wextra -o pup # -g
