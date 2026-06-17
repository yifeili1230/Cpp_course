## 1. C++ 容器 (Containers)

C++ 的世界分为**静态**（编译时决定）和**动态**（运行时处理）。STL 容器也以此划分。

### 1.1 `std::array` (静态数组) 02:32 Opens in a new window

- **特点**：固定大小，大小在**编译时**必须确定，不能在运行时改变。比 C 风格数组更安全、更易读。
- **代码示例**：

C++

```cpp
#include <iostream>
#include <array>

int main() {
    // 必须指定类型和编译时常量大小
    std::array<int, 3> data = {10, 100, 1000};
    
    // 使用成员函数
    std::cout << "Is empty: " << std::boolalpha << data.empty() << std::endl; // [00:03:56]
    std::cout << "Size: " << data.size() << std::endl;
    
    // 下标索引从 0 开始
    std::cout << "First element: " << data[0] << std::endl; 
    return 0;
}
```

### 1.2 `std::vector` (动态数组) 05:29 Opens in a new window

- **特点**：动态大小，不需要在编译时知道容量。是 C++ 中**最推荐作为默认使用**的容器 07:34 Opens in a new window 。
- **核心操作**：
    - `emplace_back()`：在尾部直接构造元素，**C++11 起推荐优先于 `push_back()` 使用** 07:11 Opens in a new window 。
    - `clear()`：清空所有元素。
- **性能优化（`reserve`）** 08:16 Opens in a new window ：由于动态扩容会导致重新分配内存并复制元素（非常耗时），若已知大致数据量，应提前调用 `reserve(n)` 预留空间。
- **代码示例**：

C++

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> names;
    
    // 性能优化：预留 100 个元素的内存空间 [00:09:38]
    names.reserve(100); 
    
    // 优先使用 emplace_back 插入元素
    names.emplace_back("Nacho");
    names.emplace_back("Roberto");
    
    std::cout << "Size: " << names.size() << " | Capacity: " << names.capacity() << std::endl;
    return 0;
}
```

### 1.3 为什么不要使用 C 风格数组？ 13:43 Opens in a new window

STL 容器与 C 数组运行速度相同，但更安全且可读性极高：

- **获取大小**：C 数组需 `sizeof(data)/sizeof(data[0])` 14:35 Opens in a new window ，STL 只需 `data.size()` 15:20 Opens in a new window 。
- **检查空状态**：STL 提供显式的 `data.empty()` 16:06 Opens in a new window 。
- **安全访问尾元素**：C 数组越界访问会引发运行时灾难 16:32 Opens in a new window ，STL 可通过 `data.back()` 明确表达意图 17:26 Opens in a new window 。
- **清空数组**：C 数组需调用外部 `memset`（对浮点数不安全）17:54 Opens in a new window ，STL 直接 `data.clear()` 18:37 Opens in a new window 。

---

## 2. 关联容器 (Associative Containers)

用于通过 **Key-Value（键值对）** 关联数据的容器，类似于 Python 中的字典（Dictionary）22:15 Opens in a new window 。

### 2.1 `std::map` (有序映射) 20:50 Opens in a new window

- **特点**：Key 必须是**唯一的**且**可排序的**（默认要求定义了 `<` 运算符）21:12 Opens in a new window 。每插入一个新元素，内部会自动进行排序 21:20 Opens in a new window 。
- **代码示例**：

C++

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    // 类型别名提升可读性 [00:24:31]
    using StudentList = std::map<int, std::string>; 
    StudentList cpp_students;
    
    // 插入数据
    cpp_students.emplace(10, "Nacho");
    cpp_students.emplace(2, "Marcelo");
    
    // 遍历：C++17 结构化绑定 (Structured Binding) [00:29:28]
    for (const auto& [id, name] : cpp_students) {
        std::cout << "ID: " << id << " -> Name: " << name << std::endl;
        // 输出会自动按 ID 升序排序：2 优先于 10
    }
    
    // C++20 特性：检查是否包含某个 Key [00:23:55]
    // if (cpp_students.contains(10)) { ... }
    
    return 0;
}
```

### 2.2 `std::unordered_map` (无序映射) 25:53 Opens in a new window

- **特点**：数据**不会排序**，内部基于哈希表实现。Key 类型必须是**可哈希的 (Hashable)** 26:18 Opens in a new window 。
- **优势**：由于不需要在插入时进行内部排序调整，**性能比 `std::map` 更加高效速度更快** 26:34 Opens in a new window 。标准库内置基本类型（`int`, `float`, `string`等）默认支持哈希 28:01 Opens in a new window 。
- **代码示例**：

