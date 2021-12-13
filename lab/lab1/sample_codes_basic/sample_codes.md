# Sample codes for First Lab

## a_plus_b.c

```c
/**
 * @file a_plus_b.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/** @note 包括stdio头文件以使用scanf，printf函数**/
#include <stdio.h>

/**
 * @brief 读取两个整数，打印他们的和
 * 
 * @param argc Unused
 * @param argv Unused
 * @return int 0
 */
int main(int argc, char** argv) {

    /** 定义两个整数类型变量 **/
    int a, b; 

    /** 使用scanf读取标准输入stdin
     * 
     * - scanf() 读取键盘输入
     * - "%d %d" 是读取的格式，注意区分 "%d,%d" 的区别
     * - &a 代表a的地址, scanf() 利用这个地址修改a的值
    **/
    scanf("%d %d", &a, &b);

    /** 使用printf打印到标准输出stdout
     * 
     * - printf() 打印字符
     * - "%d" 是以十进制输出整数变量的方式
     * - a + b 是a，b的和，我们不需要创建额外的变量
    **/
    printf("%d\n", a + b);

    /** 正常退出 return 0 **/
    return 0;
}
```

## gcd.c

```c
/**
 * @file gcd.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>


 /**
  * @brief 交换两个变量的值
  *
  * @param p_a a 指针
  * @param p_b b 指针
  */
void swap(int* p_a, int* p_b) {
    /** 利用temp变量做中转 **/
    int temp;
    /** 使用*来访问指针所指的值 **/
    temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
}

/**
 * @brief 用辗转相除法计算 gcd(a,b)
 *
 * @param a
 * @param b
 * @return int
 */
int gcd(int a, int b) {
    int r;
    /** 如果 a < b,交换a，b并继续 **/
    swap(&a, &b);

    /** 辗转相除 **/
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

 /**
  * @brief 计算 GCD(a,b)
  *
  * @param argc 没用
  * @param argv 没用
  * @return int 0
  */
int main(int argc, char** argv) {

    int a, b;

    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));

    /** 正常退出 return 0 **/
    return 0;
}
```

## fibonacci.c

```c
/**
 * @file fibonacci.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
 /** @note 包括 stdlib.h 以便使用 strtol() **/
#include <stdlib.h>

/**
 * @brief 通过循环计算 fibonacci(n)
 *
 * @param a
 * @param b
 * @return int
 */
int fibonacci(int n) {
    int t1 = 0, t2 = 1, t_next;
    if (n == 0) return 0;
    if (n == 1) return 1;
    /** 循环 n-2 次 即可得到 fibonacci(n) **/
    for (int idx = 1; idx <= n - 1; ++idx) {
        t_next = t1 + t2;
        t1 = t2;
        t2 = t_next;
    }
    return t_next;
}


/**
 * @brief 计算 fibonacci(n)
 *
 * @param argc 至少2
 * @param argv argv[1] 为 n
 * @return int 0
 */
int main(int argc, char** argv) {

    /** 创建保存n的变量 **/
    int n;
    /** 用于保存记录strol返回的执行状态 **/
    char* endptr = NULL;

    /** 检查是否有足够的参数
     * 
     * - 如果有 n 个参数， argc == n+1
     * - 如果 argc <= 1, 异常退出， return 1
    **/
    if (argc <= 1) exit(1);

    /** 使用 strtol 将字符数组转化成整数
     * 
     * - strtol 返回 'long int' 值, 使用 '(int)' 将其转换成int
     * - argv[1] 类型是 char 指针 (char*)
     * - &endptr 是 endptr 的地址, 是二重指针 (char **)
     * - 如果输入是非法的，例如非数字字符，strtol不能够处理。它会把endptr 设置成字符串的起点 string 即 argv[1]。如果该指针等于argv[1]，输入就不合法
    **/
    n = (int) strtol(argv[1], &endptr, 10);
    if (endptr == argv[1]) exit(2);

    /** 打印结果 fibonacci(n) **/
    printf("%d\n", fibonacci(n));

    /** 正常退出 return 0 **/
    return 0;
}

```

## what_day.c

```c
/**
 * @file what_day.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
/** @note 包括 string.h 以使用 strlen() **/
#include <string.h>

/**
 * @brief 通过ascii计算，对单个数字类型字符求值
 *
 * 在ascii中(https://baike.baidu.com/item/ASCII), '0' 等价与数值48(0x30)
 * '1' - '0' = 1, '2' - '0' = 2,...以此类推
 * 宏完成的是字符串替换的功能：
 * - EVAL_CHAR(x) ((x) - '0') 可以被展开为  (x - '0')
 * 例如
 * - EVAL_CHAR('1')  =>  ('1' - '0') ，其值为  1
 */
#define EVAL_CHAR(x) ((x) - '0')

 /**
  * @brief 将 YYYY-mm-DD 格式的字符解释为年、月、日
  *
  * @param arg YYYY-mm-DD 格式日期.
  * @param year year[*int] 年指针，用于获取结果
  * @param month month[*int] 月指针，用于获取结果
  * @param day day[*nt] 日指针，用于获取结果
  * @return 状态代码 0 for 表示成功 -1 表示失败
  * @remark 该函数通过修改 year, month, day指向的值来输出结果
  * 必须严格遵守格式，arg长度为10，其5、8位为'-'
  * @example
  * >>>
  * int year, month, day;
  * int ret = parse_arg(argv[1], &year, &month, &day);
  * printf("year:%d, month:%d, day:%d", year, month, day);
  * >>>
  */
int parse_arg(char* const arg, int* year, int* month, int* day) {

    /** 检查格式 **/
    if (strlen(arg) != 10 || arg[4] != '-' || arg[7] != '-') return -1; 

    /** 累加计算年月日 **/
    *year = EVAL_CHAR(arg[0]) * 1000 + EVAL_CHAR(arg[1]) * 100 + EVAL_CHAR(arg[2]) * 10 + EVAL_CHAR(arg[3]);
    *month = EVAL_CHAR(arg[5]) * 10 + EVAL_CHAR(arg[6]); 
    *day = EVAL_CHAR(arg[8]) * 10 + EVAL_CHAR(arg[9]);

    return 0;
}

/** 这个宏用于判断是不是闰年 **/
#define is_leap_year(year) ((((year) % 4 == 0) && ((year) % 100 != 0)) || ((year) % 400 == 0))

/**
 * @brief 返回特定日期的星期数 (Mon., Tue., Wed., ...Sun.)
 * 
 * @ref https://www.zhihu.com/question/369735069
 *
 * @param year 年
 * @param month 月
 * @param day 日
 * @return 整数 1-6 对应 Mon.-Sat., 7 对应 Sun.
 */
int what_day(int year, int month, int day) {
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }
    int week_day = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1) % 7;
    return week_day;

}

int main(int argc, char** argv) {
    /** 定义变量保存年月日 **/
    int year, month, day;

    /** 创建一个缓冲数组。字符串的结尾是'\0'，需要保存。因此需要额外一位的空间 **/
    char buf[11];
    /** %10s 只读入10个字符 **/
    scanf("%10s", buf);

    /** 解析输入并判断是不是合法 **/
    int ret = parse_arg(buf, &year, &month, &day);
    if (ret != 0) return -1;

    /** 显示解析后的年月日 **/
    printf("Year:%d, Month:%d, Day:%d\n", year, month, day);

    /** 运行算法 **/
    printf("%d\n", what_day(year, month, day));
    return 0;
}
```
