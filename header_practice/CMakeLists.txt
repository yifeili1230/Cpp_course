cmake_minimum_required(VERSION 3.10)
project(header_practice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(tools tools.cpp)
add_executable(main main.cpp)
target_link_libraries(main tools)