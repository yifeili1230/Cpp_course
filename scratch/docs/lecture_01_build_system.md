> 💡 **核心思想：** > * 想要彻底理解一个 C++ 项目，最好的切入点就是它的**构建系统 (Build System)**。
> 
> - 工具（如特定的构建命令）在 5 年内可能会改变，但底层的**构建概念**基本保持不变。花时间理解概念能带来更长远的收益。 05:05 Opens in a new window
> - 视频原地址：Modern C++: Build and Tools (Lecture 1, I. Vizzo, 2020)

---

## 1. C++ 编译的四大阶段 (Compilation Process)

当我们在终端调用编译器（如 `clang++`）时，背后其实默默执行了四个Distinct阶段。 08:48 Opens in a new window

### ① 预处理 (Pre-processing)

- **做什么：** 展开宏定义（`#define`）、处理条件编译、删除所有代码注释，并将 `#include` 包含的头文件内容直接复制粘贴到源文件中。 13:04 Opens in a new window
- **手动执行命令：**Bash
    
    `clang++ -E main.cpp -o main.i`
    
    *(注：预处理后的 `.i` 文件体积会暴增，因为里面包含了标准库头文件的所有代码。 15:09 Opens in a new window )*
    

### ② 编译 (Compilation)

- **做什么：** 将预处理后的高级语言代码翻译成对应目标架构（如 Intel CPU）的**汇编代码**。 16:11 Opens in a new window
- **手动执行命令：**Bash
    
    `clang++ -S main.i -o main.s`
    

### ③ 汇编 (Assembly)

- **做什么：** 将汇编代码转换为机器可执行的二进制代码，生成**目标文件 (Object File)**。 17:32 Opens in a new window
- **手动执行命令：**Bash
    
    `clang++ -c main.s -o main.o`
    

### ④ 链接 (Linking)

- **做什么：** 将一个或多个目标文件与系统库、外部库联合在一起，填充所有未解决的符号引用（例如函数实现的地址），最终生成可执行二进制文件。 18:31 Opens in a new window
- **手动执行命令：**Bash
    
    `clang++ main.o -o main`
    

---

## 2. 核心语法概念：声明与定义的分离

在 C++ 中，为了支持模块化和库的构建，通常需要将函数的声明 (Declaration)**和**定义 (Definition)分开： 24:31 Opens in a new window

### 概念解析

- **函数声明（接口）：** 相当于给编译器的“承诺 (Promise)”。告诉编译器这个函数叫什么、接收什么参数、返回什么类型，具体的实现会在链接时补上。末尾必须加分号 `;`。 25:07 Opens in a new window , 26:20 Opens in a new window
- **函数定义（实现）：** 包含函数具体逻辑的代码块。 25:14 Opens in a new window

### 🛠️ 详细代码例子：手动分立文件

我们需要编写三个文件：头文件、实现文件和主程序文件。

### 1. 头文件：`tools.hpp`

> 💡 `#pragma once` 是为了防止该头文件在同一个编译单元中被多次包含（Include 保护）。 35:25 Opens in a new window
> 

C++

```jsx
#pragma once

// 函数声明 (Promises)
void MakeItSunny();
void MakeItRain();
```

### 2. 实现文件：`tools.cpp`

C++

```cpp
#include "tools.hpp"
#include <iostream>

// 函数定义 (Implementations)
void MakeItSunny() {
    std::cout << "This is Sunny implementation" << std::endl;
}

void MakeItRain() {
    std::cerr << "Oops, not yet implemented!" << std::endl;
}
```

### 3. 主程序：`main.cpp`

C++

```cpp
#include "tools.hpp" // 只需引入声明接口

int main() {
    MakeItRain();
    MakeItSunny();
    return 0;
}
```

#### 3.1 头文件hpp和cpp #include 和linker

❌ **误区：** 认为 `#include "tools.hpp"` 会自动把同名 `tools.cpp` 的实际内容替换/复制过来。

**正解：** > 1. `#include` **只复制 `.hpp` 中的声明**（给编译器的承诺）。
2. `.cpp` 文件的实际内容是在**链接阶段（Linking）由链接器将各个 `.o` 目标文件缝合在一起的。
3. 文件同名只是为了人类可读性，编译器和链接器只认你在编译命令**（或 `CMakeLists.txt`）里明确写出来的源文件。

#### 3.11 同样命名函数的同时include

假设我们在项目中有两个不同的实现文件 `tools_a.cpp` 和 `tools_b.cpp`：

### ❌ 场景 1：普通全局函数（导致链接报错）

如果你直接在两个文件里硬编码同名函数：

C++

```cpp
// tools_a.cpp
void makeItSunny() { /* 实现 A */ }

// tools_b.cpp
void makeItSunny() { /* 实现 B */ }
```

- **结果：** 链接器（Linker）在缝合 `.o` 文件时会罢工，报 `multiple definition of 'makeItSunny'`。因为它在全局符号表里找到了两个一模一样的名字，不知道该调用哪一个。

---

### 场景 2：匿名命名空间 / `static`（内部函数）

现代 C++ 推荐使用匿名命名空间，效果等同于给函数加 `static`：

C++

