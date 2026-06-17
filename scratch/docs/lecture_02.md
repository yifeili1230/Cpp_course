# Modern C++ 笔记 | Lecture 2: Core C++

## 1. C++ 基础术语与实体 (Glossary & Entities)

### 📌 核心概念

- **声明 (Declaration):** 向编译器引入一个名字（标识符）并定义其类型，但不一定分配内存或实现细节。
- **定义 (Definition):** 声明的超集。不仅引入名字，还提供完整的实现细节（如函数体、变量的内存空间、类的完整结构）。
- **实体 (Entities):** C++ 中的值、对象、引用、函数、命名空间等都被称为实体。**注意：预处理器宏（Pre-processor Macros）不属于 C++ 实体。**
- **关键字 (Keywords):** C++ 语言保留的字（如 `const`, `auto`, `friend`），不能用作自定义标识符。
- **标识符 (Identifiers):** 用户自定义的变量名、函数名等。
    - ❌ 不能以数字开头（如 `1_variable` 是非法的）。
    - ⚠️ 区分大小写（`myVar` 和 `myvar` 是两个不同的实体）。

### 🛠️ 代码示例

C++

```cpp
#include <iostream>

// 这是一个函数声明 (Declaration)
void sayHello(); 

// 这是一个不完整类型的声明 (Incomplete Type)
struct MyType; 

// 这是一个完整类型的定义 (Definition)
struct MyType {
    int id; // 变量定义
};

int main() {
    int foo = 42; // 语句 (Statement) 必须以分号结尾
    int bar = foo + 8; // "foo + 8" 是一个表达式 (Expression)
    return 0;
}

// 这是一个完整的函数定义 (Definition)
void sayHello() {
    std::cout << "Hello!" << std::endl;
}
```

---

## 2. 作用域与生命周期 (Scope & Lifetime)

### 📌 核心概念

- **大括号 `{}` 的魔力：** 在 C++ 中，任何一对花括号 `{}` 都会开辟一个新的**局部作用域（Local Scope）** 09:53 Opens in a new window 。
- **生命周期：** 变量和对象只能在它被声明的作用域内保持有效。一旦程序运行到该作用域的结束花括号 `}`，该变量会立即被销毁（析构） 10:30 Opens in a new window 。
- **隐藏机制：** 在内部作用域可以定义与外部作用域同名的变量，这会隐藏外部变量，但为了代码可读性一般应避免。

### 🛠️ 代码示例

C++

```cpp
#include <iostream>

int main() {
    int outer_var = 100;

    { // 开启一个新的局部作用域
        int inner_var = 42;
        std::cout << "作用域内部: " << inner_var << std::endl; // 成功运行
        std::cout << "外部变量依然可见: " << outer_var << std::endl; // 成功运行
        
        int outer_var = 5; // 隐藏了外部同名变量
        std::cout << "同名隐藏后: " << outer_var << std::endl; // 输出 5
    } // 离开作用域，inner_var 在这里被销毁

    // std::cout << inner_var; // ❌ 编译报错：inner_var 在此作用域未定义
    std::cout << "作用域外部: " << outer_var << std::endl; // 输出 100

    return 0;
}
```

---

## 3. 控制结构与强类型强化的基础 (Control Structures)

讲师强调，C++ 的 `if`, `while`, `for` 基本逻辑与其他语言类似，但现代 C++ 提供了很多语法糖和防错机制来提升性能和安全性。

### 3.1 强类型替代传统 C 语言写法：`enum class` 26:20 Opens in a new window

- **传统 C 风格缺点：** 常使用 `int` 或宏定义（`#define RED 1`）表示状态，缺乏类型保护，且必须写注释说明各个数字代表什么 24:42 Opens in a new window 。
- **现代 C++ 推荐：** 使用强类型枚举 `enum class`。不仅消除了魔法数字和冗余注释，还防止了将非法数字（如 `4`）赋值给颜色变量。

### 🛠️ 代码示例

C++

```cpp
#include <iostream>

// 现代 C++ 强类型枚举 (Scoped Enumeration)
enum class RGB {
    Red,
    Green,
    Blue
};

int main() {
    RGB color = RGB::Red; // 初始化，不可随意赋整数值

    // 搭配 switch 语句使用
    switch (color) {
        case RGB::Red:
            std::cout << "It's Red" << std::endl;
            break; // ⚠️ 千万不要忘记写 break，否则会引发 fall-through 逻辑错误
        case RGB::Green:
            std::cout << "It's Green" << std::endl;
            break;
        case RGB::Blue:
            std::cout << "It's Blue" << std::endl;
            break;
    }
    return 0;
}
```

### 3.2 现代化循环结构 (Loops) 30:32 Opens in a new window

- **Range-based for loop (C++11 基于范围的循环):** 如果只需要遍历容器中的元素，不需要声明冗余的辅助索引变量 `i`（类似于 Python 的 `for x in list`） 31:26 Opens in a new window 。
- **Structured Binding (C++17 结构化绑定):** 允许以极其优雅、类似于 Python 的方式同时迭代 Map/字典的键（Key）和值（Value），且运行性能比 Python 快近 15 倍 33:08 Opens in a new window 。

### 🛠️ 代码示例

C++

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>

