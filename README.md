# Lib

## Needs

1. gcc-riscv64-linux-gnu

```shell
sudo apt install gcc-riscv64-linux-gnu
```

## Build

1. 生成汇编代码

```shell
make asm
```

1. 修改汇编代码

删除如下的 GNU 所生成的特殊节

```asm
.ident "GCC: (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0"
.section .note.GNU-stack,"",@progbits
```

1. 生成可重定位文件

```shell
make lib
```

## Usage

将 object 目录下的所有 .o 文件拷贝到链接器目录下的 lib 目录。

考虑到评测环境部署的快捷性，以及对学生工作环境环境变量的保护，链接器对库的搜索采用相对路径，因此将 lib 目录放置在项目根目录即可。

