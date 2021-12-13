# Lab 6 - Linked List

## Task 0.0 - 调试宏

我们创建一些宏用来调试。宏是 C 语言的一个工具，用来简化代码的编写工作，我们在这个 Lab 中会经常用到宏这一工具

```c
/** @file debug.h **/
#ifndef _DEBUG_H
#define _DEBUG_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define LOGE(M, ...) fprintf(stderr, "\033[31;1m[ERROR]\033[0m (%s:%d: errno: %d) " M "\n", __FILE__, __LINE__, errno, ##__VA_ARGS__)
#define LOGI(M, ...) fprintf(stderr, "\033[32;1m[INFO]\033[0m (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define CHECK(exp, M, ...) \
        if(!(exp)) { LOGE(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
```

测试代码如下

```c
#include "debug.h"

int main() {
    LOGI("Hello, %s world!", "this");
    LOGE("GoodBye");
    void* ptr = NULL;
    CHECK(ptr, "Pointer is NULL");
    return 0;
error:
    return ENOMEM;
}
```

### 效果

![effect](/uploads/upload_4ecd5119df2b11cccbaff615b058d7dc.png)

### 解释

`#ifndef`C 预处理器可以根据条件判断来忽略一部分代码。这里的`#ifndef`是“如果没有被定义”的意思。它会检查是否已经出现过`_DEBUG_H`这个宏，如果已出现，就跳过这段代码。这样就可以避免重复定义。

有了上面保护该文件的`#ifndef`，我们接着添加`_DEBUG_H`的定义，因此之后任何试图包含此文件的行为，都会由于上面的语句而跳过这段代码。

> 我们也可以将`#ifndef`用于需要的地方

`LOGI("Hello, %s world!", "this");` 这个宏会被展开成

```c
fprintf(stderr, "\033[31;1m[ERROR]\033[0m (%s:%d) " "Hello, %s world!" "\n", __FILE__, __LINE__, "this")
```

-   `stderr`标准错误，是用于输出错误信息的输出流。除此之外还有`stdin`标准输入和`stdout`标准输出，`<stdio.h>`中的`fprintf`可以操作这些流
-   `\033[32;1m` 和 `\033[0m`是特殊控制符号，用于控制在终端输出的字符的颜色
-   `__FILE__`,`__LINE__`代表当前文件的名称和行号
-   `M`被解释成输出的格式
-   `...` 的内容将会添加到后面，作为可变参数来格式化输出

> 可以用`gcc -E`选项验证宏展开的结果

`LOGE("GoodBye");` 这个宏会被展开成

```c
fprintf(__stderrp, "\033[31;1m[ERROR]\033[0m (%s:%d: errno: %d) " "GoodBye" "\n", __FILE__, __LINE__, errno);
```

- `errno` 会被展开成`(*__error())`。这个宏定义在`<errno.h>`中。作为标准库的一部分，它可以获取系统的错误代码。
- 使用了红色作为`ERROR`的告警颜色

有了以上的知识，我们不难看出，`CHECK(exp, M, ...)` 的作用是在`(exp==0)`的时候输出定义好的消息`M`，并且跳转到`error`定义的错误处理块去继续执行

> goto 语句可以用于函数内的跳转。滥用goto语句可能会损害代码可读性，但这里我们利用了goto语句的跳转特性来一次性跳出可能存在的多重循环，并直接执行错误处理。尝试编译并运行下面的代码理解goto

> ```c
> #include <stdio.h>
> int main () {
>     int i = 0;
> 
> restart:
>     printf("Hello, world\n");
>     ++i;
>     if (i < 10) goto restart;
>     return 0;
>   
> }

> `\`符号可以连接多行代码，这允许我们构建复杂的宏

> 试着编写`LOGW`和`LOGD`来输出*Warning*和*Debug*类型的日志

## Task 0.1 - 选择性开启日志输出

利用`#if LOG_LEVEL`语句和`#define LOG_LEVEL` 我们可以控制输出的日志信息

