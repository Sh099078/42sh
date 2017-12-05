project(42sh)

add_executable(42sh src/exec/simple_cmd.c)
include_directories(src)

#file(GLOB_RECURSE OBJS src/*.c)

#file(GLOB_RECURSE HEADERS src/*.h)

#add_executable(main ${OBJS} ${HEADERS})
