#!/bin/sh

rm -rf autom4te.cache

# libtoolize
rm -f aclocal.m4
aclocal
autoreconf

rm -rf autom4te.cache

exit 0