```c
#ifndef _DEBUG_H
#define _DEBUG_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define LEVEL_DISABLE 0
#define LEVEL_ERROR 1
#define LEVEL_WARNING 2
#define LEVEL_INFO 3
#define LEVEL_DEBUG 4

/** Set log level **/
#define LOG_LEVEL LEVEL_DEBUG

#if LOG_LEVEL >= LEVEL_ERROR
#define LOGE(M, ...) fprintf(stderr, "\033[31;1m[ERROR]\033[0m (%s:%d: errno: %d) " M "\n", __FILE__, __LINE__, errno, ##__VA_ARGS__)
#else
#define LOGE(M, ...)
#endif

#if LOG_LEVEL >= LEVEL_WARNING
#define LOGW(M, ...) fprintf(stderr, "\033[33;1m[WARNING]\033[0m (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGW(M, ...)
#endif

#if LOG_LEVEL >= LEVEL_INFO
#define LOGI(M, ...) fprintf(stderr, "\033[32;1m[INFO]\033[0m (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGI(M, ...)
#endif

#if LOG_LEVEL >= LEVEL_DEBUG
#define LOGD(M, ...) fprintf(stderr, "\033[2m[DEBUG] (%s:%d) " M "\n\033[0m", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGD(M, ...)
#endif

#define CHECK(exp, M, ...) \
        if(!(exp)) { LOGE(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
```

可以看到我们设定了0-4五个等级，当`LOG_LEVEL` 被设定成0时，所有的调试记录都会被关闭

> 试一试改变`LOG_LEVEL`

> 想一想，这样有什么好处

## Task 1.0 - Singly Linked List

### 准备

让我们来实现链表。我们的目标是创建一个单向链表。它有一头一尾两个节点用来管理链表

### Task 1.1 - llist.h

起草`llist.h`

一般来说，我们在头文件里声明 API 和相关的数据结构，并在源文件中实现它们。我们创建一个`llist.h`的头文件：

```c
#ifndef _LLIST_H
#define _LLIST_H
#endif
```

我们定义两个错误类型`LLIST_OK`和`LLIST_FAIL`，以及节点结构体`llist_node_t`。注意到`LLIST_DTYPE`指定了节点元素的类型为 int

```c
typedef enum {
    LLIST_OK = 0,
    LLIST_FAIL = -1,
} llist_err_t;

#define LLIST_DTYPE int

typedef struct _llist_node_t {
    struct _llist_node_t* next;
    LLIST_DTYPE data;
} llist_node_t;
```

当然，我们也需要创建一个用于管理这些节点的`llist_t`结构体

```c
typedef struct _llist_t {
    /* data */
    llist_node_t* head;
    llist_node_t* tail;
    llist_node_t* fence;
    size_t len;
} llist_t;
```

我们也许会想要实现这些链表有关的函数

