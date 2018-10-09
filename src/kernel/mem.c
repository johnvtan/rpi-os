#include <kernel/mem.h>
#include <kernel/atags.h>
#include <stdint.h>

// from the linker script
extern uint8_t __end;
static page_t *used_list;
static page_t *free_list;

// TODO: given the memory defined by the atags, how do I want to organize it?
// Have a used list and a free list
int mem_init(atag_t *atags) {
    uint32_t total_mem_size;
    uint32_t num_pages;
    uint32_t total_metadata_size;

    total_mem_size = get_mem_size(atags); 
    num_pages = total_mem_size / PAGE_SIZE;
    total_metadata_size = sizeof(page_t) * num_pages;

    // so reserve the size of the metadata from after the kernel ends
     
    return 0;
}

void *allocate_page(void) {
    return NULL;
}

int free_page(void *page) {
    return 0;
}
