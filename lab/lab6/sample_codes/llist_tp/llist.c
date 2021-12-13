#include "llist.h"

/**
 * @brief Init a llist_t structure
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_init(llist_t* self) {
    self->head = calloc(1, sizeof(llist_node_t));
    self->tail = self->head;
    self->len = 0;
    self->fence = self->head;
    return LLIST_OK;
}

/**
 * @brief Allocate a llist_t structure
 *
 * @return llist_t* The allocated structure.
 */
llist_t* list_create(void) {
    llist_t* self = calloc(1, sizeof(llist_t));
    list_init(self);
    return self;
}

/**
 * @brief Remove all nodes from list
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_removeall(llist_t* self) {
   for (llist_node_t* item = self->head->next, *prefetch = item->next;
         item != NULL;
         item = prefetch, prefetch = (prefetch != NULL)?(prefetch->next):NULL) {
             // llist_node_t * tmp = item->next;
        free(item);
        // item = tmp;
    }
    self->head->next = NULL;
}

/**
 * @brief Deinit a llist_structure
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_deinit(llist_t* self) {
    list_removeall(self);
    self->len = 0;
    self->fence = NULL;
    free(self->head);
    return LLIST_OK;
}

/**
 * @brief Destroy an allocated structure
 *
 * @warning Do not use this function against llist_t on stack
 * @param self
 * @return llist_err_t
 */
llist_err_t list_destroy(llist_t* self) {
    list_deinit(self);
    free(self);
    return LLIST_OK;
}

/**
 * @brief Represent a list to file/pipe
 *
 * @param self
 * @param fp FILE* pointer, e.g. stdio
 * @param fmt format function pointer
 * @return llist_err_t
 */
llist_err_t list_print(llist_t* self, FILE* fp, fp_fmt_fn_t fmt) {
    for (llist_node_t* item = self->head->next, *prefetch = item->next;
         item != NULL;
         item = prefetch, prefetch = (prefetch != NULL)?(prefetch->next):NULL) {
        fmt(item, stdout);
    }
    return LLIST_OK;
}

/**
 * @brief Append a new node at the end of list
 *
 * @param self
 * @param data
 * @return llist_err_t
 */
llist_err_t list_append(llist_t* self, LLIST_DTYPE data) {
    llist_node_t * node = calloc(1, sizeof(llist_node_t));
    node->data = data;
    node->next = self->tail->next;
    self->tail->next = node;
    self->tail = node;
    return LLIST_OK;
}

/**
 * @brief Find a node that equals to data
 *
 * @param self
 * @param data
 * @return llist_node_t* The node found, NULL for not found
 */
llist_node_t* list_find(llist_t* self, LLIST_DTYPE data) {}

/**
 * @brief Get item at desired position
 *
 * @param self
 * @param pos
 * @param value_ptr
 * @return llist_node_t* The node found, NULL for incorrect pos
 */
llist_node_t* list_getitem(llist_t* self, size_t pos, LLIST_DTYPE* value_ptr) {}

/**
 * @brief Insert a node to a given position pos.
 *
 * @param self
 * @param pos
 * @param data
 * @return llist_err_t Status
 */
llist_err_t list_insert(llist_t* self, size_t pos, LLIST_DTYPE data) {}

/**
 * @brief Extend an list using another list. This will make a copy of all element in the other list
 *
 * @param self
 * @param src
 * @return llist_err_t status
 */
llist_err_t list_extend(llist_t* self, llist_t* src) {}

/**
 * @brief Remove a node from list
 *
 * @param self
 * @param node_ptr
 * @return llist_err_t status
 */
llist_err_t list_remove_node(llist_t* self, llist_node_t* node_ptr) {}


/**
 * @brief Remove a node at desired position
 *
 * @param self
 * @param pos
 * @return llist_err_t status
 */
llist_err_t list_remove(llist_t* self, size_t pos) {}