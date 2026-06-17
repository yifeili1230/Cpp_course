#!/bin/bash

# 1. 创建 build 目录并进入
mkdir -p build
cd build

# 2. 运行 CMake 并指定安装路径为项目根目录下的 install 文件夹
# CMAKE_INSTALL_PREFIX 必须使用绝对路径
cmake .. -DCMAKE_INSTALL_PREFIX=../install

# 3. 编译并安装
make
make install

echo "安装完成！请检查根目录下的 install/ 文件夹。"