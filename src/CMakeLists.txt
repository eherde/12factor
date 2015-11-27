# project metadata
cmake_minimum_required(VERSION 2.8.12.2)
project(12factor)

# include
include_directories(include)

# build flags
set(CMAKE_C_FLAGS "-Wall -Wextra -g")

# libcore
add_library(core STATIC libcore/time.c)

# svc1
add_executable(svc1 svc1/main.c svc1/redis.c)
target_link_libraries (svc1 hiredis)
target_link_libraries(svc1 core)

# install
install(TARGETS svc1 DESTINATION bin)
