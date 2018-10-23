#include <kernel/atags.h>

uint32_t get_mem_size(atag_t *atags) {
    (void)atags;
    // since we're on an emu right now, just return 128 MB
    return (1024 * 1024 * 128);
}

