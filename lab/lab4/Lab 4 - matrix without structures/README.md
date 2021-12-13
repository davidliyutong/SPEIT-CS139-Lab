# Lab 4 - MATRIX

## Task 0

我们可以用`enum`来定义一个枚举类。C 语言提供了对枚举（Enum）类型，能够为数值取一个容易理解的名字

```c
enum err_t {
    MATRIX_OK = 0,
    MATRIX_FAIL = -1
};
```

定义了枚举类型后，就可以像使用宏一样使用它们。

我们可以使用二维数组存储一个矩阵：

```c
double mat[N_ROW][N_COL];
```

为了方便理解程序，我们可以用`typedef`为和`enum err_t`类型取一个别名。

```c
typedef enum err_t err_t;
```

## Task 1

### 任务

尝试使用`enum`和`typedef`，并设计一段程序来给这个矩阵赋值。你可以使用一个形如

```c
err_t matrix_assign_value(double * mat, size_t n_row, size_t n_col);
```

来给矩阵赋值。你可以用随机数填充矩阵，也可以用`scanf`从键盘读取数字你可以加上自己的设计，例如取别的函数名称。

实现打印矩阵的函数 `matrix_repr`：

```c
err_t matrix_repr(double * mat, size_t n_row, size_t n_col);
```

其效果可以随便设定。

### 演示

```c
#define N_ROW 10
#define N_COL 10
int main(int argc, char** argv) {
    srand(time(NULL));

    double mat1[N_ROW][N_COL];
    matrix_assign((double *)mat1, N_ROW, N_COL);

    printf("\nmat1 = \n");
    matrix_repr((double *)mat1, N_ROW, N_COL);

    return 0;
}
```

结果为

```console
(default) ➜  Lab 4 - matrix without structures gcc task1.c -o task1 && ./task1

mat1 =
array([[63.000, 10.000, 23.000, 77.000, 43.000, 62.000, 16.000, 39.000, 62.000, 77.000],
       [47.000, 16.000, 39.000, 60.000, 26.000, 31.000, 72.000, 3.000, 12.000, 27.000],
       [31.000, 73.000, 5.000, 69.000, 59.000, 23.000, 62.000, 46.000, 35.000, 24.000],
       [31.000, 3.000, 78.000, 26.000, 64.000, 47.000, 28.000, 33.000, 64.000, 49.000],
       [76.000, 37.000, 23.000, 59.000, 27.000, 57.000, 57.000, 76.000, 16.000, 18.000],
       [61.000, 26.000, 77.000, 75.000, 23.000, 36.000, 40.000, 34.000, 70.000, 59.000],
       [24.000, 26.000, 58.000, 1.000, 65.000, 43.000, 49.000, 19.000, 72.000, 28.000],
       [25.000, 60.000, 18.000, 17.000, 56.000, 79.000, 73.000, 63.000, 12.000, 78.000],
       [32.000, 71.000, 46.000, 11.000, 15.000, 12.000, 25.000, 18.000, 1.000, 38.000],
       [58.000, 66.000, 10.000, 61.000, 14.000, 51.000, 66.000, 42.000, 8.000, 58.000]])
```

### 提示

> 你可以用不同的方式设计函数，自定义传入参数的类型
>
> `size_t` 是 C 标准的一部分，定义在`stddef.h`中。它是一个与机器相关的`unsigned`类型，其大小足以保证存储内存中对象的大小。

## Task 2

### 任务

实现矩阵加法：

```c
err_t matrix_add(double * mat1,
                 double * mat2,
                 double * res,
                 double lmd1,
                 double lmd2,
                 double k,
                 size_t n_row, size_t n_col);
```

$$res_{n,m} = \lambda_1 \times mat1_{n,m} + \lambda_2 \times mat2_{n,m}  + k \times J_{n,m}$$

$J_{n,m}$ 为 $n \times m$ 的全 1 矩阵

### 演示

