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