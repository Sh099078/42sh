# CMake Setup/Info
cmake_minimum_required(VERSION 3.10)
project(42sh)

# VARS
set(EXECUTABLE_OUTPUT_PATH ../)
set(BROWSER chromium)
file(GLOB_RECURSE SRC src/*.c)
file(GLOB_RECURSE HDR build/*.h)

# FLAGS
set(CMAKE_C_FLAGS "-std=c99 -pedantic -Wall -Wextra -Werror -g")
include_directories(includes)
add_definitions(-D_POSIX_C_SOURCE=200809L)
add_executable(42sh ${SRC} ${HDR})
target_link_libraries(42sh readline)

# CUSTOM RULES

add_custom_target(doc
  COMMAND pwd
  COMMAND doxygen src/Doxyfile
  COMMAND $(BROWSER) doc/html/index.html
  WORKING_DIRECTORY ..
  COMMENT Generating Doxygen documentation)

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


