cmake_minimum_required(VERSION 3.16)
project(NTPClient)

set(CMAKE_CXX_STANDARD 11)
aux_source_directory(. SRC)
add_executable(${PROJECT_NAME} ${SRC})