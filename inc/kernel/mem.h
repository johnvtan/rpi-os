#ifndef __MEM_H__
#define __MEM_H__

#include <kernel/atags.h>
#include <kernel/list.h>
#include <stdint.h>

#define PAGE_SIZE (4096)

// initialize kernel heap size to be like 1 mb
#define KERNEL_HEAP_SIZE (1024 * 1024)

typedef struct {
    uint8_t used : 1;
    uint8_t kernel : 1;
    uint8_t reserved : 6;
} page_flags_t;

typedef struct {
    page_flags_t flags;
    struct list_node node;
} page_t;

int mem_init(atag_t *atags);
void *allocate_page(void);
int free_page(void *page);
#endif