```c
/**
 * @brief Init a llist_t structure
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_init(llist_t* self);

/**
 * @brief Deinit a llist_structure
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_deinit(llist_t* self);

/**
 * @brief Allocate a llist_t structure
 *
 * @return llist_t* The allocated structure.
 */
llist_t* list_create(void);

/**
 * @brief Remove all nodes from list
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_removeall(llist_t* self);

/**
 * @brief Destroy an allocated structure
 *
 * @warning Do not use this function against llist_t on stack
 * @param self
 * @return llist_err_t
 */
llist_err_t list_destroy(llist_t* self);

/**
 * @brief Represent a list to file/pipe
 *
 * @param self
 * @param fp FILE* pointer, e.g. stdio
 * @param fmt format function pointer
 * @return llist_err_t
 */
llist_err_t list_print(llist_t* self, FILE* fp, fp_fmt_fn_t fmt);

/**
 * @brief Append a new node at the end of list
 *
 * @param self
 * @param data
 * @return llist_err_t
 */
llist_err_t list_append(llist_t* self, LLIST_DTYPE data);

/**
 * @brief Find a node that equals to data
 *
 * @param self
 * @param data
 * @return llist_node_t* The node found, NULL for not found
 */
llist_node_t* list_find(llist_t* self, LLIST_DTYPE data);

/**
 * @brief Get item at desired position
 *
 * @param self
 * @param pos
 * @param value_ptr
 * @return llist_node_t* The node found, NULL for incorrect pos
 */
llist_node_t* list_getitem(llist_t* self, size_t pos, LLIST_DTYPE* value_ptr);

/**
 * @brief Insert a node to a given position pos.
 *
 * @param self
 * @param pos
 * @param data
 * @return llist_err_t Status
 */
llist_err_t list_insert(llist_t* self, size_t pos, LLIST_DTYPE data);

/**
 * @brief Extend an list using another list. This will make a copy of all element in the other list
 *
 * @param self
 * @param src
 * @return llist_err_t status
 */
llist_err_t list_extend(llist_t* self, llist_t* src);

/**
 * @brief Remove a node from list
 *
 * @param self
 * @param node_ptr
 * @return llist_err_t status
 */
llist_err_t list_remove_node(llist_t* self, llist_node_t* node_ptr);


/**
 * @brief Remove a node at desired position
 *
 * @param self
 * @param pos
 * @return llist_err_t status
 */
llist_err_t list_remove(llist_t* self, size_t pos);

```

### 任务

完成设计

## Task 1.2 - 链表的创建和销毁

可以注意到，我们为链表的创建和销毁创建了这些函数

```c
llist_t* list_init(void);
llist_t* list_create(void);
llist_err_t list_removeall(llist_t* self);
llist_err_t list_destroy(llist_t* self);
```

这些函数有不同的作用
| 函数 | 作用 |
|----------------|-------------------------------------------------|
| `list_create` | 用`malloc`分配一个节点，并初始化 |
| `list_init` | 初始化一个存在的节点，这个节点不一定是动态分配的 |
| `list_deinit` | 取消初始化一个存在的节点，这个节点的 head 是动态分配的 |
| `list_removeall` | 从一个`llist_t`节点中删除所有的`llist_node`节点 |
| `list_destroy` | 销毁一个用`malloc`分配的节点，和`list_create`成对使用 |

为了格式化输出列表，我们定义了

```c
/**
 * @brief Represent a list to file/pipe
 *
 * @param self
 * @param fp FILE* pointer, e.g. stdio
 * @param fmt format function pointer
 * @return llist_err_t
 */
llist_err_t list_print(llist_t* self, FILE* fp, fp_fmt_fn_t fmt);
```

用来格式化输出链表的每一个元素。该函数接受一个`fp_fmt_fn_t`的函数指针：

```c
typedef int (*fp_fmt_fn_t)(llist_node_t*, FILE*);
```

例如：

```c
iint fp_format_int(llist_node_t* node, FILE * fp) {
    return fprintf(fp, "{\"data\": %d}, ", node->data);
}
```

> `fnprintf`用法和`printf`类似，只是多了参数`fp`,。`fprintf`可以将内容按照格式打印到一个文件指针/管道。例如，`stdout`就是这样一个管道

我们需要实现向链表添加元素的接口

```c
llist_err_t list_append(llist_t* self, LLIST_DTYPE data);
```

可以将`LLIST_DTYPE`类型的元素添加到链表中

### 任务

请同学们于`list.c`中完成`list.h`的相关设计，并让下面的例子跑起来：

```c
#include "llist.h"
#include <stdio.h>
#include "debug.h"

int fp_format_int(llist_node_t* node, FILE * fp) {
    return fprintf(fp, "{\"data\": %d}, ", node->data);
}
void test() {
    llist_t* llist_on_heap = list_create();
    llist_t llist_on_stack = {0};
    list_init(&llist_on_stack);

    list_append(llist_on_heap, 0);
    list_append(llist_on_heap, 1);
    list_append(&llist_on_stack, 0);
    list_append(&llist_on_stack, 1);

    list_print(llist_on_heap, stdout, fp_format_int);

    list_destroy(llist_on_heap);
    llist_on_heap = NULL;
    list_deinit(&llist_on_stack);
    return;
}
int main() {
    test();
    return 0;
}
```

