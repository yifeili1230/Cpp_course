cmake_minimum_required(VERSION 3.14)
project(homework_4 LANGUAGES CXX)

# 1. 强制要求使用 C++17 标准（因为作业中的泛型和算法需要现代语法支持）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. 将包含头文件的 include 文件夹注册为全局公共路径
include_directories(include)

# 3. 核心：声明我们的算法库目标（虽然我们还没开始写 src/ipb_algorithm.cpp，先占个位）
#    C++ 需要把源文件编译成一个库（Library），供后面的测试程序去链接（Link）
add_library(ipb_algorithm src/ipb_algorithm.cpp)

# 4. 🔥 关键联动：拉开总指挥部的帷幕，把 tests 文件夹拉进构建版图！
add_subdirectory(tests)