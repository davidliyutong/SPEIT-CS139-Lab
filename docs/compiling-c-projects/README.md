# Compiling C Projects

## 编译之道

编译，是从源代码生成可执行文件的过程。从源代码构建一个C程序有三步：

1. 使用编辑器编辑代码
2. 使用编译器编译代码（然后链接）
3. 运行编译后的可执行文件

### 单文件编译

在C程序设计这门课程里，我们会使用CodeBlocks编译课程作业。也有同学会使用`gcc`命令在终端里编译程序。以一个简单的`helloworld.c`为例子：

```C
/** @file helloworld.c
 ** @brief The hello world example
 */
#include <stdio.h>
int main(int argc, const char * argv[]) {
    printf("Hello world !\n");
    return 0;
}
```

我们一般会使用这样的命令进行编译：

```shell
$ gcc -Wall -o helloworld helloworld.c
```

这条命令的含义是：调用`gcc` 从源代码`helloworld.c`生成名为`helloworld`的可执行文件（由`-o`参数决定），开启所有警告（`-Wall`）

然后，我们会用下面的命令来查看程序运行的结果：

```shell
$ ./helloworld
Hello world !
```

为了方便起见，我们可以用`&&`符号把两个语句合成一个

```shell
$ gcc -Wall -o helloworld helloworld.c && ./helloworld
```

为了检查我们代码运行的结果，我们需要在修改代码后手动输入这条命令重新编译程序。一个节约时间的小技巧是在终端中按下方向键上<kbd>↑</kbd>来调取最后一条执行的命令来介于输入的时间。
但这不是我们想要的最好的解决方法，因为：

- 需要在代码编辑器和终端之间来回切换
- 生成代码后需要额外的操作执行

### 多文件编译

我们考虑一个更加复杂的例子（依然是helloworld）。这个例子包含了三个文件：

```text
./
├── helloworld.c
├── myfunction.c
└── myfunction.h
```

他们的内容如下：

```c
/** @file helloworld.c
 ** @brief The hello world example
 */
#include "myfunction.h"
int main(int argc, const char * argv[]) {
    my_function();
    return 0;
}
```

```c
/** @file myfunction.h
 ** @brief The file contains function declaration
 */
#include <stdio.h>

/**@remark Function declaration end with ';'*/
void my_function();
```

```c
/** @file myfunction.c
 ** @brief The file contains function definition
 */
#include "myfunction.h"

void my_function(){
    printf("Hello world !\n");
}
```

虽然程序的任务没有发生改变，但是`printf`这个语句被独立出来，并拆分成**声明（Declaration）**和**定义（Definition）**两部分。
我们之前使用的编译命令在这样的项目终会出错：

```text
$ gcc -Wall -o helloworld helloworld.c
/usr/bin/ld: /tmp/ccRePKxG.o: in function `main':
helloworld.c:(.text+0x19): undefined reference to `my_function'
collect2: error: ld returned 1 exit status
```

这是因为，当编译器读取`helloworld.c`文件时，他会根据`#include "my_function.h"`这行代码将`my_function.h`中的内容添加进来。其中，`void my_function()`声明了一个名为`my_function`的函数，这个函数不接受任何参数，也不返回值。但是仅凭这些编译器并不能推断出函数是做什么的

因此，我们需要把`my_function.c`这个定义了函数行为的文件纳入进编译过程中。

```shell
$ gcc -Wall -o helloworld helloworld.c myfunction.c
$ ./helloworld
Hello world !
```

注意：

- `my_function.c` 需要使用双引号包含`my_function.h`，代表在当前目录而非系统目录下搜索函数头文件
- `helloworld.c`也需要包含`my_function.h`，从而可以使用`my_function.h`包含的`stdio`库

### 使用宏保护头文件

举一个简单的例子。我们有一个公用的结构体`struct point`会被所有的文件用到。这个**函数被定义在了头文件**`common.h`里。整个目录结构如下：

```text
./
├── common.h
├── helloworld.c
├── myfunction.c
└── myfunction.h
```

```c
/** @file common.h
 ** @brief The file contains some data structure
 */
typedef struct point {
     double x;
     double y;
 } point;
```  

```c
/** @file helloworld.c
 ** @brief The hello world example
 */
#include "myfunction.h"
#include "common.h"

int main(int argc, const char * argv[]) {
    my_function();
    return 0;
}
```

