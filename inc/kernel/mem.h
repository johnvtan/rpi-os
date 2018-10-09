#ifndef __MEM_H__
#define __MEM_H__

#include <kernel/atags.h>

#define PAGE_SIZE (4096)

typedef struct {
    uint32_t used : 1;
    uint32_t kernel_page : 1;
    uint32_t reserved : 30;
} page_flags_t;

typedef struct {
    uint32_t address;
    page_flags_t flags;
    page_t *next;
} page_t;

int mem_init(atag_t *atags);
void *allocate_page(void);
int free_page(void *page);
#endif
