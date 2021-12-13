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


llist_node_t* list_find(llist_t* self, LLIST_DTYPE data) {
    CHECK_VALID_LIST(self);
    list_for_each(item, self) {
        if (item->data == data) return item;
    }
error:
    return NULL;
}

llist_node_t* list_getitem(llist_t* self, size_t pos, LLIST_DTYPE* value_ptr) {
    CHECK_LIST(self, pos);
    LIST_RESET_FENCE(self);
    LIST_NEXT_N(self, pos);

    if (value_ptr != NULL) {
        *value_ptr = self->fence->data;
    }
    return self->fence;
error:
    return NULL;
}

llist_err_t list_insert(llist_t* self, size_t pos, LLIST_DTYPE data) {
    NODE_CREATE(new_node, data);
    if (LIST_IS_EMPTY(self)) {
        NODE_LINK(self->head->prev, new_node);
        NODE_LINK(new_node, self->head);
    } else {
        CHECK_LIST(self, pos);

        LIST_RESET_FENCE(self);
        LIST_NEXT_N(self, pos);

        NODE_LINK(self->fence->prev, new_node);
        NODE_LINK(new_node, self->fence);
    }
    ++self->len;
    return LLIST_OK;
error:
    if (new_node != NULL) free(new_node);
    return LLIST_FAIL;
}

llist_err_t list_extend(llist_t* self, llist_t* src) {
    CHECK_VALID_LIST(self);
    CHECK(!(self == src), "Same list");
    list_for_each(item, src) {
        NODE_COPY(item_copy, item);

        NODE_LINK(self->head->prev, item_copy);
        NODE_LINK(item_copy, self->head);

        ++self->len;
        continue;
error:
        if (item_copy != NULL) free(item_copy);
        return LLIST_FAIL;
    }
    return LLIST_OK;
}

llist_err_t list_remove_node(llist_t* self, llist_node_t* node_ptr) {
    CHECK(node_ptr, "NULL ptr");
    CHECK_VALID_LIST(self);

    NODE_LINK(node_ptr->prev, node_ptr->next);
    NODE_DESTROY(node_ptr);

    --self->len;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_remove(llist_t* self, size_t pos) {
    CHECK_LIST(self, pos);
    LIST_RESET_FENCE(self);
    LIST_NEXT_N(self, pos);

    NODE_LINK(self->fence->prev, self->fence->next);
    NODE_DESTROY(self->fence);
    --self->len;
    return LLIST_OK;
error:
    return LLIST_FAIL;
}

llist_err_t list_repr(llist_t* self, char* buf, size_t buf_len, char_fmt_fn_t fmt) {
    CHECK_VALID_LIST(self);
    size_t written = 0;
    ADD_STRING(buf, buf_len, written, "[");
    list_for_each(item, self) {
        ADD_ITEM(buf, buf_len, written, item, fmt);
        CHECK((buf_len > written), "Buffer is full");
    }
    ADD_STRING(buf, buf_len, written, "]\n");
    return LLIST_OK;
error:
    return LLIST_FAIL;
}
