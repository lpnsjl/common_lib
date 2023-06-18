cmake_minimum_required(VERSION 3.16)
project(Ring)

set(CMAKE_CXX_STANDARD 11)

#add_executable(Ring main.cpp Ring.cpp Ring.h mkdirs.h CSem.cpp CSem.h CShm.cpp CShm.h barrier.h)
#target_link_libraries(Ring Threads::Threads)
add_subdirectory(test)
