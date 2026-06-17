#ifndef HOMEWORK_4_H_
#define HOMEWORK_4_H_

// 📢 1. 把你之前写的 20 行核心容器头文件拉进来
#include "named_vector.hpp"

// =================================================================
// 📢 2. 占位符：为了让 test_ipb_algorithm.cpp 也能通过编译，
// 咱们先在这里把助教点名要的算法函数名给“空壳声明”出来。
// 这样即使现在算法没写完，编译也不会报错，能让我们先把 A.1 的容器测试全绿跑通！
// =================================================================

namespace ipb {

// 占位：计算累加
template <typename T>
auto accumulate(const T& container) { return 10; }

// 占位：计数
template <typename T, typename U>
int count(const T& container, const U& val) { return 1; }

// 占位：判断全偶
template <typename T>
bool all_even(const T& container) { return true; }

// 占位：截断
template <typename T, typename U>
void clamp(T& container, U min, U max) {}

// 占位：填充
template <typename T, typename U>
void fill(T& container, const U& val) {}

// 占位：查找
template <typename T, typename U>
bool find(const T& container, const U& val) { return true; }

// 占位：打印
template <typename T>
void print(const T& container) {}

// 占位：大写转换
template <typename T>
void toupper(T& container) {}

// 占位：排序
template <typename T>
void sort(T& container) {}

// 占位：旋转
template <typename T>
void rotate(T& container, int pos) {}

// 占位：反转
template <typename T>
void reverse(T& container) {}

} // namespace ipb

#endif // HOMEWORK_4_H_