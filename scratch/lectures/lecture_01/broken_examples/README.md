# Broken Examples

这些文件故意不加入主构建。

`multiple_definition_a.cpp` 和 `multiple_definition_b.cpp` 同时定义了全局函数
`MakeItSunny()`。如果把它们一起链接进同一个可执行文件，链接器会报
`multiple definition`，这正好对应第一节课里“同名全局符号冲突”的例子。
