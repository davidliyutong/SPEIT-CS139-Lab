#include "llist.h"
#include <stdio.h>
#include "debug.h"

int format_int(llist_node_t* node, char* str, size_t max_len) {
    return snprintf(str, max_len, "{\"data\": %d}, ", node->data);
}

int fp_format_int(llist_node_t* node, FILE * fp) {
    return fprintf(fp, "{\"data\": %d}, ", node->data);
}

int main() {
    LLIST_CREATE(x);
    list_append(x, 9);
    list_append(x, 10);
    list_remove(x, 0);
    list_remove(x, 0);
    list_remove(x, 0);

    list_insert(x, 0, 8);
    list_insert(x, 0, 7);
    list_removeall(x);

    list_insert(x, 0, 0);
    list_append(x, 3);
    list_insert(x, 1, 1);
    list_insert(x, 2, 2);
    llist_node_t* node_ptr;
    node_ptr = list_find(x, 2);
    node_ptr = list_getitem(x, 1, NULL);
    LLIST_DTYPE val;
    node_ptr = list_getitem(x, 2, &val);
    node_ptr = list_getitem(x, 4, &val);

    list_remove(x, 1);
    list_remove(x, 1);

    char buf[128] = { 0 };
    list_repr(x, buf, sizeof(buf), format_int);
    printf("%s", buf);

    list_print(x, stdout, fp_format_int);

    LOGI("%s", "Hello, world!");
    LLIST_DESTROY(x);
    return 0;
}