```cpp
// tools_a.cpp
namespace {
    void makeItSunny() { /* 只在 tools_a.cpp 内部有效 */ }
}

// tools_b.cpp
namespace {
    void makeItSunny() { /* 只在 tools_b.cpp 内部有效 */ }
}
```

- **底层黑魔法：** 编译器默默在后台为它们生成了别人绝对猜不到的、独一无二的空间名（如 `_UNIQUE_A::makeItSunny`）。因为别的 `.cpp` 拿不到这个隐藏密码，所以它们被**死死锁在各自的文件内部**。链接器会直接忽略它们，完美避开冲突。

---

### 场景 3：具名命名空间（带“姓氏”的全局社交）

这是现代 C++ 规范最推崇的跨文件协作方式，显式地给命名空间加上名字：

C++

```cpp
// tools_a.cpp
namespace A {
    void makeItSunny() { /* 空间 A 的全局实现 */ }
}

// tools_b.cpp
namespace B {
    void makeItSunny() { /* 空间 B 的全局实现 */ }
}
```

- **底层黑魔法：** 编译器会把空间名注入到最终的函数符号中（这个过程叫 *Name Mangling*）。链接器看到的不再是孤零零的 `makeItSunny`，而是打上品牌标签的 `A::makeItSunny`。
- **调用方式：** 依然是全局可访问的，外部只需通过 `A::makeItSunny()` 或 `B::makeItSunny()` 加上“姓氏”前缀即可精准调用，绝不撞车。

---

## 3. 手动构建静态库 (Static Library)

有了上述三个文件，如果直接运行 `clang++ main.cpp` 会报错（Linker Error），因为找不到实现的二进制符号。 38:45 Opens in a new window  我们需要手动打包一个静态库。

### 🛠️ 详细构建步骤与命令

Bash

```cpp
# 步骤 1: 将库的实现文件编译为目标文件 (.o)
# -std=c++17 指定标准，-c 表示只编译不链接
clang++ -std=c++17 -c tools.cpp -o tools.o

# 步骤 2: 使用 ar (Archive) 工具将目标文件打包为静态库 (.a)
# r 表示替换/插入文件，cs 表示创建索引
ar rcs libtools.a tools.o

# 步骤 3: 编译主程序并链接我们刚刚生成的静态库
# -L. 告诉链接器在当前目录寻找库
# -ltools 链接名为 libtools.a 的库 (注意去掉 lib 前缀和 .a 后缀)
clang++ -std=c++17 main.cpp -L. -ltools -o main

# 步骤 4: 运行可执行文件
./main
```

> 📌 **静态链接 (Static) vs 动态链接 (Dynamic)：**
> 
> - **静态库 (`.a` / `.lib`)：** 发生在**编译/链接期**。库中的二进制代码会被直接复制到最终的可执行文件中。程序体积变大，但运行速度稍快，且不依赖外部环境。 23:27 Opens in a new window , 58:35 Opens in a new window
> - **动态库 (`.so` / `.dll`)：** 发生在**运行期**。可执行程序只包含符号引用，运行时动态去系统目录（如 `/user/lib`）加载对应的库文件。如果运行时找不到 `.so` 文件，程序会崩溃。 23:53 Opens in a new window , 58:57 Opens in a new window

---

## 4. CMake 金属构建系统 (Meta-Build System)

当项目有几千个文件时，手写编译命令是不现实的。**CMake 本身并不是构建系统**，它是一个“构建系统生成器”，用来帮我们自动生成 Makefiles 或 Ninja 文件。 44:11 Opens in a new window , 44:20 Opens in a new window

### 🛠️ 详细代码例子：`CMakeLists.txt`

在项目根目录下创建一个名为 `CMakeLists.txt` 的文件：

CMake

```jsx
# 1. 规定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 定义项目名称
project(FirstProject)

# 3. 全局设置 C++ 标准为 C++17 (对应编译选项 -std=c++17)
set(CMAKE_CXX_STANDARD 17)

# 4. 强制要求编译器必须支持该标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 5. 可选：开启所有的编译器警告选项 (对应 -Wall)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# 6. 【核心】创建静态库 target
# 语法：add_library(<库名称> <源文件1> <源文件2> ...)
add_library(tools tools.cpp)

# 7. 【核心】创建可执行文件 target
# 语法：add_executable(<可执行文件名> <主程序源文件>)
add_executable(main main.cpp)

# 8. 【核心】将可执行文件与库进行链接
# 语法：target_link_libraries(<目标> <要链接的库>)
target_link_libraries(main tools)

# 9. 导出编译命令生成 compile_commands.json (供各种 IDE 和补全工具使用)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

### ⚙️ 标准的 CMake 构建流程

在项目根目录下，遵循“院外构建 (Out-of-source Build)”的规范： 47:01 Opens in a new window

Bash

```jsx
# 1. 创建并进入一个专门存放构建产物的 build 文件夹
mkdir build && cd build

# 2. 运行 CMake，让它读取上一级目录 (..) 的 CMakeLists.txt 并生成 Makefile
cmake ..

# 3. 调用实际的构建工具（如 make）执行编译和链接
make

# 4. 执行生成的程序
./main
```

> 💡 **小贴士：** 如果构建配置被搞乱了或者遇到奇奇怪怪的缓存错误，最直接有效的办法就是将 `build` 文件夹整个删掉，然后重新创建并重新执行 `cmake ..`
>