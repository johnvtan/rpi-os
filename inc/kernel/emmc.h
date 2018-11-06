#ifndef __EMMC_H__
#define __EMMC_H__

#include <stdint.h>

#define EMMC_BASE_ADDRESS (0x3F300000U)

typedef struct {
    uint32_t reserved;
} EMMC_PERIPH;

int emmc_init(void);
uint32_t emmc_read(void);
int emmc_write(uint32_t data);
#endif
