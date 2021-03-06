# CMake Setup/Info
cmake_minimum_required(VERSION 3.10)
project(42sh)

# VARS
set(EXECUTABLE_OUTPUT_PATH .)
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

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  "../doc/latex"
  "../doc/html")

add_custom_target(doc
  COMMAND doxygen doc/Doxyfile
  WORKING_DIRECTORY ..
  COMMENT "Generating Doxygen documentation")

add_custom_target(man
  COMMAND man doc/42sh.1
  WORKING_DIRECTORY ..
  COMMENT "Generating Manual Page")

add_custom_target(check
  COMMAND bundle install --path=vendor/bundle
  COMMAND ./testsuite.rb
  DEPENDS ../build/42sh
  WORKING_DIRECTORY ../tests/
  COMMENT "Launching testsuite")

# TODO
## Check for package existence before using them
### TEMPLATE WOULD BE:
#find_package(package_name)
#if(PACKAGE_FOUND)
#else (PACKAGE_FOUND)
#  message("Doxygen needs to be installed to generate the doxygen documentation")
#endif (PACKAGE_FOUND)
