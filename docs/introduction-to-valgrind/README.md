# Introduction to Valgrind

Valgrind 是一款分析程序运行的工具
[Valgrind 介绍](https://valgrind.org/)

## 安装

可以在Ubuntu上使用包管理工具安装Valgrind

```console
sudo apt-get install valgrind
```

可以在Mac上用brew安装[valgrind-macos](https://github.com/LouisBrunner/valgrind-macos)，但是尚不支持M1 Mac

```console
brew tap LouisBrunner/valgrind
brew install --HEAD LouisBrunner/valgrind/valgrind
```

Valgrind 不支持Windows。作为替代，可以使用Deleaker工具（Visual Studio的拓展）

## 例子

我们构建如下的应用程序来模拟一次内存泄漏。将以下代码保存在`valgrind_ex.c`中

```c
/** @file valgrind_ex.c **/
#include <stdio.h>
#include <stdlib.h>

void func() {
    char * a_piece_of_memory = (char *)malloc(10);
}

int main()
{
    func();
    return 0;
}
```

## 使用 Valgrind

使用gcc编译`valgrind_ex.c`

```console
gcc valgrind_ex.c -o valgrind_ex
```

我们不直接运行`valgrind_ex`程序，而是用Valgrind运行

```console
valgrind ./valgrind_ex
```

运行结果如下

![Valgrind](./uploads/2021-11-29-19-59-40.png)

可以看到Valgrind正确的给出了内存泄漏的检测结果
