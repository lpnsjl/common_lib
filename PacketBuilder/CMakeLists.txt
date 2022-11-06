cmake_minimum_required(VERSION 3.22)
project(PacketBuilder)

set(CMAKE_CXX_STANDARD 11)

add_executable(PacketBuilder main.cpp Buffer.cpp Buffer.h)
