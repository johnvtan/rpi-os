#include <kernel/mem.h>
#define NULL (0)
// from the linker script
extern uint8_t __end;

static page_t *page_array;
static uint32_t num_pages;

int mem_init(atag_t *atags) {
    uint32_t total_mem_size;
    uint32_t total_metadata_size;
    uint32_t kernel_pages;
    uint32_t i;

    total_mem_size = get_mem_size(atags); 
    num_pages = total_mem_size / PAGE_SIZE;
    total_metadata_size = sizeof(page_t) * num_pages;

    // total number of kernel pages is size of code + size of kernel heap + size of page array
    /*
     * So far, I think memory should look like this:
     * | Kernel code | page array | kernel heap (not yet allocated) | free memory           |
     */
    kernel_pages = ((uint32_t)&__end / PAGE_SIZE) + (KERNEL_HEAP_SIZE / PAGE_SIZE) + total_metadata_size;

    // so reserve the size of the metadata from after the kernel ends
    page_array = (page_t*)&__end; 

    // initialize all the memory metadata
    for (i = 0; i < num_pages; i++) {
        page_array[i].address = i * PAGE_SIZE;
        if (i < kernel_pages) {
            page_array[i].flags.used = 1;
            page_array[i].flags.kernel = 1;
        } else {
            page_array[i].flags.used = 0;
            page_array[i].flags.kernel = 0;
        }
    }
     
    return 0;
}

void *allocate_page(void) {
    // for now, this just iterates through the entire page array from the beginning and gets the first free one
    uint32_t i;
    for (i = 0; i < num_pages; i++) {
        if (page_array[i].flags.used == 0) {
            // congrats! you get a page!
            // I guess for now, all pages will be for the kernel until the kernel hands it off to user
            page_array[i].flags.kernel = 1;
            page_array[i].flags.used = 1;
            return (void*)page_array[i].address;
        }
    }
    // all pages are being used and we're out of memory
    return NULL;
}

int free_page(void *page) {
    // the page we get is the address we want to free
    uint32_t page_index = (uint32_t)((uint32_t)page / PAGE_SIZE);

    // if that page wasn't allocated in the first place, return 
    if (page_array[page_index].flags.used == 0) {
        return -1;
    }
    page_array[page_index].flags.used = 0;
    page_array[page_index].flags.kernel = 1;
    return 0;
}
