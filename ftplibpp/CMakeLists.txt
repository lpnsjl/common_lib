cmake_minimum_required(VERSION 3.16)
project(ftpclient)

set(CMAKE_CXX_STANDARD 11)
# 如果不需要SSL加密功能，可以添加-DNOSSL选项屏蔽，然后不需要链接ssl, crypto; 否则必须链接ssl, crypto
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOSSL")
aux_source_directory(. SRC)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ssl crypto)