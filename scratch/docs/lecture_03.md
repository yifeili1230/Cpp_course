## 1. 字符串处理：C Style vs. C++ Style

在 Modern C++ 中，原则上**禁止使用 C 风格字符串**（如 `char*` 或 `const char*` 配合 `strcpy`），因为它们极易引发内存越界和安全隐患。

### ❌ C Style 错误示范（容易导致 Buffer Overflow）

在开启编译器优化（如 `-O3`）时，以下代码极易导致程序崩溃或行为怪异：

C++

```cpp
#include <cstring>
#include <iostream>

int main() {
    const char* source = "This is a very long string";
    char destination[10]; // 空间不足
    
    // 危险：不检查边界，直接引发溢出
    std::strcpy(destination, source); 
    std::cout << destination << std::endl;
    return 0;
}
```

### Modern C++ 推荐做法

使用 `std::string`，安全、可读，且赋值时会自动处理内存（如果作业里出现纯 C 风格字符串，讲师会直接算错）：

C++

```cpp
#include <string>
#include <iostream>

int main() {
    std::string source = "This is a safe C++ string";
    std::string destination;
    
    destination = source; // 安全复制，自动扩容
    std::cout << destination << std::endl;
    return 0;
}
```

---

## 2. C++ 函数核心语法（Function Anatomy）

### 自动返回值推导 (C++14 Auto Return Type)

当返回值类型极其复杂时（例如迭代器或嵌套容器），可以使用 `auto` 让编译器自动推导。

C++

```cpp
#include <iostream>
#include <map>
#include <string>

// C++14 支持对函数返回值使用 auto
auto get_dictionary() {
    std::map<std::string, int> dict = {{"apple", 1}, {"banana", 2}};
    return dict; // 编译器自动推导返回类型为 std::map<std::string, int>
}

int main() {
    auto my_dict = get_dictionary();
    std::cout << my_dict["apple"] << std::endl;
    return 0;
}
```

### 结构化绑定多返回值 (C++17 Structured Binding)

C++ 原生函数只能返回一个对象。如果需要返回多个值，在 C++17 中可以利用 `std::tuple` 和结构化绑定，写出类似 Python 的优雅代码。

C++

```cpp
#include <iostream>
#include <tuple>
#include <string>

// 使用 std::tuple 返回多个不同类型的值
std::tuple<std::string, double> get_student_info() {
    return {"Alice", 4.0};
}

int main() {
    // C++17 结构化绑定 (Structured Binding)
    auto [name, gpa] = get_student_info();
    
    std::cout << "Name: " << name << ", GPA: " << gpa << std::endl;
    return 0;
}
```

---

## 3. 函数核心陷阱与优化原则

### ⚠️ 致命陷阱：绝对不要返回局部变量的引用

局部变量在函数生命周期结束（出作用域）时即被销毁。返回其引用会导致“悬空引用”（Dangling Reference），访问未知内存（垃圾值）。

C++

```cpp
#include <iostream>

// ❌ 错误：返回了局部变量 result 的引用
int& multiply_by_ten(int number) {
    int result = number * 10;
    return result; // 警告！result 马上就要被销毁了
}

int main() {
    int& bad_ref = multiply_by_ten(5);
    // 此时 bad_ref 指向的代码块已被释放，开启优化后输出的大多是垃圾随机数
    std::cout << bad_ref << std::endl; 
    return 0;
}
```

> **课程警示：** 有时候在函数里加一句话打印（比如 `cout`），这个错误程序突然又能跑出正确结果了。讲师强调：**“程序凑巧能跑”不等于“代码正确”**。绝对不要因为加上某行调试代码能跑，就留下错误的内存逻辑。
> 

### 静态局部变量 (Static Local Variables)

使用 `static` 修饰的局部变量只会在第一次调用时初始化，其生命周期贯穿整个程序。但**不建议滥用**，因为它会引入隐式的全局状态，并可能引发“静态初始化顺序冲突”（Static Initialization Order Fiasco）。

C++

```cpp
#include <iostream>

void count_calls() {
    static int counter = 0; // 只在第一次调用时初始化
    counter++;
    std::cout << "Function called " << counter << " times" << std::endl;
}

int main() {
    count_calls(); // 输出 1
    count_calls(); // 输出 2
    return 0;
}
```

---

## 4. 参数传递最佳实践（Pass by Const Reference）

