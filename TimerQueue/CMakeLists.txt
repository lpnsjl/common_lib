cmake_minimum_required(VERSION 3.10)
project(TimerQueue)

find_package(Threads)
aux_source_directory(. SRC)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} Threads::Threads)