> 当我们`free`一块内存后，一个常见的防止出错的办法是把这个内存的指针变量设制成 NULL。因为重复释放一块内存会出错，而`free(NULL)`不会。

> 使用`valgrind --leak-check=full`检查以确保没有内存泄漏

![valgrind](/uploads/upload_146724e8f46cf4719a0c8b6b7de4f2fe.png)

## Task 1.3 功能函数

以下这些函数的作用不言而喻

```c
llist_node_t* list_find(llist_t* self, LLIST_DTYPE data);
llist_node_t* list_getitem(llist_t* self, size_t pos, LLIST_DTYPE* value_ptr);
llist_err_t list_insert(llist_t* self, size_t pos, LLIST_DTYPE data);
llist_err_t list_extend(llist_t* self, llist_t* src);
llist_err_t list_remove_node(llist_t* self, llist_node_t* node_ptr);
llist_err_t list_remove(llist_t* self, size_t pos);
```

### 任务

在`llist.c`中实现它们

> 你也可以实现别的API，但是基本的增删查改要有

## Task 2.0 - Doubly Linked List

修改前一部分的链表节点定义，增加`prev`成员。

```c
typedef struct _llist_node_t {
    struct _llist_node_t* next;
    struct _llist_node_t* prev;
    LLIST_DTYPE data;
} llist_node_t;
```

### 任务

修改前一部分函数的定义，增加`list_print_reverse`以实现链表的后向便利、打印

## Task 3.0 - 起草

### 准备

让我们来实现链表。我们准备设定一个双向循环链表。

![llist](/uploads/upload_5efaddfccef2aab978a3d5d8396beee2.svg)

> 这也是 Linux 内核中链表的实现方式

使用双向循环链表的好处有：

-   不需要考虑处理特殊的尾节点和头节点，一般的链表这些节点的 next 和 prev 是 NULL
-   使用`ptr = ptr->next`遍历时不会访问空指针
-   可以从两个方向遍历
-   列表的头指针也是尾指针

### 任务

起草`list.h`

```c
typedef enum {
    LLIST_OK = 0,
    LLIST_FAIL = -1,
} llist_err_t;

#define LLIST_DTYPE int

typedef struct _llist_node_t {
    /* data */
    struct _llist_node_t* next;
    struct _llist_node_t* prev;
    LLIST_DTYPE data;
} llist_node_t;

typedef struct _llist_t {
    /* data */
    llist_node_t* head;
    llist_node_t* fence;
    size_t len;
} llist_t;
```

和之前的双向链表没有区别，因此我们需要修改的是链表创建以及添加元素时候的**行为**

### 任务

修改代码，实现双向循环链表

## Task 3.1 - Doubley Linked List with Various Data type

为此，我们需要用`void*`类型的`data`成员和`size_t` 类型的`size`成员来存储存入链表的对象。因此，取出对象时，我们需要判断对象的类型

```c
typedef struct _llist_node_t {
    /* data */
    struct _llist_node_t* next;
    struct _llist_node_t* prev;
    void* data;
    size_t size;
} llist_node_t;
```

为此，我们要重写`NODE_CREATE`和`NODE_DESTORY`这两个宏

```c
#define NODE_CREATE(name, value, size) \
        NODE_ALLOCATE(name); \
        CHECK((name->data) = calloc(1, size), "Cannot allocate data memory") \
        memcpy(name->data, value, size); \
        name->size = size

#define NODE_DESTROY(node_ptr) \
        free(node_ptr->data); \
        node_ptr->data = NULL; \
        free(node_ptr); \
        node_ptr = NULL

```

修改`list_append`, `list_find`, `list_getitem`, `list_insert`的声明