在 C++ 中，大对象（如大型字符串、`std::vector`）如果直接值传递，会发生深拷贝，极其消耗性能。**现代 C++ 的金科玉律是：对于不改变内容的入参，一律使用 `const T&`。**

C++

```cpp
#include <iostream>
#include <string>

// ❌ 差劲做法：值传递（Pass by Value），每次调用都会完整复制一遍大字符串
void print_image_path_bad(std::string path) {
    std::cout << path << std::endl;
}

//  最佳实践：常量引用传递（Pass by Const Reference）
// 既避免了数据拷贝（速度提升数倍），又防止了函数内部意外修改原数据
void print_image_path_good(const std::string& path) {
    // path = "new_path"; // 如果取消注释这行，编译器会直接报错，保护数据安全
    std::cout << path << std::endl;
}

int main() {
    std::string huge_path = "usr/local/share/images/dataset/image_001.png";
    print_image_path_good(huge_path);
    return 0;
}
```

---

## 5. 内联函数 (Inline Functions) 与编译期优化

函数调用会有开销（压栈、跳转、出栈）。对于极其短小且高频调用的函数，可以使用 `inline` 关键字。现代编译器在开启优化后，甚至会自动将内联函数直接展开为具体的计算结果（即在编译期消除调用开销）。

C++

```cpp
#include <iostream>

// 使用 inline 建议编译器进行内联展开
inline int square(int x) {
    return x * x;
}

int main() {
    // 开启优化（如 -O2）后，编译器可能会直接把这行代码替换为：int result = 25;
    int result = square(5); 
    std::cout << result << std::endl;
    return 0;
}
```

---

## 6. 函数重载 (Function Overloading)

C++ 支持函数重载：允许函数**同名**，只要它们的**参数列表不同**即可。编译器会在编译时根据传入的参数类型自动匹配正确的函数。

C++

```cpp
#include <iostream>
#include <string>

// 版本 1：接收 int
void print_type(int value) {
    std::cout << "This is an integer: " << value << std::endl;
}

// 版本 2：接收 double
void print_type(double value) {
    std::cout << "This is a double: " << value << std::endl;
}

// 版本 3：接收 std::string
void print_type(const std::string& value) {
    std::cout << "This is a string: " << value << std::endl;
}

int main() {
    print_type(10);             // 自动调用版本 1
    print_type(3.14);           // 自动调用版本 2
    print_type(std::string("hi")); // 自动调用版本 3
    return 0;
}
```

---

## 7. 命名空间（Namespaces）与 `using` 的禁忌

命名空间用于划分逻辑模块，避免全局命名冲突。

### ❌ 严厉警告：绝对不要在全局或头文件中写 `using namespace std;`

这会将整个标准库引入全局作用域，极易与你自定义的函数引发命名冲突（在 `.h` 头文件里写这个更是灾难）。

C++

```cpp
#include <iostream>
#include <cmath>

using namespace std; // ❌ 极其危险的坏习惯

// 自定义一个 pow 函数
double pow(double base, int exp) {
    return 100.0; 
}

int main() {
    // 报错：编译失败！编译器不知道该调用你写的 pow 还是 <cmath> 里的 std::pow
    // std::cout << pow(2.0, 3) << std::endl; 
    return 0;
}
```

### 正确做法：显式指定或局部引入

C++

```cpp
#include <iostream>
#include <cmath>

// 自定义 pow 函数
double pow(double base, int exp) {
    return 100.0;
}

int main() {
    // 局部引入具体的成员，安全且省位置
    using std::cout;
    using std::endl;
    
    cout << pow(2.0, 3) << endl;      // 明确调用自定义的 pow (输出 100)
    cout << std::pow(2.0, 3) << endl; // 明确调用标准库的 pow (输出 8)
    
    return 0;
}
```

### 匿名命名空间 (Unnamed Namespace)

如果你希望某个常量或函数**只在当前的 `.cpp` 文件内可见**（相当于老版本 C 语言里的全局 `static` 限制），现代 C++ 推荐将其放入匿名命名空间。

C++

```cpp
#include <iostream>

namespace {
    // 该常量和函数仅限制在当前文件内可见，其他编译单元（.cpp）无法链接到它们
    const double PI = 3.14159265;
    void local_helper() {
        std::cout << "Helper reference." << std::endl;
    }
}

int main() {
    std::cout << PI << std::endl; // 直接使用，无需前缀
    local_helper();
    return 0;
}
```

---

课程视频参考：Modern C++: C++ Functions (Lecture 3, I. Vizzo, 2020)