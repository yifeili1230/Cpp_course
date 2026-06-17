cmake_minimum_required(VERSION 3.10)
project(hw1_task_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_library(ipb_arithmetic src/sum.cpp src/subtract.cpp)
add_executable(main src/main.cpp)
target_link_libraries(main ipb_arithmetic)

# 定义安装规则
# 1. 安装库文件和可执行文件到 bin 目录
install(TARGETS ipb_arithmetic main
        DESTINATION bin)

# 2. 安装头文件到 include 目录
# 这样别人包含了你的 include 目录后，就能使用你的库了
install(DIRECTORY include/ipb_arithmetic
        DESTINATION include)