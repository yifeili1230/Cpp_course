#!/bin/bash

# 1. 创建并进入 build 文件夹
mkdir -p build
cd build

# 2. 编译阶段 (Compilation)
# 注意：因为现在在 build 文件夹里，所以找源码要用 ../src
# 找头文件要用 -I../include
c++ -std=c++17 -c ../src/sum.cpp -I../include/ -o sum.o
c++ -std=c++17 -c ../src/subtract.cpp -I../include/ -o subtract.o
c++ -std=c++17 -c ../src/main.cpp -I../include/ -o main.o

# 3. 链接阶段 (Linking)
# 所有的 .o 都在当前 build 文件夹下，直接链接即可
c++ -std=c++17 main.o sum.o subtract.o -o main_executable