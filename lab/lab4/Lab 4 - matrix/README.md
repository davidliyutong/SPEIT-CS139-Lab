# Lab 4 - MATRIX

## Task 0

设计一个 2D 矩阵数据结构`matrix_t`来存储一个浮点数组成的矩阵，例如

```c
typedef struct matrix_t {
    double * arr;
    size_t dim[2];
} matrix_t;
```

以及一个枚举类`err_t`用来描述我们可能遇到的错误

```c
typedef enum err_t {
    MATRIX_OK,
    MATRIX_FAIL
}err_t;
```

> 一些解释：
> `typedef`可以将`struct double_matrix_t` 重命名为`double_matrix_t`。

你可以加上自己的设计，例如取别的类型名称。

## Task 1

实现三个和矩阵相关的函数：

-   `matrix_init` 初始化矩阵，分配一块动态内存
-   `matrix_free` 释放`matrix_init`申请到内存
-   `matrix_repr` 显示矩阵的内容

### 演示

```c
...
int main(int argc, char** argv) {

    size_t dim[] = {5,5};
    matrix_t * pMat = matrix_init(dim);
    matrix_repr(pMat);
    matrix_free(pMat);

    return 0;
}
```

结果为

```console
(default) ➜ gcc task1.c -o task1 && ./task1
array([[0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000]])
```

### 提示

函数的原型可以这样设计： `matrix_repr`的效果可以随便设定

```c
matrix_t * matrix_init(size_t dim[2]);
err_t matrix_free(matrix_t *mat);
err_t matrix_repr(matrix_t * mat);
```

## Task 2

设计两个函数:

-   `matrix_get_item`
-   `matrix_set_item`

分别获取和设定矩阵的元素

### 演示

```c
int main(int argc, char** argv) {

    size_t dim[] = {5,5};
    matrix_t * pMat = matrix_init(dim);

    size_t coord[] = {1,1};
    matrix_set_item(pMat, coord, 5);
    matrix_repr(pMat);
    matrix_free(pMat);

    return 0;
}
```

```console
(default) ➜ gcc task2.c -o task2 && ./task2
array([[0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 5.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000]])
```

### 提示

函数原型

```c
err_t matrix_get_item(matrix_t * mat, size_t coord[2], double * val);
err_t matrix_set_item(matrix_t * mat, size_t coord[2], double val);
```

## Task 3

实现矩阵加法

$$RES_{n,m} = \lambda_1 * mat1_{n,m} + \lambda_2 * mat2_{n,m}  + k *J_{n,m}$$

$J_{n,m}$ 为 $n \times m$ 的全 1 矩阵

### 演示

```c
size_t coords1[] = { 0,0, 1,1, 2,2, 3,3 };
for (size_t* coord = coords1; coord < coords1 + (sizeof(coords1) / (sizeof(size_t))); coord += 2) {
        matrix_set_item(pMat1, coord, 1);
}

size_t coords2[] = { 0,0, 0,1,0,2,0,3 };
for (size_t* coord = coords2; coord < coords2 + (sizeof(coords2) / (sizeof(size_t))); coord += 2) {
    matrix_set_item(pMat2, coord, 10);
}

double k = -1.;
double lmd1 = 2.;
double lmd2 = 1.;

matrix_t* pMat3 = matrix_add(pMat1, pMat2, lmd1, lmd2, k);
```

```console
(default) ➜ gcc task3.c -o task3 && ./task3
array([[1.000, 0.000, 0.000, 0.000, 0.000]
       [0.000, 1.000, 0.000, 0.000, 0.000]
       [0.000, 0.000, 1.000, 0.000, 0.000]
       [0.000, 0.000, 0.000, 1.000, 0.000]
       [0.000, 0.000, 0.000, 0.000, 0.000]])

array([[10.000, 10.000, 10.000, 10.000, 0.000]
       [0.000, 0.000, 0.000, 0.000, 0.000]
       [0.000, 0.000, 0.000, 0.000, 0.000]
       [0.000, 0.000, 0.000, 0.000, 0.000]
       [0.000, 0.000, 0.000, 0.000, 0.000]])

array([[11.000, 9.000, 9.000, 9.000, -1.000]
       [-1.000, 1.000, -1.000, -1.000, -1.000]
       [-1.000, -1.000, 1.000, -1.000, -1.000]
       [-1.000, -1.000, -1.000, 1.000, -1.000]
       [-1.000, -1.000, -1.000, -1.000, -1.000]])
```