```c
/** @file myfunction.h
 ** @brief The file contains function declaration
 */
#include <stdio.h>
#include "common.h"

/**@remark Function declaration end with ';'*/
void my_function();
```

```c
/** @file myfunction.c
 ** @brief The file contains function definition
 */
#include "myfunction.h"

void my_function(){
    printf("Hello world !\n");
}
```

我们尝试用同样的命令编译这个项目，编译器会给出一个错误

```shell
In file included from myfunction.h:1,
                 from helloworld.c:2:
common.h:1:16: error: redefinition of ‘struct point’
    1 | typedef struct point {
      |                ^~~~~
In file included from helloworld.c:1:
common.h:1:16: note: originally defined here
    1 | typedef struct point {
      |                ^~~~~
In file included from myfunction.h:1,
                 from helloworld.c:2:
common.h:4:3: error: conflicting types for ‘point’
    4 | } point;
      |   ^~~~~
In file included from helloworld.c:1:
common.h:4:3: note: previous declaration of ‘point’ was here
    4 | } point;
      |   ^~~~~
```

这是因为`common.h`中定义的`point`被包含了多次，产生了重复的符号。为了避免此类错误，我们可以用一个宏来保护它：

```c
/** @file common.h
 ** @brief The file contains some data structure
 */
#ifndef _PROTECT_COMMON_H
#define _PROTECT_COMMON_H

typedef struct point {
     double x;
     double y;
 } point;
#endif
```

在编译期间，编译器首先检测 #ifndef。第一次处理`common.h`文件时，测试会成功，因为 `_PROTECT_COMMON_H` 还未定义。紧接着，下一条语句定义了 `_PROTECT_COMMON_H`。如果我们编译的文件恰好又一次包含了该头文件。`#ifndef` 指示会发现 `_PROTECT_COMMON_H` 已经定义，并且忽略该头文件的剩余部分。

## 初识Makefile

每次测试程序都需要在终端中键入长命令是一个麻烦的事，尤其是当项目变得庞大起来。Make工具因此被发明出来。Make工具的作用是"自动化"编译。编译的所有命令都被写入一个名为Makefile的文件中（没有后缀名）Makefile一旦写好，只需要一个Make命令就能够编译整个工程。向别人分享代码后，对方只需要执行一个命令就可以得到二进制程序。

[这篇博客](https://blog.csdn.net/qq_22182835/article/details/89467386)写的不错。然而Makefile编写是十分复杂的，且不能在Windows系统上运用。为了简化这个过程，并实现跨平台的自动化编译，CMake工具被发明出来。我们将在后文中详细介绍CMake工具

## 初识CMake

总的来说，在终端中编译C的可执行文件是一个辛苦的差事。如果要把程序交给别人评测，还需要写出一长串命令。随着项目的更改，编译的命令也需要变化。CMake一类的自动工具因此发展起来。CMake是个一个开源的跨平台自动化建构系统，用来管理软件建置的程序，并不依赖于某特定编译器，并可支持多层目录、多个应用程序与多个库。 它用配置文件控制建构过程（build process）的方式和Unix的make相似，只是CMake的配置文件取名为CMakeLists.txt。CMake并不直接建构出最终的软件，而是产生标准的建构档（如Unix的Makefile或Windows Visual C++的projects/workspaces），然后再依一般的建构方式使用。

CMake 和Unix下的`make`工具有很多渊源，但两者并不一样：前者是跨平台 的自动化建构系统，后者只存在于Unix上。
> [CMake](https://zh.wikipedia.org/wiki/CMake)

### 基本语法

`CMake`工程的主文件名为`CMakeLists.txt`。它允许用户通过一系列指令构建整一套工程。一个最基础的CMake工程通常包括以下语句：

```cmake
# 项目名称/类型
project(project_name C)

# 需要设置的编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT} -Wall -g -D DEBUG")

# 需要生成的可执行文件的名称以及源文件的路径
add_executable(executable_name sourcefile1.c sourcefile2.c)

# 需要输出的信息
message("your_message")
```

### 一个稍微复杂的CMake工程

[CMake官网](https://cmake.org/cmake/help/v3.21/)有详细的文档和示例。在CS139中，我们大概率不需要更加复杂的配置。此外，搜索引擎可以解答大部分的问题。