C++

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<int, std::string> students;
    
    students.emplace(10, "Nacho");
    students.emplace(2, "Marcelo");
    
    // 输出顺序为哈希存储的随机无序状态 [00:29:50]
    for (const auto& [id, name] : students) {
        std::cout << "ID: " << id << " -> Name: " << name << std::endl;
    }
    return 0;
}
```

---

## 3. 迭代器 (Iterators) 34:16 Opens in a new window

- **定义**：迭代器是**连接算法与数据的胶水** 34:27 Opens in a new window 。它让算法无需关心底层容器的具体实现（无论是 vector、array 还是 list），实现泛型编程 34:56 Opens in a new window 。
- **基本操作**：
    - 可以通过 `it` 解引用访问数据 36:20 Opens in a new window 。
    - 通过 `++it` 或 `-it` 向前/后移动 36:35 Opens in a new window 。
- **常用范围迭代器** 37:05 Opens in a new window ：
    - `begin()` / `end()`：指向容器首元素 / 尾元素后一个位置。
    - `cbegin()` / `cend()`：常数迭代器（只读，不可修改元素内容）。
    - `rbegin()` / `rend()`：反向迭代器（用于逆序遍历）。

---

## 4. STL 算法库 (Algorithms) 42:27 Opens in a new window

STL 提供了超过 80 个标准算法（需引入 `<algorithm>`），它们通过**一对迭代器**来指定操作的数据范围 42:51 Opens in a new window 。**原则：不要重复发明轮子** 43:05 Opens in a new window 。

### 4.1 基础与查找算法

- `std::sort` (排序) 44:55 Opens in a new window ：

C++

```cpp
#include <vector>
#include <algorithm>
// 基础升序排序
std::sort(vec.begin(), vec.end()); 
// 逆序排序（利用反向迭代器）[00:45:58]
std::sort(vec.rbegin(), vec.rend()); 
// 对局部子集进行排序 (例如仅前10个元素) [01:00:40]
std::sort(vec.begin(), vec.begin() + 10);
```

- `std::find` (查找) 46:11 Opens in a new window ：

C++

```cpp
auto it = std::find(vec.begin(), vec.end(), 3);
if (it != vec.end()) { /* 找到了 */ } // [00:46:43]
```

- `std::fill` (填充) 47:03 Opens in a new window ：将指定范围内所有元素设为某个值。

C++

```cpp
std::fill(vec.begin(), vec.end(), -1); // 快速将整个vector填充为-1
```

- `std::count` (计数) 47:25 Opens in a new window ：

C++

```cpp
int num = std::count(vec.begin(), vec.end(), 3); // 计算数字3出现的次数
```

### 4.2 高级断言与修改算法

- `std::count_if` (条件计数) 48:32 Opens in a new window ：配合断言函数使用。

C++

```cpp
// 计数所有能被3整除的数 [00:48:41]
int count = std::count_if(vec.begin(), vec.end(), [](int i){ return i % 3 == 0; });
```

- `std::for_each` (逐个操作) 50:23 Opens in a new window ：替代传统的原生 `for` 循环。

C++

```cpp
std::for_each(vec.begin(), vec.end(), [](int i) { std::cout << i << " "; });
```

- `std::all_of` (全满断言) 51:49 Opens in a new window ：检查是否范围内**所有**元素都满足条件。

C++

```cpp
bool all_even = std::all_of(vec.begin(), vec.end(), [](int i){ return i % 2 == 0; });
```

- `std::rotate` (旋转平移) 52:36 Opens in a new window ：围绕某个迭代器位置对数据进行循环左移/右移。

C++

```cpp
// 将第二个元素之后的内容旋转到前面
std::rotate(vec.begin(), vec.begin() + 2, vec.end());
```

- `std::transform` (转换) 53:38 Opens in a new window ：对数据做映射加工（如字符串转大写）。

C++

```cpp
std::string s = "hello";
std::transform(s.begin(), s.end(), s.begin(), ::toupper); // [00:54:19]
```

### 4.3 数值与工具算法

- `std::accumulate` (累加/求积) 54:26 Opens in a new window ：（需引入 `<numeric>`）

C++

```cpp
#include <numeric>
int sum = std::accumulate(vec.begin(), vec.end(), 0); // 从0开始累加求和 [00:54:50]
int prod = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>()); // 求阶乘/连乘 [00:55:09]
```

- `std::clamp` (区间限定) 55:53 Opens in a new window ：**C++17 引入**。将数值强行限定在 `[min, max]` 区间内，避免手写复杂的 `if-else`。

C++

```cpp
std::cout << std::clamp(0.5, 0.0, 1.0);  // 输出 0.5 (在范围内)
std::cout << std::clamp(2.1, 0.0, 1.0);  // 输出 1.0 (超过最大值，截断) [00:56:42]
std::cout << std::clamp(-2.1, 0.0, 1.0); // 输出 0.0 (低于最小值，截断) [00:56:49]
```

- `std::sample` (随机采样) 56:57 Opens in a new window ：**C++17 引入**。从容器中随机抽取指定数量的样本。

C++

```cpp
#include <random>
std::string in = "C++++School", out;
std::random_device rd;
std::mt19937 gen(rd());
// 从中随机抽取5个字符放入out
std::sample(in.begin(), in.end(), std::back_inserter(out), 5, ge
```