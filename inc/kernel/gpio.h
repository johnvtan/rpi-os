#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

#define GPIO_BASE_ADDR 0x3F200000U

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t fsel0 :3;
            uint32_t fsel1 :3;
            uint32_t fsel2 :3;
            uint32_t fsel3 :3;
            uint32_t fsel4 :3;
            uint32_t fsel5 :3;
            uint32_t fsel6 :3;
            uint32_t fsel7 :3;
            uint32_t fsel8 :3;
            uint32_t fsel9 :3;
            uint32_t reserved1 :2;
        };
    };
} GPIO_GPFSELn;

// many of the registers used in GPIO periph take one of two forms, depending on
// which gpios they refer to. If the reg refers to the first 32 bits, then we can 
// represent it with just a uint32_t, but if it refers to the last 22, then we have
// some reserved bits.
typedef struct {
    uint32_t gpio_val;
} GPIO_GENERAL_0;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t gpio_val  :22;
            uint32_t reserved1 :10;
        };
    };
} GPIO_GENERAL_1;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t pud       :2;
            uint32_t reserved1 :30;
        };
    };
} GPIO_GPPUD;

typedef struct {
    // 0x00
    GPIO_GPFSELn gpio_func_sel_0;
    // 0x04
    GPIO_GPFSELn gpio_func_sel_1;
    // 0x08
    GPIO_GPFSELn gpio_func_sel_2;
    // 0x0C
    GPIO_GPFSELn gpio_func_sel_3;
    // 0x10
    GPIO_GPFSELn gpio_func_sel_4;
    // 0x14
    GPIO_GPFSELn gpio_func_sel_5;
    // 0x18
    uint32_t reserved1;
    //0x1C
    GPIO_GENERAL_0 pin_output_set_0;
    // 0x20
    GPIO_GENERAL_1 pin_output_set_1;
    // 0x24
    uint32_t reserved2;
    // 0x28
    GPIO_GENERAL_0 pin_output_clear_0;
    // 0x2C
    GPIO_GENERAL_1 pin_output_clear_1;
    // 0x30
    uint32_t reserved3;
    // 0x34
    GPIO_GENERAL_0 pin_level_0;
    // 0x38
    GPIO_GENERAL_1 pin_level_1;
    // 0x3C
    uint32_t reserved4;
    // 0x40
    GPIO_GENERAL_0 pin_event_detect_status_0;
    // 0x44
    GPIO_GENERAL_1 pin_event_detect_status_1;
    // 0x48
    uint32_t reserved5;
    // 0x4C
    GPIO_GENERAL_0 pin_rising_edge_detect_en_0;
    // 0x50
    GPIO_GENERAL_1 pin_rising_edge_detect_en_1;
    // 0x54
    uint32_t reserved6;
    // 0x58
    GPIO_GENERAL_0 pin_falling_edge_detect_en_0;
    // 0x5C
    GPIO_GENERAL_1 pin_falling_edge_detect_en_1;
    // 0x60
    uint32_t reserved7;
    // 0x64
    GPIO_GENERAL_0 pin_high_detect_en_0;
    // 0x68
    GPIO_GENERAL_1 pin_high_detect_en_1;
    // 0x6C
    uint32_t reserved8;
    // 0x70
    GPIO_GENERAL_0 pin_low_detect_en_0;
    // 0x74
    GPIO_GENERAL_1 pin_low_detect_en_1;
    // 0x78
    uint32_t reserved9;
    // 0x7C
    GPIO_GENERAL_0 pin_async_rising_edge_detect_en_0;
    // 0x80
    GPIO_GENERAL_1 pin_async_rising_edge_detect_en_1;
    // 0x84
    uint32_t reserved10;
    // 0x88
    GPIO_GENERAL_0 pin_async_falling_edge_detect_en_0;
    // 0x8C
    GPIO_GENERAL_1 pin_async_falling_edge_detect_en_1;
    // 0x90
    uint32_t reserved11;
    // 0x94
    GPIO_GPPUD pin_pull_up_down_en;
    // 0x98
    GPIO_GENERAL_0 pin_pull_clock_0;
    // 0x9C
    GPIO_GENERAL_1 pin_pull_clock_1;
    // 0xA0
    uint32_t reserved12;
    // 0xB0 has a test register, but I'm not sure if I really need it.
} GPIO_PERIPH;

#endif