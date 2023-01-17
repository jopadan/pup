cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)
project(pup LANGUAGES C)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "PUP - game resource Packer/UnPacker written in C")

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-march=native -O3)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-ffunction-sections)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wpedantic)
add_link_options(-Wl,--gc-sections)
#add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

# input sources
file(GLOB PUP_SOURCES LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS FALSE PATTERN *.c)
list(FILTER PUP_SOURCES EXCLUDE REGEX test.c)

# external dependencies
find_package(ZLIB REQUIRED)

# pup executable
add_executable(${PROJECT_NAME} ${PUP_SOURCES}) 
target_compile_options(${PROJECT_NAME} PUBLIC ${ZLIB_CFLAGS})
target_include_directories(${PROJECT_NAME} PUBLIC ${ZLIB_INCLUDE_DIR} $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

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

