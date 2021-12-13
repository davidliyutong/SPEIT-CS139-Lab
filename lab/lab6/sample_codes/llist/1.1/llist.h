#ifndef _LLIST_H
#define _LLIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"

typedef enum {
    LLIST_OK = 0,
    LLIST_FAIL = -1,
} llist_err_t;

#define LLIST_DTYPE int
typedef struct _llist_node_t {
    /* data */
    struct _llist_node_t* next;
    struct _llist_node_t* prev;
    LLIST_DTYPE data;
} llist_node_t;

#define NODE_ALLOCATE(name) \
        llist_node_t * (name) = NULL ; \
        CHECK((name) = (llist_node_t * )calloc(1, sizeof(llist_node_t)), "Cannot allocate memory")

#define NODE_CREATE(name, value) \
        NODE_ALLOCATE(name); \
        name->data = value

#define NODE_COPY(dest, src) \
        NODE_ALLOCATE(dest) \
        memcpy(dest, src, sizeof(llist_node_t))

#define NODE_DESTROY(node_ptr) \
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
llist_err_t list_append(llist_t* self, LLIST_DTYPE data);

/**
 * @brief Find a node that equals to data
 *
 * @param self
 * @param data
 * @return llist_node_t* The node found, NULL for not found
 */
llist_node_t* list_find(llist_t* self, LLIST_DTYPE data);

/**
 * @brief Get item at desired position
 *
 * @param self
 * @param pos
 * @param value_ptr
 * @return llist_node_t* The node found, NULL for incorrect pos
 */
llist_node_t* list_getitem(llist_t* self, size_t pos, LLIST_DTYPE* value_ptr);

/**
 * @brief Insert a node to a given position pos.
 *
 * @param self
 * @param pos
 * @param data
 * @return llist_err_t Status
 */
llist_err_t list_insert(llist_t* self, size_t pos, LLIST_DTYPE data);

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

#define list_for_each(item, self) \
        for (llist_node_t* item = self->head->next, *prefetch = item->next; item != self->head; item = prefetch, NODE_NEXT(prefetch))

#define CHECK_VALID_LIST(self) CHECK(self, "Invalid list")


#endif