### 提示

```c
matrix_t * matrix_add(matrix_t * mat1, matrix_t * mat2, double lmd1, double lmd2, double k);
```

> 不要忘记在使用完毕后释放矩阵的内存

## Task 4 *

实现矩阵乘法

$$matmul(mat1, mat2) = mat1 . mat2$$

### 演示

```c
...
matrix_t* pMat3 = matrix_add(pMat1, pMat2, lmd1, lmd2, k);
matrix_t* pMat4 = matrix_matmul(pMat3, pMat2);
...
printf("\nmat3 = \n");
matrix_repr(pMat3);
printf("\nmat4 = \n");
matrix_repr(pMat4);
```

```console
(default) ➜ gcc -g task4.c -o task4 && ./task4
...

mat2 = 
array([[10.000, 10.000, 10.000, 10.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000],
       [0.000, 0.000, 0.000, 0.000, 0.000]])


mat3 = 
array([[11.000, 9.000, 9.000, 9.000, -1.000],
       [-1.000, 1.000, -1.000, -1.000, -1.000],
       [-1.000, -1.000, 1.000, -1.000, -1.000],
       [-1.000, -1.000, -1.000, 1.000, -1.000],
       [-1.000, -1.000, -1.000, -1.000, -1.000]])


mat4 = 
array([[110.000, 110.000, 110.000, 110.000, 0.000],
       [-10.000, -10.000, -10.000, -10.000, 0.000],
       [-10.000, -10.000, -10.000, -10.000, 0.000],
       [-10.000, -10.000, -10.000, -10.000, 0.000],
       [-10.000, -10.000, -10.000, -10.000, 0.000]])
```

### 提示

```c
matrix_t * matrix_matmul(matrix_t * mat1, matrix_t * mat2);
```

## Task 5

接下来创建两个文件`matrix.c` 和 `matrix.h`，将矩阵有关的代码保存在这两个文件里，使得人们可以通过 `#include<matrix.h>` 来使用我们编写的矩阵运算函数

```console
.
├── matrix.h
├── matrix.c
└── task5.c
```

`task5.c` 的内容如下：

```c
#include <stdio.h>
#include "matrix.h"

int main(int argc, char** argv) {

    size_t dim[] = {5,5};
    matrix_t * pMat = matrix_init(dim);

    printf("\nmat = \n");
    matrix_repr(pMat);
    matrix_free(pMat);

    return 0;
}
```

请同学们思考：

1. C语言的`#include`机制是怎样的?
2. `matrix.h` 中的内容应该是什么?
3. `matrix.c` 中的内容应该是什么?
4. 应该如何编译我们的程序?

## Task 6

使用`gcc -E`命令检查编译器的预处理。C语言代码在交给编译器之前，会先由预处理器进行一些文本替换方面的操作，例如宏展开`#define`、文件包含`#include`、删除部分代码等。在正常的情况下，GCC 不会保留预处理阶段的输出文件，也即`.i`文件。然而，可以利用`-E`选项保留预处理器的输出文件，以用于诊断代码

```console
gcc -E task5.c
```

> 你可以创建一个空的`matrix.h`文件，然后向里面写入任意的语句，然后查看GCC的处理结果

默认情况下，预处理器的输出会被导入到标准输出流`stdout`，可以利用-o选项把它导入到某个输出文件：

```console
gcc -E task5.c task5.i
```