```c
/**
 * @brief Append a new node at the end of list
 *
 * @param self
 * @param data
 * @return llist_err_t
 */
llist_err_t list_append(llist_t* self, const void * data, size_t size);

/**
 * @brief Find a node that equals to data
 *
 * @param self
 * @param data
 * @return llist_node_t* The node found, NULL for not found
 */
llist_node_t* list_find(llist_t* self, const void * data, size_t size);

/**
 * @brief Get item at desired position
 *
 * @param self
 * @param pos
 * @param value_ptr
 * @return llist_node_t* The node found, NULL for incorrect pos
 */
llist_node_t* list_getitem(llist_t* self, size_t pos, void* value_ptr);

/**
 * @brief Insert a node to a given position pos.
 *
 * @param self
 * @param pos
 * @param data
 * @return llist_err_t Status
 */
llist_err_t list_insert(llist_t* self, size_t pos, const void * data, size_t size);
```

并修改相应的实现

## Task 3.2 - Doubley Linked List with Various Data type, another solution

对于一个自定义的结构体`my_struct`，如果我们让其第一个成员为`list_node_t`，那么`my_struct.node`的地址将相等于`my_struct`。我们可以利用这一个特性将链表节点包括含别的结构体中。

运行以下程序并思考`offset_of`和`container_of`工作的机制

```c
#include <stdio.h>
#include "debug.h"

#define offset_of(type, member) ((size_t) &((type *)0)->member)

#define container_of(ptr, type, member) ({ \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)( (char *)(ptr) - offset_of(type ,member));})

typedef struct _llist_node_t {
    /* data */
    struct _llist_node_t* next;
    struct _llist_node_t* prev;
    size_t len;
} llist_node_t;

typedef llist_node_t llist_head_t;

typedef struct _student_t {
    llist_head_t head;
    char* name;
    int id;
} student_t;

typedef struct _teacher_t {
    char* name;
    int id;
    llist_head_t head;
} teacher_t;

int main() {
    student_t stu;
    LOGI("&stu=%p", &stu);
    LOGI("&stu->head=%p", &stu.head);

    teacher_t tch;
    LOGI("&tch=%p", &tch);
    LOGI("&tch->head=%p", &tch.head);
    LOGI("&container_of(tch->head, teacher_t, head)=%p", container_of(&tch.head, teacher_t, head));
    return 0;
}
```

---

## Macros explained

### 1.1

```c
#define NODE_ALLOCATE(name) \
        llist_node_t * (name) = NULL ; \
        CHECK((name) = calloc(1, sizeof(llist_node_t)), "Cannot allocate memory")
```

这个宏简化了节点的内存分配过程。它将定义节点指针，申请内存并检查申请结果，把申请到的内存地址用节点指针保存合并成了一条宏指令。

```c
#define NODE_CREATE(name, value) \
        NODE_ALLOCATE(name); \
        name->data = value
```

这个宏是`NODE_ALLOCATE(name)`和`name->data = value`的结合，用于创建节点并给节点赋值。

```c
#define NODE_COPY(dest, src) \
        NODE_ALLOCATE(dest) \
        memcpy(dest, src, sizeof(llist_node_t))
```

这个宏将`src`节点拷贝到 dest 节点，`dest`节点是新分配的

```c
#define NODE_DESTROY(node_ptr) \
        free(node_ptr); \
        node_ptr = NULL
```

这个宏可以释放一个节点，并自动将指向节点的指针设成 NULL

```c
#define NODE_LINK(slow, fast) slow->next = fast; fast->prev = slow
```

这个宏可以连接两个节点

> 这里也可以加上判断`slow`,`fast`节点非空的语句

```c
#define NODE_NEXT(node_ptr) node_ptr = (node_ptr==NULL)?NULL:node_ptr->next
```

这个宏可以将`node_ptr`修改成`node_ptr->next`。这里进行了非空的判断

```c
#define NODE_NEXT_N(node, n) \
        for (size_t idx = 0; idx < n; ++idx, NODE_NEXT(node)){}
```

