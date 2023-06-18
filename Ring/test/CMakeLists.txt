include_directories(..)
file(GLOB RING_SRC ${CMAKE_SOURCE_DIR}/*.cpp)

find_package(Threads)

add_executable(RingWriter ${RING_SRC} RingWriter.cpp)
target_link_libraries(RingWriter Threads::Threads)

add_executable(RingReader ${RING_SRC} RingReader.cpp)
target_link_libraries(RingReader Threads::Threads)