```c
#define N_ROW 3
#define N_COL 3
int main(int argc, char** argv) {
    srand(time(NULL));

    double mat1[N_ROW][N_COL];
    matrix_assign((double *)mat1, N_ROW, N_COL);
    double mat2[N_ROW][N_COL];
    matrix_assign((double *)mat2, N_ROW, N_COL);

    double res[N_ROW][N_COL];
    matrix_add((double *)mat1, (double *)mat2, (double *)res, 1, 1, 0, N_ROW, N_COL);

    printf("\nmat1 = \n");
    matrix_repr((double *)mat1, N_ROW, N_COL);
    printf("\nmat2 = \n");
    matrix_repr((double *)mat2, N_ROW, N_COL);
    printf("\res = \n");
    matrix_repr((double *)res, N_ROW, N_COL);

    return 0;
}
```

结果为

```console
(default) ➜  Lab 4 - matrix without structures gcc task2.c -o task2 && ./task2

mat1 =
array([[28.000, 67.000, 71.000],
       [51.000, 46.000, 3.000],
       [58.000, 54.000, 5.000]])


mat2 =
array([[9.000, 42.000, 27.000],
       [14.000, 75.000, 18.000],
       [23.000, 4.000, 3.000]])

es =
array([[37.000, 109.000, 98.000],
       [65.000, 121.000, 21.000],
       [81.000, 58.000, 8.000]])
```

### 提示

> 你可以用不同的方式设计函数，自定义传入参数的类型
>
> mat1, mat2, res 的内存需要提前分配好，并且确保他们的尺寸是一致的。

## Task 3 \*

实现矩阵乘法 `matrix_matmul`:

```c
err_t matrix_matmul(double * mat1,
                    double * mat2,
                    double * res,
                    size_t n_row1, size_t n_col1,
                    size_t n_row2, size_t n_col2);
```

$$res = mat1 . mat2$$

### 演示

```c
...
#define RANDINT(N) rand() % N
#define VALUE_MAX 8
...

#define N_ROW 3
#define N_COL 3
int main(int argc, char** argv) {
    srand(time(NULL));

    double mat1[N_ROW][N_COL];
    matrix_assign((double*)mat1, N_ROW, N_COL);
    double mat2[N_ROW][N_COL];
    matrix_assign((double*)mat2, N_ROW, N_COL);

    double res[N_ROW][N_COL];
    matrix_matmul((double*)mat1, (double*)mat2, (double*)res, N_ROW, N_COL, N_ROW, N_COL);

    printf("\nmat1 = \n");
    matrix_repr((double*)mat1, N_ROW, N_COL);
    printf("\nmat2 = \n");
    matrix_repr((double*)mat2, N_ROW, N_COL);
    printf("\res = \n");
    matrix_repr((double*)res, N_ROW, N_COL);

    return 0;
}
```

结果为

```console
(default) ➜  Lab 4 - matrix without structures gcc task3.c -o task3 && ./task3

mat1 =
array([[2.000, 6.000, 7.000],
       [4.000, 5.000, 1.000],
       [1.000, 7.000, 0.000]])


mat2 =
array([[1.000, 7.000, 0.000],
       [3.000, 7.000, 6.000],
       [5.000, 6.000, 6.000]])

es =
array([[55.000, 98.000, 78.000],
       [24.000, 69.000, 36.000],
       [22.000, 56.000, 42.000]])

(default) ➜  Lab 4 - matrix without structures python
Python 3.8.8 | packaged by conda-forge | (default, Feb 20 2021, 15:50:57)
[Clang 11.0.1 ] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import numpy as np
>>> from numpy import array
>>> np.matmul(array([[2.000, 6.000, 7.000],
...        [4.000, 5.000, 1.000],
...        [1.000, 7.000, 0.000]]),
...        array([[1.000, 7.000, 0.000],
...        [3.000, 7.000, 6.000],
...        [5.000, 6.000, 6.000]]))
array([[55., 98., 78.],
       [24., 69., 36.],
       [22., 56., 42.]])
>>>
```

## Task 4

接下来（Task 4 - Task6）我们会创建两个文件`matrix.c` 和 `matrix.h`，将矩阵有关的代码保存在这两个文件里，使得人们可以通过 `#include<matrix.h>` 来使用我们编写的矩阵运算函数

