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
    size_t len;
} llist_node_t;

typedef llist_node_t llist_head_t;

#define NODE_ALLOCATE(name) \
        llist_node_t * (name) = NULL ; \
        CHECK((name) = (llist_node_t *)calloc(1, sizeof(llist_node_t)), "Cannot allocate memory")

#define NODE_DESTROY(node_ptr) \
        free(node_ptr); \
        node_ptr = NULL

#define NODE_COPY(src, offset, size) \
    ({ \
        void* entry = (void*)((char*)src - offset); \
        void* entry_copy = calloc(1, size); \
        memcpy(entry_copy, entry, size); \
        llist_head_t* dest = (llist_head_t*)((char*)entry_copy + offset); \
        dest; \
    })

#define NODE_LINK(slow, fast) slow->next = fast; fast->prev = slow

#define NODE_NEXT(node_ptr) node_ptr = (node_ptr==NULL)?NULL:node_ptr->next

#define NODE_NEXT_N(node, n) \
        for (size_t idx = 0; idx < n; ++idx, NODE_NEXT(node)){}

#define NODE_PREV(node_ptr) node_ptr = (node_ptr==NULL)?NULL:node_ptr->prev

#define NODE_PREV_N(node, n) \
        for (size_t idx = 0; idx < n; ++idx, NODE_PREV(node)){}

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
 * @brief Init a llist_head_t structure
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_init(llist_head_t* self);

/**
 * @brief Deinit a llist_structure
 *
 * @param self
 * @return llist_err_t status
 */
llist_err_t list_deinit(llist_head_t* self);

/**
 * @brief Allocate a llist_head_t structure
 *
 * @return llist_head_t* The allocated structure.
 */
llist_head_t* list_create(void);

/**
 * @brief Remove all nodes from list
 *
 * @param self
 * @param offset
 * @return llist_err_t status
 */
llist_err_t list_removeall(llist_head_t* self, size_t offset);

/**
 * @brief Destroy an allocated structure
 *
 * @warning Do not use this function against llist_head_t on stack
 * @param self
 * @param offset
 * @return llist_err_t
 */
llist_err_t list_destroy(llist_head_t* self, size_t offset);

/**
 * @brief Represent a list to file/pipe
 *
 * @param self
 * @param fp FILE* pointer, e.g. stdio
 * @param fmt format function pointer
 * @return llist_err_t
 */
llist_err_t list_print(llist_head_t* self, FILE* fp, fp_fmt_fn_t fmt);

/**
 * @brief Append a new node at the end of list
 *
 * @param self
 * @param data
 * @param offset
 * @param size
 * @return llist_err_t
 */
llist_err_t list_append(llist_head_t* self, llist_head_t* node, size_t offset, size_t size);

/**
 * @brief Extend an list using another list. This will make a copy of all element in the other list
 *
 * @param self
 * @param src
 * @param offset
 * @param size
 * @return llist_err_t status
 */
llist_err_t list_extend(llist_head_t* self, llist_head_t* src, size_t offset, size_t size);

/**
 * @brief Remove a node from list
 *
 * @param self
 * @param node
 *  * @param offset
 * @return llist_err_t status
 */
llist_err_t list_remove_node(llist_head_t* self, llist_node_t* node, size_t offset);


#define LLIST_INIT(name) \
        llist_head_t name; \
        list_init(&name);

#define LLIST_ALLOCATE(name) \
        llist_head_t* name = (llist_head_t*)calloc(1, sizeof(llist_head_t)); \
        CHECK(name, "Cannot allocate memory")

#define LLIST_CREATE(name) \
        llist_head_t * name = list_create(); \

#define LLIST_DESTROY(list_ptr, type, member) \
        list_destroy(list_ptr, offset_of(type, member)); \
        list_ptr = NULL

#define list_for_each(item, self) \
        for (llist_node_t* item = self->next, *prefetch = item->next; item != self; item = prefetch, NODE_NEXT(prefetch))

#define offset_of(type, member) ((size_t) &((type *)0)->member)

#define container_of(ptr, type, member) ({ \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)( (char *)(ptr) - offset_of(type ,member));})

#define list_entry(node, type, member) container_of(node, type, member)


#define list_for_each_entry(item, self, member) \
        for (item = list_entry(self->next, typeof(item), member),  *prefetch = item->member.next; &item->member != self; item = list_entry(prefetch,  typeof(item), member), NODE_NEXT(prefetch))

#define CHECK_VALID_LIST(self) CHECK(self, "Invalid list")
#define CHECK_INDEX(self, pos) CHECK(!((pos < 0) || (pos >= self->len)), "Index out of range")
#define CHECK_LIST(self, pos) CHECK_INDEX(self, pos); CHECK_VALID_LIST(self)

#define LIST_IS_EMPTY(self) (self->prev == self->next)

#define LLIST_APPEND(self, elem, member) \
        (list_append(self, &(elem.member), offset_of(typeof(elem), member), sizeof(typeof(elem))))

#define LLIST_GET_ITEM(self, n) \
        ({ \
            llist_node_t * ptr = self->next; \
            NODE_NEXT_N(ptr, n);\
            ptr; \
        })

#define LLIST_INSERT(self, n, elem, member) \
        ({ \
            llist_node_t* item = LLIST_GET_ITEM(self, n); \
            list_append(item, &(elem.member), offset_of(typeof(elem), member), sizeof(typeof(elem)))); \
        })

#define LLIST_EXTEND(self, src, type, member) \
        list_extend(self, src, offset_of(type, member), sizeof(type))


#define LLIST_REMOVE_NODE(self, node, type, member) \
        (list_remove_node(self, node, offset_of(type, member)))

#define LLIST_REMOVE(self, n, type, member) \
        ({ \
            llist_node_t* item = LLIST_GET_ITEM(self, n); \
            LLIST_REMOVE_NODE(self, item, type, member); \
        })


#endif