这个宏连续进行了`n`次`NODE_NEXT`。注意这里for语句的第三部分并排写了两道语句`++idx`, `NODE_NEXT(node)`，这样是合法的

```c
#define NODE_PREV(node_ptr) node_ptr = (node_ptr==NULL)?NULL:node_ptr->prev
```

类比`NODE_NEXT`

```c
#define NODE_PREV_N(node, n) \
        for (size_t idx = 0; idx < n; ++idx, NODE_PREV(node)){}
```

类比`NODE_NEXT_N`

```c
#define LLIST_INIT(name) \
        llist_t name = {0}; \
        list_init(&name)
```

定义并初始化一个llist，这个llist创建在栈上，因此需要在函数退出前调用`list_deinit`来释放额外的head节点的内存。

```c
#define LLIST_ALLOCATE(name) \
        llist_t* name = calloc(1, sizeof(llist_t)); \
        CHECK(name, "Cannot allocate memory")
```

类比`NODE_ALLOCATE`

```c
#define LLIST_CREATE(name) \
        llist_t * name = list_create(); \
```

类比`NODE_CREATE`

```c
#define LLIST_DESTROY(list_ptr) \
        list_destroy(list_ptr); \
        list_ptr = NULL
```

类比`NODE_DESTORY`

```c
#define list_for_each(item, self) \
        for (llist_node_t* item = self->head->next, *prefetch = item->next; item != self->head; item = prefetch, NODE_NEXT(prefetch))
```

展开成for语句，遍历节点。这里用到了prefetch变量来预先读取循环变量item的next成员，因此可以在循环中删除next成员也不会出错

```c
#define CHECK_VALID_LIST(self) CHECK(self, "Invalid list")
```

检查`self`是否为NULL

### 1.2

```c
#define CHECK_INDEX(self, pos) CHECK(!((pos < 0) || (pos >= self->len)), "Index out of range")
```

检查pos是否超过llist的上下界

```c
#define CHECK_LIST(self, pos) CHECK_INDEX(self, pos); CHECK_VALID_LIST(self)
```

`CHECK_INDEX`和`CHECK_VALID_LIST`的组合

```c
#define LIST_IS_EMPTY(list_ptr) (list_ptr->head->next == list_ptr->head)
```

判断链表是否空

```c
#define LIST_RESET_FENCE(self) \
    self->fence = self->head->next;
```

重设`self->fence`为`self->head->next`

```c
#define LIST_NEXT(self) NODE_NEXT(self->fence)
```

调用`NODE_NEXT`修改`self->fence`

```c
#define LIST_NEXT_N(self, n) NODE_NEXT_N(self->fence, n)
```

调用`NODE_NEXT_N`修改`self->fence`

```c
#define LIST_PREV(self) NODE_PREV(self->fence)
```

类比`LIST_NEXT`

```c
#define LIST_PREV_N(self) NODE_PREV_N(self->fence, n)
```

类比`LIST_NEXT_N`

```c
#define ADD_STRING(str, max_len, cnt, ...) \
    cnt += snprintf(str + cnt, max_len - cnt, __VA_ARGS__)
```

将一些格式化的字符串添加到目标字符串str的尾部，cnt是计数器，max_len是目标的最大长度

```c
#define ADD_ITEM(str, max_len, cnt, item, fmt) \
    cnt += fmt(item, str + cnt, max_len - cnt)
```

类比`ADD_STRING`，只不过调用的是fmt函数

### GNUC

```c
#if defined(__GNUC__)
#define __LIST_HAVE_TYPEOF 1
#endif

#ifndef container_of
#ifdef __LIST_HAVE_TYPEOF
#define container_of(ptr, type, member)                            \
    __extension__({                                                \
        const __typeof__(((type *) 0)->member) *__pmember = (ptr); \
        (type *) ((char *) __pmember - offsetof(type, member));    \
    })
#else
#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) -offsetof(type, member)))
#endif
```
