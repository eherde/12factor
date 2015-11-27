# project metadata
cmake_minimum_required(VERSION 2.8.12.2)
project(12factor)

# include
include_directories(include)

# build flags
set(CMAKE_C_FLAGS "-Wall -Wextra -g")

# libcore
add_library(core STATIC libcore/signal.c libcore/time.c)

# rd
add_executable(rd rd/main.c rd/redis.c)
target_link_libraries(rd hiredis)
target_link_libraries(rd core)

# install
install(TARGETS rd DESTINATION bin)
