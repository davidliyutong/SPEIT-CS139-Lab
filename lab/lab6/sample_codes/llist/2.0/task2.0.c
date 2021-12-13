#include "llist.h"
#include <stdio.h>
#include "debug.h"

int fp_format_int(llist_node_t* node, FILE* fp) {
    return fprintf(fp, "{\"data\": %d}, ", *(int*)(node->data));
}

int fp_format_double(llist_node_t* node, FILE* fp) {
    return fprintf(fp, "{\"data\": %lf}, ", *(double*)(node->data));
}

int fp_format_char_ptr(llist_node_t* node, FILE* fp) {
    return fprintf(fp, "{\"data\": \"%s\"}, ", *(char**)(node->data));
}

int fp_format_char_array(llist_node_t* node, FILE* fp) {
    return fprintf(fp, "{\"data\": \"%s\"}, ", (char*)(node->data));
}

int main() {
    LLIST_CREATE(x);

    LIST_APPEND(x, int, 9);
    LIST_APPEND(x, int, 10);
    LIST_INSERT(x, 0, int, 8);
    LIST_INSERT(x, 0, int, 7);
    list_print(x, stdout, fp_format_int);
    list_removeall(x);


    LIST_INSERT(x, 0, double, 1.5);
    LIST_INSERT(x, 0, double, -1.5);
    LIST_INSERT(x, 0, double, 2.5);
    list_print(x, stdout, fp_format_double);
    list_remove(x, 2);
    list_print(x, stdout, fp_format_double);
    list_removeall(x);


    LIST_INSERT(x, 0, char*, "helloworld");
    LIST_INSERT(x, 0, char*, "goodbye");
    LIST_APPEND(x, char*, "bonjour");
    list_print(x, stdout, fp_format_char_ptr);


    llist_node_t* node_ptr;
    LIST_FIND(x, char*, "helloworld", node_ptr);
    LOGI("node_ptr: %p", node_ptr);
    fp_format_char_ptr(node_ptr, stdout);
    LIST_FIND(x, char*, "bye", node_ptr);
    LOGI("node_ptr: %p", node_ptr);

    printf("\n--------\n");
    char* val = 0;
    node_ptr = list_getitem(x, 1, &val);
    LOGI("node_ptr: %p", node_ptr);
    fp_format_char_ptr(node_ptr, stdout);
    printf("%s\n", val);
    list_removeall(x);


    char buf[128] = "BufBufBuf";
    list_append(x, buf, strlen(buf) + 1);
    // memcpy(buf, "BlahBlahBlah", 13);
    // list_append(x, buf, strlen(buf));
    list_print(x, stdout, fp_format_char_array);

    LLIST_DESTROY(x);
    return 0;
}