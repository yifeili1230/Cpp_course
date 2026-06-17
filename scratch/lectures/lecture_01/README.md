# Lecture 1

这讲对应 `docs/lecture_01_build_system.md`。

本目录里放的是和第一节课配套的代码例子，包含：

- 编译流程演示
- 声明 / 定义分离
- 静态库链接
- 命名空间和同名符号示例
- 一组 C++17 特性演示

先看这个文件最省脑子：

- `src/lecture01_notes.cpp`: 第一讲的单文件复习版，按笔记顺序一路往下打印

常用构建：

```bash
cmake -S lectures/lecture_01 -B lectures/lecture_01/build
cmake --build lectures/lecture_01/build
```

手动四阶段构建：

```bash
bash lectures/lecture_01/scripts/manual_build.sh
```