int main() {
    // 1. C++11 基于范围的循环 (Range-based for)
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    for (const auto& name : names) { // 读取时建议加上 const 引用以避免拷贝开销
        std::cout << "Name: " << name << std::endl;
    }

    // 2. C++17 结构化绑定遍历 Map 字典 (Structured Binding)
    std::map<std::string, int> age_dict = {{"Alice", 27}, {"Bob", 30}};
    
    // 直接解包获取 key 和 value
    for (const auto& [name, age] : age_dict) {
        std::cout << "Key: " << name << ", Value: " << age << std::endl;
    }

    return 0;
}
```

---

## 4. 变量、常量与引用基础 (Variables, Const & References)

### 📌 核心知识点

1. **自动类型推导 (`auto`):** C++ 是强类型语言，但通过 `auto` 关键字可以让编译器通过右侧的初始值自动推断出正确的具体类型，减少代码冗余 36:58 Opens in a new window 。
2. **禁止对浮点数直接使用 `==`:** 由于计算机底层对浮点数（`float`/`double`）的二进制存储方式存在精度误差，在 C++ 中**绝对不要**用 `==` 直接判断两个浮点数是否相等 38:26 Opens in a new window 。
3. **Const 原则 (Const-correctness):** 核心准则——**“除非该变量必须被修改，否则请将其声明为 `const`”**。这可以在编译阶段预防不小心的修改错误 43:47 Opens in a new window 。
4. **引用 (`&`):** 作为已存在变量的“别名”。操作引用就是直接操作原变量，常用于函数传参以**规避昂贵的数据拷贝开销**，极大提升程序效率 44:06 Opens in a new window 。

### 🛠️ 代码示例

C++

```cpp
#include <iostream>
#include <cmath>

int main() {
    // 1. 自动类型推导
    auto small_int = 42;      // 推导为 int
    auto precise_num = 0.01f; // 带有 f 尾缀，推导为 float

    // 2. ❌ 浮点数比对的错误示范与正确写法
    double a = 0.1 + 0.2;
    double b = 0.3;
    if (a == b) { /* ⚠️ 大概率为 false，不要这样做！ */ }

    // 正确写法：判断差值的绝对值是否小于一个极小量 (epsilon)
    if (std::abs(a - b) < 1e-9) {
        std::cout << "a 和 b 足够接近，相等！" << std::endl;
    }

    // 3. Const 原则与引用
    int original_score = 90;
    int& ref_to_score = original_score; // ref_to_score 是 original_score 的别名

    ref_to_score = 95; // 修改引用会直接改变原变量
    std::cout << "原变量变为: " << original_score << std::endl; // 输出 95

    const int kMaxPoints = 100; // 谷歌风格常数变量：k开头，CamelCase
    // kMaxPoints = 110; // ❌ 编译报错：无法修改 const 变量

    return 0;
}
```

---

## 5. 经典实战对比：C 风格 vs C++ 字符串流处理 (StringStream)

### 📌 场景描述

假设输入一个文件名为 `"00205.txt"` 的数据集字符串，我们的目标是：

1. 分离出前面的数字前缀，并将其直接转化为真正的数字（`int` 类型）以便后续进行数学计算。
2. 分离出后面的扩展名 `"txt"` 字符串。
- **C 语言写法缺点：** 必须使用 `strtok` 等函数按字符或模式遍历、切割指针，然后再调用 `atoi` 等转换函数。代码艰涩、难懂且容易引发安全漏洞 47:21 Opens in a new window 。
- **现代 C++ 写法优点：** 使用标准库自带的 `std::stringstream`。它会将字符串看作一个标准输入输出流，配合右移操作符 `>>`，可以自动、优雅地完成**格式化切分与类型的自动转换** 48:03 Opens in a new window 。

### 🛠️ C++ 核心代码示例

C++

```cpp
#include <iostream>
#include <string>
#include <sstream> // 必须引入此头文件以使用 stringstream

int main() {
    std::string file_name = "00205.txt";

    // 创建一个字符串输入流并将目标字符串塞入其中
    std::stringstream ss(file_name);

    int number;
    std::string extension;

    // 🌟 核心魔法：从左到右解析流
    // 1. 流会自动发现前面是数字，自动过滤前导0，转换并填入 int 变量中
    // 2. 剩余的 ".txt" 部分作为普通的字符串填入 extension 中
    ss >> number >> extension;

    // 最终输出：
    std::cout << "解析出的纯数字 (int): " << number << std::endl;       // 输出: 205
    std::cout << "解析出的扩展名 (string): " << extension << std::endl; // 输出: .txt

    // 证明成功转换为 int：现在可以直接做数学运算
    std::cout << "数字加一运算结果: " << (number + 1) << std::endl;    // 输出: 206

    return 0;
}
```

---

### Notion 记忆补充卡片（可直接复制）

> 🧠 **Lecture 2 核心复习要点：**
> 
> - **C++ 是强类型语言：** 每一个对象、变量在编译期必须确定类型，使用 `auto` 是让编译器替你推导，并不是弱类型。
> - **如何编写具备现代感的可维护代码：**
>     1. 丢掉 C 风格的裸数或 `#define` 常量，改用 `enum class` 进行状态分类。
>     2. 抛弃传统的复杂 `for(int i...)`，优先在容器遍历中采用基于范围的循环 `for(auto& x : container)` 和 C++17 结构化绑定。
>     3. 处理字符串中多类型数据复合解析时，优先选用 `std::stringstream`。