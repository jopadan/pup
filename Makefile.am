AUTOMAKE_OPTIONS = foreign subdir-objects

SRCDIR=src
RESOURCE_FORMAT_FILES=restable.c \
                      res.c \
		      restable.h \
                      res.h \
		      dat.h \
		      dat2.h \
		      rff.h \
		      labn.h \
		      meta.h \
		      dpk4.h \
		      wad23.h \
		      pack.h \
		      pack2.h \
		      vpp.h \
		      viv.h \
		      pak.h \
		      gob.h \
		      grp.h

COMPRESSION_FORMAT_FILES=

dist_doc_DATA = README.md INSTALL.md LICENSE ChangeLog

bin_PROGRAMS = pup test

AM_CPPFLAGS = -Isrc/ -Isrc/cmp/ -Isrc/fmt/
AM_LDFLAGS = -Lsrc/ -Lsrc/cmp/ -Lsrc/fmt/
pup_SOURCES = \
              ${SRCDIR}/cmp/comdec.c \
              ${SRCDIR}/cmp/comdec.h \
              ${SRCDIR}/cmp/c_zlib.c \
              ${SRCDIR}/cmp/c_zlib.h \
              ${SRCDIR}/cmp/c_pack2.c \
              ${SRCDIR}/cmp/c_pack2.h \
              ${SRCDIR}/cmp/c_lzss.c \
              ${SRCDIR}/cmp/c_lzss.h \
              ${SRCDIR}/cmp/c_dat.c \
              ${SRCDIR}/cmp/c_dat.h \
	      ${SRCDIR}/fmt/restable.c \
	      ${SRCDIR}/fmt/restable.h \
	      ${SRCDIR}/fmt/res.c \
	      ${SRCDIR}/fmt/res.h \
	      ${SRCDIR}/fmt/dat.c \
	      ${SRCDIR}/fmt/dat.h \
	      ${SRCDIR}/fmt/dat2.c \
	      ${SRCDIR}/fmt/dat2.h \
	      ${SRCDIR}/fmt/rff.c \
	      ${SRCDIR}/fmt/rff.h \
	      ${SRCDIR}/fmt/labn.c \
	      ${SRCDIR}/fmt/labn.h \
	      ${SRCDIR}/fmt/meta.c \
	      ${SRCDIR}/fmt/meta.h \
	      ${SRCDIR}/fmt/dpk4.c \
	      ${SRCDIR}/fmt/dpk4.h \
	      ${SRCDIR}/fmt/wad23.c \
	      ${SRCDIR}/fmt/wad23.h \
	      ${SRCDIR}/fmt/pack.c \
	      ${SRCDIR}/fmt/pack.h \
	      ${SRCDIR}/fmt/pack2.c \
	      ${SRCDIR}/fmt/pack2.h \
	      ${SRCDIR}/fmt/vpp.c \
	      ${SRCDIR}/fmt/vpp.h \
	      ${SRCDIR}/fmt/viv.c \
	      ${SRCDIR}/fmt/viv.h \
	      ${SRCDIR}/fmt/pak.c \
	      ${SRCDIR}/fmt/pak.h \
	      ${SRCDIR}/fmt/gob.c \
	      ${SRCDIR}/fmt/gob.h \
	      ${SRCDIR}/fmt/grp.c \
	      ${SRCDIR}/fmt/grp.h \
	      ${SRCDIR}/bin.c \
	      ${SRCDIR}/bin.h \
	      ${SRCDIR}/main.c

test_SOURCES = ${SRCDIR}/bin.c \
               ${SRCDIR}/bin.h \
               ${SRCDIR}/test.c

