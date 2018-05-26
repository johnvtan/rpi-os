#ifndef __SYSTEM_TIMER_H__
#define __SYSTEM_TIMER_H__

#define SYSTEM_TIMER_BASE 0x7E003000U

typedef struct _CS {
    unsigned int M0       : 1;
    unsigned int M1       : 1;
    unsigned int M2       : 1;
    unsigned int M3       : 1;
    unsigned int reserved : 28;
} SYSTEM_TIMER_CS;

typedef struct _COUNT {
    unsigned int count;
} SYSTEM_TIMER_COUNT;

typedef struct _COMPARE {
    unsigned int compare;
} SYSTEM_TIMER_COMPARE;

typedef struct _SYSTEM_TIMER {
    SYSTEM_TIMER_CS      control_status;    // offset 0x00
    SYSTEM_TIMER_COUNT   counter_lower;     // offset 0x4
    SYSTEM_TIMER_COUNT   counter_high;      // offset 0x8
    SYSTEM_TIMER_COMPARE compare_0;         // offset 0xC
    SYSTEM_TIMER_COMPARE compare_1;         // offset 0x10
    SYSTEM_TIMER_COMPARE compare_2;         // offset 0x14
    SYSTEM_TIMER_COMPARE compare_3;         // offset 0x18
} SYSTEM_TIMER;

#endif