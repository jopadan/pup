cmake_minimum_required(VERSION 3.0)
project(pup LANGUAGES C)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "PUP - game resource Packer/UnPacker written in C")

include(GNUInstallDirs)
include(FindPkgConfig)

set(SRCDIR src)

set(CHECKSUM_SOURCES
	      ${SRCDIR}/chk/crc_ccitt32.c
)

set(CHECKSUM_INCLUDES
              ${SRCDIR}/chk/crc_ccitt32.h
)

set(COMPRESSION_SOURCES
              ${SRCDIR}/cmp/comdec.c
              ${SRCDIR}/cmp/c_zlib.c
              ${SRCDIR}/cmp/c_pack2.c
              ${SRCDIR}/cmp/c_lzss.c
              ${SRCDIR}/cmp/c_dat.c
)

set(COMPRESSION_INCLUDES
              ${SRCDIR}/cmp/comdec.h
              ${SRCDIR}/cmp/c_zlib.h
              ${SRCDIR}/cmp/c_pack2.h
              ${SRCDIR}/cmp/c_lzss.h
              ${SRCDIR}/cmp/c_dat.h
)

set(FORMAT_SOURCES
	      ${SRCDIR}/fmt/restable.c
	      ${SRCDIR}/fmt/res.c
	      ${SRCDIR}/fmt/dat.c
	      ${SRCDIR}/fmt/dat2.c
	      ${SRCDIR}/fmt/rff.c
	      ${SRCDIR}/fmt/labn.c
	      ${SRCDIR}/fmt/meta.c
	      ${SRCDIR}/fmt/dpk4.c
	      ${SRCDIR}/fmt/wad23.c
	      ${SRCDIR}/fmt/pack.c
	      ${SRCDIR}/fmt/pack2.c
	      ${SRCDIR}/fmt/vpp.c
	      ${SRCDIR}/fmt/viv.c
	      ${SRCDIR}/fmt/pak.c
	      ${SRCDIR}/fmt/gob.c
	      ${SRCDIR}/fmt/grp.c
)


set(FORMAT_INCLUDES
	${SRCDIR}/fmt/restable.h
	${SRCDIR}/fmt/res.h
	${SRCDIR}/fmt/dat.h
	${SRCDIR}/fmt/dat2.h
	${SRCDIR}/fmt/rff.h
	${SRCDIR}/fmt/labn.h
	${SRCDIR}/fmt/meta.h
	${SRCDIR}/fmt/dpk4.h
	${SRCDIR}/fmt/wad23.h
	${SRCDIR}/fmt/pack.h
	${SRCDIR}/fmt/pack2.h
	${SRCDIR}/fmt/vpp.h
	${SRCDIR}/fmt/viv.h
	${SRCDIR}/fmt/pak.h
	${SRCDIR}/fmt/gob.h
	${SRCDIR}/fmt/grp.h
)

set(OPTIONAL_FORMAT_SOURCES
	${SRCDOR}/fmt/pod.c
	${SRCDIR}/fmt/epd.c
	${SRCDIR}/fmt/pod1.c
	${SRCDIR}/fmt/pod2.c
	${SRCDIR}/fmt/pod3.c
	${SRCDIR}/fmt/pod4.c
	${SRCDIR}/fmt/pod5.c
	${SRCDIR}/fmt/pod6.c
)
set(OPTIONAL_FOMAT_INCLUDES
	${SRCDIR}/fmt/pod.h
	${SRCDIR}/fmt/pod_common.h
	${SRCDIR}/fmt/epd.h
	${SRCDIR}/fmt/pod1.h
	${SRCDIR}/fmt/pod2.h
	${SRCDIR}/fmt/pod3.h
	${SRCDIR}/fmt/pod4.h
	${SRCDIR}/fmt/pod5.h
	${SRCDIR}/fmt/pod6.h
)
set(SOURCE_FILES
	${CHECKSUM_SOURCES}
	${COMPRESSION_SOURCES}
	${FORMAT_SOURCES}
	${SRCDIR}/bin.c
	${SRCDIR}/main.c
)

set(INCLUDE_FILES
	${CHECKSUM_INCLUDES}
	${COMPRESSION_INCLUDES}
	${FORMAT_INCLUDES}
	${SRCDIR}/bin.h
)

set(TEST_SOURCE_FILES
	${SRCDIR}/bin.c
	${SRCDIR}/test.c
)

set(TEST_INCLUDES
	${SRCDIR}/bin.h
)

pkg_search_module(ZLIB REQUIRED zlib)
pkg_search_module(ZIP REQUIRED libzip)
pkg_search_module(PODFMT OPTIONAL libpodfmt)

if(PODFMT)
set(SOURCE_FILES ${SOURCE_FILES} ${OPTIONAL_SOURCE_FILES})
set(INCLUDE_FILES ${INCLUDE_FILES} ${OPTIONAL_INCLUDE_FILES})
endif()

# pup executable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES}
	${ZLIB_INCLUDE} ${ZIP_INCLUDE} ${PODFMT_INCLUDE})

target_compile_options( ${PROJECT_NAME} PUBLIC ${ZLIB_CFLAGS} ${ZIP_CFLAGS}
	${PODFMT_CFLAGS})

target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDEDIR}
	${ZIP_INCLUDEDIR} ${PODFMT_INCLUDEDIR}
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${SRCDIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${SRCDIR}/chk>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${SRCDIR}/cmp>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${SRCDIR}/fmt>
)

target_link_libraries( ${PROJECT_NAME} PUBLIC ${ZLIB_LIBRARIES}
			${ZIP_LIBRARIES} ${PODFMT_LIBRARIES} )
# test executable
add_executable( test ${TEST_SOURCE_FILES} ${TEST_INCLUDE_FILES}
	${ZLIB_INCLUDE} ${ZIP_INCLUDE} ${PODFMT_INCLUDE}
)
set_target_properties( test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR} )
add_test(test test)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

