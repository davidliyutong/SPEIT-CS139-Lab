#include "llist.h"
#include <memory.h>
#include <stdlib.h>
#include <errno.h>
#include "debug.h"

llist_err_t list_init(llist_head_t* self) {
    self->prev = self->next = self;
    self->len = 0;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_head_t* list_create() {
    LLIST_ALLOCATE(list_ptr);
    list_init(list_ptr);
    return list_ptr;
error:
    return NULL;
}

llist_err_t list_removeall(llist_head_t* self, size_t offset) {
    CHECK_VALID_LIST(self);
    list_for_each(item, self) {
        void* entry = (char*)((char*)item - offset);
        NODE_DESTROY(entry);
    }
    list_init(self);
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_destroy(llist_head_t* self, size_t offset) {
    CHECK_VALID_LIST(self);
    CHECK((list_removeall(self, offset) == LLIST_OK), "Removeall failed");
    free(self);
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_print(llist_head_t* self, FILE* fp, fp_fmt_fn_t fmt) {
    CHECK_VALID_LIST(self);
    list_for_each(item, self) {
        fmt(item, fp);
    }
    fprintf(fp, "\n");
    return LLIST_OK;
error:
    return LLIST_FAIL;

}

llist_err_t list_append(llist_head_t* self, llist_head_t* node, size_t offset, size_t size) {
    CHECK(node, "NULL ptr");

    llist_head_t* node_copy = NODE_COPY(node, offset, size);

    NODE_LINK(self->prev, node_copy);
    NODE_LINK(node_copy, self);
    ++self->len;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_extend(llist_head_t* self, llist_head_t* src, size_t offset, size_t size) {
    CHECK_VALID_LIST(self);
    CHECK(!(self == src), "Same list");
    list_for_each(item, src) {
        llist_head_t* item_copy = NODE_COPY(item, offset, size);

        NODE_LINK(self->prev, item_copy);
        NODE_LINK(item_copy, self);

        ++self->len;
        continue;

    }
    return LLIST_OK;
error:
    return LLIST_FAIL;
}


llist_err_t list_remove_node(llist_head_t* self, llist_node_t* node, size_t offset) {
    CHECK(node, "NULL ptr");
    CHECK_VALID_LIST(self);

    NODE_LINK(node->prev, node->next);
    void* entry = (char*)((char*)node - offset);
    NODE_DESTROY(entry);

    --self->len;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}