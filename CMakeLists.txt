cmake_minimum_required(VERSION 3.0)
project(pup LANGUAGES C)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "PUP - game resource Packer/UnPacker written in C")

include(GNUInstallDirs)
include(FindPkgConfig)

set(CHECKSUM_SOURCES
	      src/chk/ccitt32.c
)

set(CHECKSUM_INCLUDES
              src/chk/ccitt32.h
)

set(COMPRESSION_SOURCES
              src/cmp/comdec.c
              src/cmp/c_zlib.c
              src/cmp/c_pack2.c
              src/cmp/c_lzss.c
              src/cmp/c_dat.c
)

set(COMPRESSION_INCLUDES
              src/cmp/comdec.h
              src/cmp/c_zlib.h
              src/cmp/c_pack2.h
              src/cmp/c_lzss.h
              src/cmp/c_dat.h
)

set(FORMAT_SOURCES
	src/fmt/restable.c
	src/fmt/res.c
	src/fmt/dat.c
	src/fmt/dat2.c
	src/fmt/rff.c
	src/fmt/labn.c
	src/fmt/meta.c
	src/fmt/dpk4.c
	src/fmt/wad23.c
	src/fmt/pack.c
	src/fmt/pack2.c
	src/fmt/vpp.c
	src/fmt/viv.c
	src/fmt/pak.c
	src/fmt/gob.c
	src/fmt/grp.c
	src/fmt/pod.c
	src/fmt/epd.c
	src/fmt/pod1.c
	src/fmt/pod2.c
	src/fmt/pod3.c
	src/fmt/pod4.c
	src/fmt/pod5.c
	src/fmt/pod6.c
	)


set(FORMAT_INCLUDES
	src/fmt/restable.h
	src/fmt/res.h
	src/fmt/dat.h
	src/fmt/dat2.h
	src/fmt/rff.h
	src/fmt/labn.h
	src/fmt/meta.h
	src/fmt/dpk4.h
	src/fmt/wad23.h
	src/fmt/pack.h
	src/fmt/pack2.h
	src/fmt/vpp.h
	src/fmt/viv.h
	src/fmt/pak.h
	src/fmt/gob.h
	src/fmt/grp.h
	src/fmt/pod.h
	src/fmt/epd.h
	src/fmt/pod1.h
	src/fmt/pod2.h
	src/fmt/pod3.h
	src/fmt/pod4.h
	src/fmt/pod5.h
	src/fmt/pod6.h
)

set(SOURCE_FILES
	${CHECKSUM_SOURCES}
	${COMPRESSION_SOURCES}
	${FORMAT_SOURCES}
	src/bin.c
	src/main.c
)

set(INCLUDE_FILES
	${CHECKSUM_INCLUDES}
	${COMPRESSION_INCLUDES}
	${FORMAT_INCLUDES}
	src/bin.h
)

set(TEST_SOURCE_FILES
	src/bin.c
	src/test.c
)

set(TEST_INCLUDES
	src/bin.h
)

pkg_search_module(ZLIB REQUIRED zlib)
pkg_search_module(ZIP REQUIRED libzip)
pkg_search_module(PODFMT REQUIRED libpodfmt)

# pup executable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES}
	${ZLIB_INCLUDE} ${ZIP_INCLUDE} ${PODFMT_INCLUDE})

target_compile_options( ${PROJECT_NAME} PUBLIC ${ZLIB_CFLAGS} ${ZIP_CFLAGS}
	${PODFMT_CFLAGS})

target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDEDIR}
	${ZIP_INCLUDEDIR} ${PODFMT_INCLUDEDIR}
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/chk>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/cmp>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/fmt>
)

set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR} )
target_link_libraries( ${PROJECT_NAME} PUBLIC ${ZLIB_LIBRARIES}
			${ZIP_LIBRARIES} ${PODFMT_LIBRARIES} )
# test executable
add_executable( test ${TEST_SOURCE_FILES} ${TEST_INCLUDES}
	${ZLIB_INCLUDE} ${ZIP_INCLUDE} ${PODFMT_INCLUDE}
)
set_target_properties( test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_BINARY_DIR} )
add_test(test test)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

