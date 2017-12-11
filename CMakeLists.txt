cmake_minimum_required(VERSION 3.10)

project(42sh)

set(EXECUTABLE_OUTPUT_PATH ../)

set(CMAKE_C_FLAGS "-std=c99 -pedantic -Wall -Wextra -Werror -lreadline -g \
-D_POSIX_C_SOURCE=200809L")

#include_directories(src)
#include_directories(src/parser)

file(GLOB_RECURSE SRC src/*.c)
file(GLOB_RECURSE HDR build/*.h)

include_directories(includes)

add_executable(42sh ${SRC} ${HDR})

#option(BUILD_DOC "Build documentation" ON)
#find_package(Doxygen)
#if(DOXYGEN_FOUND)
#  add_custom_target(doc_doxygen ALL
#    COMMAND doxygen ../Doxyfile
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    COMMENT "Generating API documentation with Doxygen"
#    VERBATIM )
#else (DOXYGEN_FOUND)
#  message("Doxygen needs to be installed to generate the doxygen documentation")
#endif (DOXYGEN_FOUND)


