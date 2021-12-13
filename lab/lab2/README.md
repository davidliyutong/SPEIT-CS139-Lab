# Lab 2

## Guidelines

总是写注释，让你的程序容易被看懂
使用有意义的变量名称和函数名称

## Task 0

如果我们要从键盘读取$10$个整数并保存在数组中，然后将这些数字打印出来。以下程序可以作为参考：

- `int arr[10]` 可以创建一个长度为10，类型为`int`的数组
- `scanf("%d"， &arr[0])` 可以用将键盘输入读取到`arr[0]`

```c
#include <stdio.h>

#define ARRAY_LEN 10

int main(int argc, char** argv) {

    int arr[ARRAY_LEN];

    printf("Enter the elements into the array: ");
    for (int i = 0; i < ARRAY_LEN; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nThe elements of the array are: ");
    for (int i = 0; i < ARRAY_LEN; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
```

演示：

```text
$ ./task_0
Enter the elements into the array: 1 2 3 5 6 7 8 9 10 9
The elements of the array are: 1 2 3 5 6 7 8 9 10 9   
```

## Task 1

修改程序，从保存的数组中查找特定的整数。尝试把**task0**中的代码改写成函数，并重复使用。

提示：

- 首先从键盘中读取要查找的数
- 然后进行查找
- 如果没有该数不存在数组中，给出提示
- 如果该数存在，给出其在数组中的位置
- 注意考虑数组中出现重复元素的情况

演示：

```text
$ ./task_1
Enter the elements into the array: 1 2 3 5 6 7 8 9 10 9
The elements of the array are: 1 2 3 5 6 7 8 9 10 9    
Input the number to query:
>>> 4
The number does not exist.
Input the number to query:
>>> 5
The number exists, its index is 3.
```

## Task 2

修改程序，输出数组中所有元素的和

演示：

```text
$ ./task_2
Enter the elements into the array: 1 2 3 5 6 7 8 9 10 9
The elements of the array are: 1 2 3 5 6 7 8 9 10 9    
The sum of array is 60.
```

## Task 3

修改程序，找到数组中最大和最小的元素，并打印他们在数组中的位置。

提示：

- 注意考虑数组中出现多个并列最大值最小值的情况，将它们全部打印出来

演示：

```text
$ ./task_3
Enter the elements into the array: 1 2 10 5 6 7 8 9 10 9
The elements of the array are: 1 2 3 5 6 7 8 9 10 9
The maximum element of the array is: 10 at index 2, 8,
The minimum element of the array is: 1 at index 0,
```

## Task 4

修改程序，统计数组中偶数的个数

演示：

```text
$ ./task_4
Enter the elements into the array: 1 2 10 5 6 7 8 9 10 9
The elements of the array are: 1 2 3 5 6 7 8 9 10 9
There are 5 even numbers.
```

## Task 5

修改程序，将保存的数组逆序，并打印逆序后的数组内容

提示：

- 注意要修改数组在内存中的内容，而非简单的用逆序将数组打印
- 可以使用额外的变量帮助交换

演示：

```text
$ ./task_5
Enter the elements into the array: 1 2 10 5 6 7 8 9 10 9
The elements of the array are: 1 2 3 5 6 7 8 9 10 9
The array is reversed.
The elements of the array are: 9 10 9 8 7 6 5 3 2 1
```

## Task 6 (选做)

在**task0**中没有考虑输入时出现非数字字符的情况，同学们可以考虑一下如何从输入中排除非法数字或者在输入非法数字时给出提示。
