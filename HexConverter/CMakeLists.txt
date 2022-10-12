cmake_minimum_required(VERSION 3.22)
project(HexConverter)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp HexConverter.cpp)
