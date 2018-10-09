#ifndef __LIST_H__
#define __LIST_H__

/**
 * List implementation, mostly ripped off the Linux kernel's list.h
 */

struct list_node {
    struct list_node *next;
    struct list_node *prev;
};

static inline int list_init(list_node *head) {
    return 0;
}

static inline int list_add(list_node *head, list_node *new) {
    return 0;
}

static inline int list_delete(list_node *prev, list_node *next) {
    return 0;
}

/*
 * This macro infers the address of the type containing the list node
 * using the name of the type and the name of the list_node member in that struct
 * 
 * @param ptr The ptr to the list_node (&struct list_node)
 * @param type The name of the type containing the list node
 * @param member The name of the member in the struct that is of type list_node
 * @return Pointer to struct containing ptr as a member
 */
#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head)

#define list_for_each_prev(pos, head)
#endif
