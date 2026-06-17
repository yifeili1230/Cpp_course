cmake_minimum_required(VERSION 3.10)
project(image_browser_app)

# 1. 强制开启 C++17 标准（std::filesystem 标配）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. 自动把编译出的库或程序扔到 bin 目录中（对齐测试脚本）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 3. 指定头文件搜索路径：告诉编译器 .hpp 全在 include 文件夹里
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. 收集所有的业务实现代码
set(SOURCE_FILES
    src/html_writer.cpp
    src/image_browser.cpp
    src/main.cpp
)

# 5. 将它们编译成一个统一的静态库（或者是可执行程序，取决于助教测试脚本的玩法）
add_executable(main ${SOURCE_FILES})

target_link_libraries(main PUBLIC stdc++fs)