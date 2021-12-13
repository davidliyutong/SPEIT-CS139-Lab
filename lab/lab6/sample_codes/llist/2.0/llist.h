#ifndef _LLIST_H
#define _LLIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"

typedef enum {
    LLIST_OK = 0,
    LLIST_FAIL = -1,
} llist_err_t;

typedef struct _llist_node_t {
    /* data */
    struct _llist_node_t* next;
    struct _llist_node_t* prev;
    void* data;
    size_t size;
} llist_node_t;

#define NODE_ALLOCATE(name) \
        llist_node_t * (name) = NULL ; \
        CHECK((name) = (llist_node_t *)calloc(1, sizeof(llist_node_t)), "Cannot allocate memory")

#define NODE_CREATE(name, value, size) \
        NODE_ALLOCATE(name); \
        CHECK((name->data) = calloc(1, size), "Cannot allocate data memory") \
        memcpy(name->data, value, size); \
        name->size = size

#define NODE_COPY(dest, src) \
        NODE_ALLOCATE(dest) \
        memcpy(dest, src, sizeof(llist_node_t))

#define NODE_DESTROY(node_ptr) \
        free(node_ptr->data); \
        node_ptr->data = NULL; \
        free(node_ptr); \
        node_ptr = NULL

#define NODE_LINK(slow, fast) slow->next = fast; fast->prev = slow

#define NODE_NEXT(node_ptr) node_ptr = (node_ptr==NULL)?NULL:node_ptr->next

#define NODE_NEXT_N(node, n) \
        for (size_t idx = 0; idx < n; ++idx, NODE_NEXT(node)){}

#define NODE_PREV(node_ptr) node_ptr = (node_ptr==NULL)?NULL:node_ptr->prev

#define NODE_PREV_N(node, n) \
        for (size_t idx = 0; idx < n; ++idx, NODE_PREV(node)){}


typedef struct _llist_t {
    /* data */
    llist_node_t* head;
    llist_node_t* fence;
    size_t len;
} llist_t;

/**
 * @brief Format a node (char buffer)
 *
 */
typedef int (*char_fmt_fn_t)(llist_node_t*, char*, size_t);

/**
 * @brief Format a node (file/pipe)
 *
 */
typedef int (*fp_fmt_fn_t)(llist_node_t*, FILE*);


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

/**
 * @brief Represent a list to buffer
 *
 * @param self
 * @param buf char array buffer
 * @param buf_len length of buffer
 * @param fmt function to format each node
 * @return llist_err_t status
 */
llist_err_t list_repr(llist_t* self, char* buf, size_t buf_len, char_fmt_fn_t fmt);

#define LLIST_INIT(name) \
        llist_t name = {0}; \
        list_init(&name)

#define LLIST_ALLOCATE(name) \
        llist_t* name = (llist_t*)calloc(1, sizeof(llist_t)); \
        CHECK(name, "Cannot allocate memory")

#define LLIST_CREATE(name) \
        llist_t * name = list_create(); \

#define LLIST_DESTROY(list_ptr) \
        list_destroy(list_ptr); \
        list_ptr = NULL

#define CHECK_VALID_LIST(self) CHECK(self, "Invalid list")
#define CHECK_INDEX(self, pos) CHECK(!((pos < 0) || (pos >= self->len)), "Index out of range")
#define CHECK_LIST(self, pos) CHECK_INDEX(self, pos); CHECK_VALID_LIST(self)

#define LIST_IS_EMPTY(list_ptr) (list_ptr->head->next == list_ptr->head)

#define LIST_RESET_FENCE(self) \
    self->fence = self->head->next;
#define LIST_NEXT(self) NODE_NEXT(self->fence)
#define LIST_NEXT_N(self, n) NODE_NEXT_N(self->fence, n)
#define LIST_PREV(self) NODE_PREV(self->fence)
#define LIST_PREV_N(self) NODE_PREV_N(self->fence, n)


#define LIST_APPEND_VAR(self, var) list_append(self, &var, sizeof(var))
#define LIST_APPEND(self, type, value) \
        { \
            const type var = value; \
            LIST_APPEND_VAR(self, var); \
        }


#define LIST_INSERT_VAR(self, pos, var) list_insert(self, pos, &var, sizeof(var))
#define LIST_INSERT(self, pos, type, value) \
        { \
            const type var = value; \
            LIST_INSERT_VAR(self, pos, var); \
        }

#define LIST_FIND_VAR(self, pos, var) list_find(self, &var, sizeof(var))
#define LIST_FIND(self, type, value, res) \
        { \
            const type var = value; \
            res = LIST_FIND_VAR(self, pos, var); \
        }


#define ADD_STRING(str, max_len, cnt, ...) \
    cnt += snprintf(str + cnt, max_len - cnt, __VA_ARGS__)

#define ADD_ITEM(str, max_len, cnt, item, fmt) \
    cnt += fmt(item, str + cnt, max_len - cnt)

#endif