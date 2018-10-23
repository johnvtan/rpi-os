#ifndef __ATAGS_H__
#define __ATAGS_H__

#include <stdint.h>

// Atags are identifiers defined by the bootloader and passed to the kernel when it's started
// We use them to determine the total size of memory we have available and their purpose
// i.e., some are reserved as memory for the screen
typedef enum {
    NONE = 0x00000000,
    CORE = 0x5441001,
    MEM = 0x5441002
} atag_t;

typedef struct {
    uint32_t size;
    uint32_t start;
} mem_t;

uint32_t get_mem_size(atag_t *atags);
#endif
