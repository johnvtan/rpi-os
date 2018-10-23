#ifndef __MEM_H__
#define __MEM_H__

#include <kernel/atags.h>
#include <kernel/list.h>
#include <stdint.h>

#define PAGE_SIZE (4096)

// initialize kernel heap size to be like 1 mb
#define KERNEL_HEAP_SIZE (1024 * 1024)

typedef struct {
    uint32_t used : 1;
    uint32_t kernel : 1;
    uint32_t reserved : 30;
} page_flags_t;

typedef struct {
    uint32_t address;
    page_flags_t flags;
} page_t;

typedef struct {
    page_t page;
    struct list_node *node;
} page_list_t;

int mem_init(atag_t *atags);
void *allocate_page(void);
int free_page(void *page);
#endif
