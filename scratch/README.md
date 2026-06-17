# C++ Build Playground

这是一个按“每一讲一个文件夹”组织的 C++ 练习仓库。真正的代码例子都放在 `lectures/lecture_xx/` 下面，每一讲都可以单独配置和编译。

## 目录结构

```text
.
├── CMakeLists.txt
├── README.md
├── docs/
│   ├── lecture_01_build_system.md
│   └── lecture_02.md
└── lectures/
    ├── lecture_01/
    │   ├── CMakeLists.txt
    │   ├── README.md
    │   ├── broken_examples/
    │   ├── examples/
    │   ├── include/
    │   ├── scripts/
    │   └── src/
    └── lecture_02/
        ├── CMakeLists.txt
        ├── README.md
        ├── examples/
        ├── include/
        └── src/
    └── lecture_03/
        ├── CMakeLists.txt
        ├── README.md
        └── src/
    └── lecture_04/
        ├── CMakeLists.txt
        ├── README.md
        └── src/
```

## 使用方式

```bash
cmake -S lectures/lecture_01 -B lectures/lecture_01/build
cmake --build lectures/lecture_01/build
```

各讲的主程序会生成在各自的 `build/` 下面，常用目标包括：

```bash
./lectures/lecture_01/build/lecture01_notes
./lectures/lecture_01/build/namespace_demo
./lectures/lecture_02/build/lecture02_notes
./lectures/lecture_03/build/lecture03_notes
./lectures/lecture_04/build/lecture04_notes
```

## 新增一讲的约定

以后你放入新的笔记时，直接新建一个同名目录，例如 `lectures/lecture_03/`，里面放：

```text
lecture_03/
├── CMakeLists.txt
├── README.md
├── include/
├── src/
└── examples/
```

然后把对应的代码例子收进这个文件夹，根目录 CMake 会自动扫描 `lectures/*/CMakeLists.txt` 并加入构建。

如果你更喜欢完全隔离，也可以直接在那一讲自己的目录里配置：

```bash
cmake -S lectures/lecture_02 -B lectures/lecture_02/build
cmake --build lectures/lecture_02/build
```
