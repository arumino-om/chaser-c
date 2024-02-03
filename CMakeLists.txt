cmake_minimum_required(VERSION 3.27)
project(chaser_c C)

set(CMAKE_C_STANDARD 11)

option(CHASERC_BUILD_SHARED_LIBRARY "build chaser-c as a shared library" OFF)

if (CHASERC_BUILD_SHARED_LIBRARY)
    add_library(chaser_c SHARED
            src/chaser_server.c
            src/chaser_server.h)
else()
    add_library(chaser_c STATIC
            src/chaser_server.c
            src/chaser_server.h)
endif()