现在回答问题：C语言的`#include`机制是怎样的?

## Task 7

参考[Compiling C Project](https://oc.sjtu.edu.cn/courses/38294/files/2980179?module_item_id=504381)，完成`matrix.h`和`matrix.c`的拆分

伪代码

```c
/** @file matrix.h **/

[需要包括的头文件]
#include ...

[宏的定义]
#define ...

[结构体定义]
typedef struct ..

[函数的原型]
matrix_t* matrix_init(size_t dim[2]);
...
```

```c
/** @file matrix.c **/

[需要包括的头文件]
#include ...
#include "matrix.h"

[函数的定义]
matrix_t* matrix_init(size_t dim[2]){
       ...
}
...
```

> 区分函数的原型和定义：
>
> - 原型：这里有一个这样的函数
> - 定义：这个函数实际上是这般那般

## Task 8

现在回答问题：应该如何编译我们的程序?

### 手动编译

GCC的`-c`选项只对源文件进行编译，不链接生成可执行文件。尝试执行以下命令

```console
gcc -c -g task5.c -o task5.o
gcc -c -g matrix.c -o matrix.o
```

> 思考：几个GCC选项的含义？

我们得到了两个obj文件

### 使用objdump检查obj文件

使用`which objdump`检查objdump的安装

```console
(default) ➜ which objdump
/usr/bin/objdump
```

常用`objdump`选项

- `objdump -t obj` 输出目标文件的符号表
- `objdump -S -d obj` C语言源代码与汇编语言同时显示

```console
objdump -S -d task5.o > task5.s
objdump -S -d matrix.o > matrix.s
```

```console
(default) ➜  objdump -t task5.o               

task5.o:        file format mach-o arm64

SYMBOL TABLE:
0000000000000000 l     F __TEXT,__text ltmp0
0000000000000090 l     O __TEXT,__literal16 l___const.main.dim
00000000000000a0 l     O __TEXT,__cstring l_.str
0000000000000090 l     O __TEXT,__literal16 ltmp1
00000000000000a0 l     O __TEXT,__cstring ltmp2
0000000000000568 l     O __LD,__compact_unwind ltmp3
0000000000000000 g     F __TEXT,__text _main
0000000000000000         *UND* ___stack_chk_fail
0000000000000000         *UND* ___stack_chk_guard
0000000000000000         *UND* _matrix_free
0000000000000000         *UND* _matrix_init
0000000000000000         *UND* _matrix_repr
0000000000000000         *UND* _printf

(default) ➜  objdump -t matrix.o               

matrix.o:       file format mach-o arm64

SYMBOL TABLE:
0000000000000000 l     F __TEXT,__text ltmp0
0000000000000630 l     O __TEXT,__cstring l_.str
0000000000000638 l     O __TEXT,__cstring l_.str.1
000000000000063a l     O __TEXT,__cstring l_.str.2
0000000000000641 l     O __TEXT,__cstring l_.str.3
000000000000064e l     O __TEXT,__cstring l_.str.4
0000000000000630 l     O __TEXT,__cstring ltmp1
0000000000000f50 l     O __LD,__compact_unwind ltmp2
00000000000002e4 g     F __TEXT,__text _matrix_add
0000000000000090 g     F __TEXT,__text _matrix_free
00000000000001c8 g     F __TEXT,__text _matrix_get_item
0000000000000000 g     F __TEXT,__text _matrix_init
000000000000045c g     F __TEXT,__text _matrix_matmul
00000000000000cc g     F __TEXT,__text _matrix_repr
0000000000000258 g     F __TEXT,__text _matrix_set_item
0000000000000000         *UND* ___memcpy_chk
0000000000000000         *UND* ___stack_chk_fail
0000000000000000         *UND* ___stack_chk_guard
0000000000000000         *UND* _calloc
0000000000000000         *UND* _exit
0000000000000000         *UND* _free
0000000000000000         *UND* _printf
```

> `file format` 和编译器的平台有关，这里编译平台是Mac M1，使用了`gcc-arm64`

可以发现，在`task5.o`中，符号`_matrix_free`, `_matrix_init` 和 `_matrix_repr`都是未定义的。因此当我们直接使用 `gcc task5.c -o task5.o` 时，编译器会找不到这些函数的定义（因为`task5.c`和`matrix.h`中都没有这些函数的定义。

### 手动连接

我们可以把 `task5.o` 和 `matrix.o` 手动链接到一起来解决这一问题

```console

(default) ➜  gcc task5.o matrix.o -o task5
(default) ➜  gcc task5.o matrix.o -o task5

task5:  file format mach-o arm64

SYMBOL TABLE:
0000000100008030 l     O __DATA,__data __dyld_private
0000000000000000      d  *UND* ***
0000000000000000      d  *UND* task5.c
0000000061908d69      d  *UND* ***
00000001000037fc      d  *UND* 
00000001000037fc      d  *UND* _main
000000000000008c      d  *UND* 
000000000000008c      d  *UND* 
0000000000000000      d  *UND* 
0000000000000000      d  *UND* ***
0000000000000000      d  *UND* matrix.c
0000000061908e38      d  *UND* ***
0000000100003888      d  *UND* 
0000000100003888      d  *UND* _matrix_init
0000000000000090      d  *UND* 
0000000000000090      d  *UND* 
0000000100003918      d  *UND* 
0000000100003918      d  *UND* _matrix_free
000000000000003c      d  *UND* 
000000000000003c      d  *UND* 
0000000100003954      d  *UND* 
0000000100003954      d  *UND* _matrix_repr
00000000000000fc      d  *UND* 
00000000000000fc      d  *UND* 
0000000100003a50      d  *UND* 
0000000100003a50      d  *UND* _matrix_get_item
0000000000000090      d  *UND* 
0000000000000090      d  *UND* 
0000000100003ae0      d  *UND* 
0000000100003ae0      d  *UND* _matrix_set_item
000000000000008c      d  *UND* 
000000000000008c      d  *UND* 
0000000100003b6c      d  *UND* 
0000000100003b6c      d  *UND* _matrix_add
0000000000000178      d  *UND* 
0000000000000178      d  *UND* 
0000000100003ce4      d  *UND* 
0000000100003ce4      d  *UND* _matrix_matmul
00000000000001d4      d  *UND* 
00000000000001d4      d  *UND* 
0000000000000000      d  *UND* 
0000000100000000 g     F __TEXT,__text __mh_execute_header
00000001000037fc g     F __TEXT,__text _main
0000000100003b6c g     F __TEXT,__text _matrix_add
0000000100003918 g     F __TEXT,__text _matrix_free
0000000100003a50 g     F __TEXT,__text _matrix_get_item
0000000100003888 g     F __TEXT,__text _matrix_init
0000000100003ce4 g     F __TEXT,__text _matrix_matmul
0000000100003954 g     F __TEXT,__text _matrix_repr
0000000100003ae0 g     F __TEXT,__text _matrix_set_item
0000000000000000         *UND* ___memcpy_chk
0000000000000000         *UND* ___stack_chk_fail
0000000000000000         *UND* ___stack_chk_guard
0000000000000000         *UND* _calloc
0000000000000000         *UND* _exit
0000000000000000         *UND* _free
0000000000000000         *UND* _printf
0000000000000000         *UND* dyld_stub_binder
```

可以发现，在`task5`中，符号`_matrix_free`, `_matrix_init` 和 `_matrix_repr`都是定义的。`./task5`可以直接执行

### 简化的命令

`gcc task5.c matrix.c -o task5` 可以直接完成编译+链接的操作

## Task 9 *

使用GDB调试，观察程序的运行

参考[Introduction to GDB](https://oc.sjtu.edu.cn/courses/38294/pages/introduction-to-gdb?module_item_id=538058)，使用GDB调试程序的运行，练习GDB的使用。