```console
.
├── matrix.h
├── matrix.c
└── task4.c
```

`task4.c` 的内容如下：

```c
#include <stdio.h>
#include <time.h>
#include "matrix.h"

#define N_ROW 10
#define N_COL 10
int main(int argc, char** argv) {
    srand(time(NULL));

    double mat1[N_ROW][N_COL];
    matrix_assign((double *)mat1, N_ROW, N_COL);

    printf("\nmat1 = \n");
    matrix_repr((double *)mat1, N_ROW, N_COL);

    return 0;
}
```

请同学们思考：

1. C 语言的`#include`机制是怎样的?
2. `matrix.h` 中的内容应该是什么?
3. `matrix.c` 中的内容应该是什么?
4. 应该如何编译我们的程序?

## Task 5 \*

使用`gcc -E`命令检查编译器的预处理。C 语言代码在交给编译器之前，会先由预处理器进行一些文本替换方面的操作，例如宏展开`#define`、文件包含`#include`、删除部分代码等。在正常的情况下，GCC 不会保留预处理阶段的输出文件，也即`.i`文件。然而，可以利用`-E`选项保留预处理器的输出文件，以用于诊断代码

```console
gcc -E task4.c
```

> 你可以创建一个空的`matrix.h`文件，然后向里面写入任意的语句，然后查看 GCC 的处理结果

默认情况下，预处理器的输出会被导入到标准输出流`stdout`，可以利用 `-o` 选项把它导入到某个输出文件：

```console
gcc -E task4.c -o task4.i
```

现在回答问题：C 语言的`#include`机制是怎样的?

## Task 6

