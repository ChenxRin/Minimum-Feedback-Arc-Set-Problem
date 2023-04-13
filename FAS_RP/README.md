# FAS

> 部分基于图计算系统 Ligra 实现

## Running

以执行目录为项目根目录为例。执行根目录下的脚本 `build.sh`：

```shell
./build.sh
```

之后会编译可执行程序，程序被编译到 `build` 目录下。

部分输入数据在 `input` 目录。每个程序使用命令模式编译，读取对应文件只需将文件名作为文件参数，如运行 `SCC`：

```shell
./build/SCC ./inputs/FAS_testcase1
```

