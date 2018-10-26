#ifndef __LIST_H__
#define __LIST_H__

#define NULL (0)
/**
 * List implementation, mostly ripped off the Linux kernel's list.h
 * (all functions assume that the list_node has already been allocated)
 * This might all go horribly wrong because I'm not doing anything with atomics, but whatever
 */

struct list_node {
    struct list_node *next;
    struct list_node *prev;
};

static inline int list_init(struct list_node *head) {
    if (NULL == head) {
        return -1;
    }
    head->next = head;
    head->prev = head;
    return 0;
}

// internal inline used to add when we know the prev and next nodes
static inline int __list_add(struct list_node *entry, struct list_node *prev, struct list_node *next) {
    if (NULL == entry || NULL == prev || NULL == next) {
        return -1;
    }
    entry->next = next;
    entry->prev = prev;
    next->prev = entry;
    return 0;
}

// inserts node after the head
static inline int list_add(struct list_node *head, struct list_node *new_node) {
    return __list_add(new_node, head, head->next);
}

// inserts node after tail/before head
static inline int list_add_tail(struct list_node *head, struct list_node *new_node) {
    return __list_add(new_node, head->prev, head);
}

// deletes from list, but DOESN'T deallocate memory to that node.
static inline int __list_delete(struct list_node *prev, struct list_node *next) {
    if (NULL == prev || NULL == next) {
        return -1;
    }
    prev->next = next;
    next->prev = prev;
    return 0;
}

static inline int list_delete(struct list_node *entry) {
    if (0 != __list_delete(entry->prev, entry->next)) {
        return -1;
    }
    entry->next = NULL;
    entry->prev = NULL;
    return 0;
}

// method for popping the head off and returning the new head
static inline struct list_node* list_pop_head(struct list_node *head) {
    struct list_node *new_head = head->next;
    list_delete(head);
    return new_head;
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

// since this is a circular list our stopping condition is when we're back at the head
// this probably also means that our head is sort of useless, since when we iterate we don't 
// actually get to the head
#define list_for_each(pos, head) \
    for (pos = head->next; pos != head; pos = pos->next)

#define list_for_each_prev(pos, head) \
    for (pos = head->prev; pos- != head; pos = pos->prev)

#endif
