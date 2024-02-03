cmake_minimum_required(VERSION 3.27)
project(chaser_c CXX)

set(CMAKE_C_STANDARD 11)

option(CHASERC_BUILD_SHARED_LIBRARY "build chaser-c as a shared library" OFF)

if (CHASERC_BUILD_SHARED_LIBRARY)
    add_library(chaser_c SHARED
            src/asahikawa/chaser_client.cc
            src/asahikawa/chaser_client.h
            src/chaser_socket/socket_interface.cc
            src/chaser_socket/socket_interface.h
            src/chaser_socket/socket_winsock2.cc
            src/chaser_socket/socket_winsock2.h)
else()
    add_library(chaser_c STATIC
            src/asahikawa/chaser_client.cc
            src/asahikawa/chaser_client.h
            src/chaser_socket/socket_interface.cc
            src/chaser_socket/socket_interface.h
            src/chaser_socket/socket_winsock2.cc
            src/chaser_socket/socket_winsock2.h)
endif()