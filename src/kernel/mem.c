#include <kernel/mem.h>

#ifdef TEST
#include <common/stdio.h>
#endif

#define NULL (0)
// from the linker script
extern uint8_t __end;

static page_t *page_array;
static struct list_node *free_page_list_head;
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
    kernel_pages = ((uint32_t)&__end / PAGE_SIZE) + (KERNEL_HEAP_SIZE / PAGE_SIZE) + (total_metadata_size / PAGE_SIZE);

    // so reserve the size of the metadata from after the kernel ends
    page_array = (page_t*)&__end; 


    // a little confusing, but all the kernel pages are marked as used, 
    // so the free_page_list_head should be the first non kernel page
    free_page_list_head = &page_array[kernel_pages].node;
    list_init(free_page_list_head);

    // initialize all the memory metadata
    for (i = 0; i < num_pages; i++) {
        if (i < kernel_pages) {
            page_array[i].flags.used = 1;
            page_array[i].flags.kernel = 1;
        } else {
            // Add new node as tail so that we preserve sequential order
            // This should be okay even if it's the head we're adding to itself
            list_add_tail(free_page_list_head, &page_array[i].node);
            page_array[i].flags.used = 0;
            page_array[i].flags.kernel = 0;
        }
    }

#ifdef TEST
    printf("Total memory size is: %u\n", total_mem_size);
    printf("Total number of pages is: %u\n", num_pages);
    printf("Total size of metadata is: %u\n", total_metadata_size);
    printf("Number of pages reserved for kernel is: %u\n", kernel_pages);
    printf("The page array will start at address: %u\n", (uint32_t)page_array);
    printf("The address of the free list head is: %u\n", (uint32_t)list_entry(free_page_list_head, page_t, node));
#endif
    
    return 0;
}

void *allocate_page(void) {
    void *rv = NULL;
    if (free_page_list_head == NULL) {
        return NULL;
    }

    // get new page from free_page_list and set it to be allocated
    page_t *allocated_page = list_entry(free_page_list_head, page_t, node); 
    allocated_page->flags.used = 1;

    // then pop the head off and get the new head of the free list
    free_page_list_head = list_pop_head(free_page_list_head);

    // get physical address. is it divided by sizeof(page_t)?
    rv = (void *)((allocated_page - page_array) * PAGE_SIZE);
    return rv;
}

int free_page(void *page) {
    // the page we get is the address we want to free
    uint32_t page_index = (uint32_t)((uint32_t)page / PAGE_SIZE);

    // if that page wasn't allocated in the first place, return 
    if (page_array[page_index].flags.used == 0) {
        return -1;
    }
    page_array[page_index].flags.used = 0;
    page_array[page_index].flags.kernel = 0;

    list_add_tail(free_page_list_head, &page_array[page_index].node);
    // also set the freed page ptr to NULL 
    page = NULL;
    return 0;
}
