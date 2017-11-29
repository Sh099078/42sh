project(main)

file(GLOB_RECURSE OBJS src/*.c)

file(GLOB_RECURSE HEADERS src/*.h)

add_executable(main ${OBJS} ${HEADERS})
