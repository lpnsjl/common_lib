cmake_minimum_required(VERSION 3.16)
project(LinuxUtility)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
aux_source_directory(. SRC)
add_executable(${PROJECT_NAME} ${SRC})