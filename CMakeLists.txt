#cmake_minimum_required(VERSION 3.10)

project(42sh)

set(EXECUTABLE_OUTPUT_PATH ../)

set(
  SRC
  src/input_handler.c
  src/prompt.c
  src/parser.c
  src/ast.c )

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(doc_doxygen ALL
    COMMAND doxygen ../Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

add_executable(42sh ${SRC})

#include_directories(src)
