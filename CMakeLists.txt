cmake_minimum_required(VERSION 3.0)
project(pup LANGUAGES C)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "PUP - game resource Packer/UnPacker written in C")

include(GNUInstallDirs)
include(FindPkgConfig)

file(GLOB PUP_SOURCES LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS *.c)
list(FILTER PUP_SOURCES EXCLUDE REGEX test.c)
file(GLOB PUP_INCLUDES LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS *.h)

find_package(ZLIB REQUIRED)

# pup executable
add_executable(${PROJECT_NAME} ${PUP_SOURCES} ${PUP_INCLUDES})
target_compile_options(${PROJECT_NAME} PUBLIC ${ZLIB_CFLAGS})
target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDEDIR}
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${ZLIB_LIBRARIES})

# test executable
add_executable(test bin.c test.c bin.h)
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(test test)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

