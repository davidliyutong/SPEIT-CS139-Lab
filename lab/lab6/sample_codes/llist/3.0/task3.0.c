#include "llist.h"
#include <stdio.h>
#include "debug.h"


typedef struct _student_t {
    llist_head_t head;
    char* name;
    int id;
} student_t;

#define NEW_NODE(type, name, ...) type name = {.head=(llist_node_t *)&name, __VA_ARGS__}

int fp_format_student(llist_node_t* node, FILE* fp) {
    student_t* entry = container_of(node, student_t, head);
    return fprintf(fp, "{\"name\": \"%s\", \"name\": %d}, ", entry->name, entry->id);
}


int main() {
    NEW_NODE(student_t, st1, .name = "alice", .id = 10);
    NEW_NODE(student_t, st2, .name = "bob", .id = 20);
    NEW_NODE(student_t, st3, .name = "charlie", .id = 30);
    NEW_NODE(student_t, st4, .name = "dave", .id = 40);
    NEW_NODE(student_t, st5, .name = "eric", .id = 50);

    LLIST_CREATE(student_list);
    LLIST_APPEND(student_list, st1, head);
    LLIST_APPEND(student_list, st2, head);
    LLIST_APPEND(student_list, st3, head);
    LLIST_APPEND(student_list, st4, head);
    list_print(student_list, stdout, fp_format_student);

    llist_node_t * item = LLIST_GET_ITEM(student_list, 1);
    LLIST_REMOVE_NODE(student_list, item, student_t, head);
    list_print(student_list, stdout, fp_format_student);

    LLIST_CREATE(student_list_dup);
    LLIST_EXTEND(student_list_dup, student_list, student_t, head);
    list_print(student_list_dup, stdout, fp_format_student);


    LLIST_DESTROY(student_list, student_t, head);
    LLIST_DESTROY(student_list_dup, student_t, head);
    return 0;
}