参考[Compiling C Project](https://oc.sjtu.edu.cn/courses/38294/files/2980179?module_item_id=504381)，完成`matrix.h`和`matrix.c`的拆分

伪代码

```c
/** @file matrix.h **/

[需要包括的头文件]
#include ...

[宏的定义]
#define ...

[结构体定义和枚举定义]
struct ..
typedef ..
enum ..

[函数的原型]
err_t matrix_assign(double* mat, size_t n_row, size_t n_col);
...
```

```c
/** @file matrix.c **/

[需要包括的头文件]
#include ...
#include "matrix.h"

[函数的定义]
err_t matrix_assign(double* mat, size_t n_row, size_t n_col){
       ...
}
...
```

> 区分函数的原型和定义：
>
> -   原型：这里有一个这样的函数
> -   定义：这个函数实际上是这般那般
>
> 现在回答问题：为什么 matrix.c 要`#include "matrix.h"`?

## Task 7 \*

现在回答问题：应该如何编译我们的程序?

### 手动编译

GCC 的`-c`选项只对源文件进行编译，不链接生成可执行文件。尝试执行以下命令

```console
gcc -c -g task4.c -o task4.o
gcc -c -g matrix.c -o matrix.o
```

> 思考：几个 GCC 选项的含义？

我们得到了两个 obj 文件

### 使用 objdump 检查 obj 文件

使用`which objdump`检查 objdump 的安装

```console
(default) ➜ which objdump
/usr/bin/objdump
```

常用`objdump`选项

-   `objdump -t obj` 输出目标文件的符号表
-   `objdump -S -d obj` C 语言源代码与汇编语言同时显示

```console
objdump -S -d task4.o > task4.s
objdump -S -d matrix.o > matrix.s
```

```console
(default) ➜  Lab 4 - matrix without structures objdump -t task4.o

task4.o:        file format mach-o arm64

SYMBOL TABLE:
0000000000000000 l     F __TEXT,__text ltmp0
000000000000009c l     O __TEXT,__cstring l_.str
000000000000009c l     O __TEXT,__cstring ltmp1
0000000000000448 l     O __LD,__compact_unwind ltmp2
0000000000000000 g     F __TEXT,__text _main
0000000000000000         *UND* ___stack_chk_fail
0000000000000000         *UND* ___stack_chk_guard
0000000000000000         *UND* _matrix_assign
0000000000000000         *UND* _matrix_repr
0000000000000000         *UND* _printf
0000000000000000         *UND* _srand
0000000000000000         *UND* _time
```

> `file format` 和编译器的平台有关，这里编译平台是 Mac M1，使用了`gcc-arm64`
>
> 需要通过`-g`选项来保留调试信息

可以发现，在`task4.o`中，符号`_matrix_assign` 和 `_matrix_rep`都是未定义的。因此当我们直接使用 `gcc task4.c -o task4.o` 时，编译器会找不到这些函数的定义（因为`task4.c`和`matrix.h`中都没有这些函数的定义。

> `_printf` 为什么也是为定义的?

### 手动连接

我们可以把 `task4.o` 和 `matrix.o` 手动链接到一起来解决这一问题

```console
gcc task4.o matrix.o -o task4
```

```console
(default) ➜  Lab 4 - matrix without structures objdump -t task4             

task4:  file format mach-o arm64

SYMBOL TABLE:
0000000100008028 l     O __DATA,__data __dyld_private
0000000000000000      d  *UND* /Users/liyutong/Desktop/2021-1 CS139-助教/Documents/2021-11-06 4th Lab/Lab 4 - matrix without structures/
0000000000000000      d  *UND* task4.c
000000006191e21d      d  *UND* /Users/liyutong/Desktop/2021-1 CS139-助教/Documents/2021-11-06 4th Lab/Lab 4 - matrix without structures/task4.o
0000000100003b14      d  *UND* 
0000000100003b14      d  *UND* _main
000000000000009c      d  *UND* 
000000000000009c      d  *UND* 
0000000000000000      d  *UND* 
0000000000000000      d  *UND* /Users/liyutong/Desktop/2021-1 CS139-助教/Documents/2021-11-06 4th Lab/Lab 4 - matrix without structures/
0000000000000000      d  *UND* matrix.c
000000006191e1ed      d  *UND* /Users/liyutong/Desktop/2021-1 CS139-助教/Documents/2021-11-06 4th Lab/Lab 4 - matrix without structures/matrix.o
0000000100003bb0      d  *UND* 
0000000100003bb0      d  *UND* _matrix_assign
0000000000000078      d  *UND* 
0000000000000078      d  *UND* 
0000000100003c28      d  *UND* 
0000000100003c28      d  *UND* _matrix_repr
00000000000000f0      d  *UND* 
00000000000000f0      d  *UND* 
0000000100003d18      d  *UND* 
0000000100003d18      d  *UND* _matrix_add
000000000000009c      d  *UND* 
000000000000009c      d  *UND* 
0000000100003db4      d  *UND* 
0000000100003db4      d  *UND* _matrix_matmul
000000000000012c      d  *UND* 
000000000000012c      d  *UND* 
0000000000000000      d  *UND* 
0000000100000000 g     F __TEXT,__text __mh_execute_header
0000000100003b14 g     F __TEXT,__text _main
0000000100003d18 g     F __TEXT,__text _matrix_add
0000000100003bb0 g     F __TEXT,__text _matrix_assign
0000000100003db4 g     F __TEXT,__text _matrix_matmul
0000000100003c28 g     F __TEXT,__text _matrix_repr
0000000000000000         *UND* ___stack_chk_fail
0000000000000000         *UND* ___stack_chk_guard
0000000000000000         *UND* _printf
0000000000000000         *UND* _rand
0000000000000000         *UND* _srand
0000000000000000         *UND* _time
0000000000000000         *UND* dyld_stub_binder
```

可以发现，在`task4`中，符号`_matrix_assign` 和 `_matrix_rep`都是定义的。`./task4`可以直接执行

> `_printf` 为什么也是定义的?

### 简化的命令

`gcc task4.c matrix.c -o task4` 可以直接完成编译+链接的操作

## Task 8 \*

使用 GDB 调试，观察程序的运行

参考[Introduction to GDB](https://oc.sjtu.edu.cn/courses/38294/pages/introduction-to-gdb?module_item_id=538058)，使用 GDB 调试程序的运行，练习 GDB 的使用。
