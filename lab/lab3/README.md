# Lab 2

## Task 0

准备一个`print_arr`函数，用来在Terminal显示数组：

```c
void print_arr(int *arr, int length){
    ...
}
```

准备一个`swap`函数实现在`array`中两个位置上的数的而交换(注意数组边界检查)：

```c
void swap(int *arr, int length, int i, int j){
    ...
}
```

## Task 1

我们准备一个长度为*SIZE*的数组（*SIZE*为一个常量）。该数组存的整数从 0 到*SIZE*,数值互不相同。请实现一个`fill`函数来实现乱序数组：

```c
void fill(int * arr, int length){
    ...
}
```

## Task2

我们来实现第一个排序算法：插入排序。这也是最人性化的排序算法：依次看每个元素，然后在已经排序完成的部分里找到这个元素应该所处的位置。让我们实现一个从小到大的排序函数

```c
void inssort(int* A, int N){
    ...
}
```

### 讨论

我们的实现是插入当前检查的元素吗？为什么要这样实现？

## Task3

我们来实现冒泡（Bubble）算法:

```c
void bubblesort(int* A, int N){
    ...
}
```

### 讨论

冒泡和插入的区别是什么？

## Task4

是不是到现在为止我们实现的都是从小到大的排序？如果我们要做一个从大到小的排序，我们是要把 `>` 和 `<` 都换掉？我们要从头开始修改吗？
让我们尝试使用函数指针来实现升序或者逆序的选择！
实现两个比较函数`ascending`和`descending`:

```c
/** @brief Return True if i < j **/
int ascending(int i, int j){
    ...
} 
/** @brief Return True if i > j **/
int descending(int i, int j){
    ...
}
```

实现一个包含函数指针参数的`inssort`和`bubblesort`:

```c
void inssort(int* A, int N, int (* compare)(int, int)){
    ...
}
void inssort(int* A, int N, int (* compare)(int, int)){
    ...
}
```
