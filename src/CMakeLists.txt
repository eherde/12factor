# project metadata
cmake_minimum_required(VERSION 2.8.12.2)
project(12factor)

# ext
find_library(HIREDIS NAMES libhiredis.a hiredis PATHS ../ext/dst/usr/local/lib)

# include
include_directories(include)

# build flags
set(CMAKE_C_FLAGS "-Wall -Wextra -g")

# libcore
add_library(core STATIC ../ext/bsd/strlcpy.c libcore/env.c libcore/signal.c libcore/time.c)

# rd
add_executable(rd rd/main.c rd/redis.c)
target_include_directories(rd PRIVATE ../ext/dst/usr/local/include)
target_link_libraries(rd ${HIREDIS})
target_link_libraries(rd core)

# install
install(TARGETS rd DESTINATION bin)
