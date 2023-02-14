# Introduction to GDB

## 调试策略

调试有一定的策略可以采取

1. 创建一个空间（可以是一张纸，一个文本文档，也可以是脑海里的一块区域）来记录想法、bug和问题
2. 写下你打算修复的bug或者打算探寻点机制，以及可能的产生原因。
3. 对于每个原因，写下你所认为的，问题来源的函数或文件，或者仅仅写下你不知道。
4. 现在启动调试，在可能的问题处那里设置断点。
5. 对于每一处断点，确认其是否与问题产生有关
6. 如果它不是真正原因，则在标记它为不是，以及理由。移到下一个可能的原因

这样我们就完成了许多"假设-验证"循环。这里以gdb为例为大家演示

在Ubuntu上，可以通过`sudo apt-get install gdb`安装GDB

也为大家提供了`cs50/ide`在线编程服务。该服务已经安装好GDB

使用GDB主要需要完成如下步骤

1. 使用`-g`选项编译可执行文件
2. 设置断点
3. 执行程序，在断点停留，然后进行其他操作

## GDB 指令一览

- `help <COMMAND>` 获得某一个命令的简单帮助。

- `break file.c:(line|function)` 在你希望暂停的地方设置断点。你可以提供行号或者函数名称。

- `run <ARGS>` 运行程序，使用`ARGS`作为命令行参数。

- `cont` 继续执行程序，直到断点或错误。

- `step` 单步执行代码，但是会进入函数内部。使用它来跟踪函数内部，来观察它做了什么。

- `next` 就像是step，但是他会运行函数并步过它们。

- `backtrace` 执行“跟踪回溯”，它会转储函数到当前执行点的执行轨迹。

- `set var X = Y` 将变量X设置为Y。

- `print X` 打印出X的值，你通常可以使用C的语法来访问指针的值或者结构体的内容。

- `回车键` 重复上一条命令。

- `quit`

> GDB 命令必须在启动gdb的状态下执行。此时，终端提示符会变成`(gdb)`

## 举个🌰


```c
#include <stdio.h>
int some_function(char * param1, int param2){
    printf("do %s for %d days\n", param1, param2);
    return -1;
};
int main(int argc, char ** argv) {
    int (*p)(char*, int);
    p = some_function;
    int ret = p("work\n", 996);
    printf(ret<0?"undingable\n":"dingable\n");
    return 0;
}
```

观看视频 [Introduction to GDB](https://www.bilibili.com/video/BV1HL4y1q7ue/)

### 更多资源

[GDB调试入门指南](https://zhuanlan.zhihu.com/p/74897601)
[练习31：代码调试](https://wizardforcel.gitbooks.io/lcthw/content/ex31.html)
[练习18：函数指针](https://wizardforcel.gitbooks.io/lcthw/content/ex18.html)
