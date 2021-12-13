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
