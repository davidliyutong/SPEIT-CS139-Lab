# Lab 1

## Task 1: $A + B$

设计一段程序，从键盘读入 $A$、$B$ 两个数。计算 $A+B$ 的值并输出

描述：

- $A$、$B$ 均为整数
- $-10000000 \leq A, B \leq 10000000$

提示：

- 使用`scanf("%d %d", &A, &B);`可以从键盘读出**用空格分割的**两个整数
- 使用`printf("%d", A+B);`可以输出计算的结果

演示：

```bash
$ ./a_plus_b
> 10 -10
0
```

## Task 2: $GCD(A, B)$

Greatest Common Divisor (GCD) 即最大公约数。有关最大公约数的介绍，请阅读[百度百科-最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin).

设计一段程序，从键盘读入 $A$、$B$ 两个数。计算 $GCD(A+B)$ 的值并输出

描述：

- $A$、$B$ 均为正整数
- $0 \leq A, B \leq 10000000$

演示：

```bash
$ ./gcd
> 5 10
5
```

## Task 3: Fibonacci sequence

斐波那契数列（Fibonacci sequence），又称黄金分割数列。

在数学上，斐波那契数列以如下被以递推的方法定义：

- $$F(0)=0$$
- $$F(1)=1$$
- $$F(n)=F(n - 1)+F(n - 2)（n \geq 2，n \in N*）$$

设计一段程序，从**传入参数**读取一个正整数$N$，然后输出$F(N)$

> **关于传入参数的说明**
> 假设有这样一段程序：
>
> ```c
> /**
> example_program.c
> **/
> int main (int argc, char ** argv) {
>     printf("%d\n", argc);
>     printf("%s\n", argv[0]);
>     printf("%s\n", argv[1]);
>     return 0;
> }
> ```
>
> 那么当我们执行`./example_program arg1`时， arg1将会被传入程序。我们将有如下输出：
>
>```bash
>$./example_program arg1
>2
>./example_program
>arg1
>```
>
>我们可以发现`argc`值为2，有两个参数被传入了，分别是程序的执行路径和`"arg1"`字符串

演示：

```bash
$ ./fiboacci 5
5
```

Sample Code of processing arguments:

```C
#include <stdio.h>
 /** @note Include stdlib.h to use strtol() **/
#include <stdlib.h>
int main(int argc, char** argv) {
    int n = (int) strtol(argv[1], NULL, 10);
    /** After strtol(), argv[1] is converted from char * to int **/
    /** You can proceed with variable n **/
    printf("N = %d\n", n);
    return 0;
}
```

> 提示
>
> 解决这个问题有两种思路：
>
> 1. 使用循环
> 2. 使用递归 (**Bonus**)

## (**Bonus**) Task 4: What day of the week is it?

设计一段程序，从键盘读取日期，然后输出这天是星期几

描述：

- 日期的格式是YYYY-mm-DD, 例如`2021-09-17`
- 日期作为第一个也是唯一一个参数传入
- 日期是有效的公元日期，意味着不会有`2021-02-29`这样的日期出现
- 输入只会出现**新中国成立后**的日期, 而且在`9999-12-31`以前
- 星期一到星期六由对应的数字表示。星期天用数字7表示

演示：

```bash
$ ./what_day
> 2021-09-17
5
```

> 提示
>
> - 我们假设公元1年1月1日(0001-01-01)是星期天
> - 现行的格里高利历，用格利高里历回算的1年1月1日并非是“真正的”1年1月1日

```C
#include <stdio.h>
#include <string.h>

/**
 * @brief Convert a single digit from char to int by manipulating with ascii
 * 
 */
#define EVAL_CHAR(x) ((x) - '0')

/**
 * @brief Parse a YYYY-mm-DD format string to year, month, day
 * 
 * @param arg A string in YYYY-mm-DD format.
 * @param year year[*int]
 * @param month month[*int]
 * @param day day[*nt]
 * @return int Status code. 0 for success and -1 for failure
 * @remark The function will modify year, month and day using their pointer.
 *         The length of arg must by 10, the 5th and 8th position of arg must by '-'
 * @example
 * >>>
 * int year, month, day;
 * int ret = parse_arg(argv[1], &year, &month, &day);
 * printf("year:%d, month:%d, day:%d", year, month, day);
 * >>>
 */
int parse_arg(char * const arg, int * year, int * month, int * day) {

    if (strlen(arg) != 10 || arg[4] != '-' || arg[7] != '-') return -1; // Check format.
    
    *year = EVAL_CHAR(arg[0]) * 1000 + EVAL_CHAR(arg[1]) * 100 + EVAL_CHAR(arg[2]) * 10 + EVAL_CHAR(arg[3]); // Calculate year by adding digits
    *month = EVAL_CHAR(arg[5]) * 10 + EVAL_CHAR(arg[6]); // Calculate month by adding digits
    *day = EVAL_CHAR(arg[8]) * 10 + EVAL_CHAR(arg[9]); // Calculate day by adding digits

    return 0;
}

int main(int argc, char** argv) {
    int year, month, day;
    char buf[11]; // buffer, 1 byte larger than desired to store extra '\0'
    scanf("%10s", buf); // limit scanf length to 10
    int ret = parse_arg(buf, &year, &month, &day);
    printf("year:%d, month:%d, day:%d", year, month, day);
    return 0;
}
```
