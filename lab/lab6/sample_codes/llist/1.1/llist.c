#include "llist.h"
#include <memory.h>
#include <stdlib.h>
#include <errno.h>
#include "debug.h"

llist_err_t list_init(llist_t* self) {
    CHECK(!(self->head), "List allready inited");
    NODE_ALLOCATE(head);
    head->next = head->prev = head;
    self->fence = self->head = head;
    self->len = 0;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_deinit(llist_t* self) {
    CHECK((list_removeall(self)==LLIST_OK), "Removeall failed");
    NODE_DESTROY(self->head);
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_t* list_create() {
    LLIST_ALLOCATE(list_ptr);
    list_init(list_ptr);
    return list_ptr;
error:
    return NULL;
}

#define list_for_each(item, self) \
        for (llist_node_t* item = self->head->next, *prefetch = item->next; item != self->head; item = prefetch, NODE_NEXT(prefetch))

llist_err_t list_removeall(llist_t* self) {
    CHECK_VALID_LIST(self);
    list_for_each(item, self) {
        NODE_DESTROY(item);
    }
    self->fence = self->head->next = self->head->prev = self->head;
    self->len = 0;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_destroy(llist_t* self) {
    CHECK_VALID_LIST(self);
    CHECK((list_removeall(self)==LLIST_OK), "Removeall failed");
    CHECK((list_deinit(self)==LLIST_OK), "Deinit failed");
    free(self);
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_print(llist_t* self, FILE* fp, fp_fmt_fn_t fmt) {
    CHECK_VALID_LIST(self);
    list_for_each(item, self) {
        fmt(item, fp);
    }
    fprintf(fp, "\n");
    return LLIST_OK;
error:
    return LLIST_FAIL;

}

llist_err_t list_append(llist_t* self, LLIST_DTYPE data) {
    NODE_CREATE(new_node, data);

    NODE_LINK(self->head->prev, new_node);
    NODE_LINK(new_node, self->head);

    ++self->len;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}