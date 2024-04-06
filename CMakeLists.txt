cmake_minimum_required(VERSION 3.10)
project(DesignPattern)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 设置头文件目录
set(INCLUDE_DIR ./include)
aux_source_directory(./src SRC)

# 添加可执行文件
add_executable(DesignPattern ${SRC})

# 设置链接头文件
target_include_directories(DesignPattern PUBLIC ${INCLUDE_DIR})
