cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#初始化根项目 最好放在standard后面进行
project(scheduler LANGUAGES CXX)

file(GLOB srcs *.h *.cpp json.hpp)

add_executable(scheduler ${srcs})

#加入json子目录,这条命令会调用json/CMakelists.txt
add_subdirectory(task)

target_link_libraries(scheduler task)
