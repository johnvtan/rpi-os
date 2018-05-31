#ifndef __UART_0_H__
#define __UART_0_H__

#include <stdint.h>

#define UART0_BASE_ADDR 0x3F201000U

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t data        :8;
            uint32_t frame_err   :1;
            uint32_t parity_err  :1;
            uint32_t break_err   :1;
            uint32_t overrun_err :1;
            uint32_t reserved1   :19;
        };
    };
} UART0_DR;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t frame_err   :1;
            uint32_t parity_err  :1;
            uint32_t break_err   :1;
            uint32_t overrun_err :1;
        };
    };
} UART0_RSRECR;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t clear_to_send :1;
            uint32_t reserved1     :2;
            uint32_t busy          :1;
            uint32_t rx_empty      :1;
            uint32_t tx_full       :1;
            uint32_t rx_full       :1;
            uint32_t tx_empty      :1;
            uint32_t reserved2     :24;
        };
    };
} UART0_FR;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t data       :16;
            uint32_t reserved1  :16;
        };
    };
} UART0_IBRD;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t data     :6;
            uint32_t reserved :26;
        };
    };
} UART0_FBRD;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t brk          :1;
            uint32_t parity_en    :1;
            uint32_t even_parity  :1;
            uint32_t stop_2       :1;
            uint32_t fifo_en      :1;
            uint32_t word_len     :2;
            uint32_t stick_parity :1;
            uint32_t reserved1    :24;
        };
    };
} UART0_LCRH;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t uart_en    :1;
            uint32_t reserved1  :6;
            uint32_t loopback_en :1;
            uint32_t tx_en      :1;
            uint32_t rx_en      :1;
            uint32_t dtr        :1;
            uint32_t rts        :1;
            uint32_t out1       :1;
            uint32_t out2       :1;
            uint32_t rts_en     :1;
            uint32_t cts        :1;
            uint32_t reserved2  :16;
        };
    };
} UART0_CR;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t tx_ifl_sel :3;
            uint32_t rx_ifl_sel :3;
            uint32_t reserved1  :26;
        };
    };
} UART0_IFLS;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t ri  :1;
            uint32_t cts :1;
            uint32_t dcd :1;
            uint32_t dsr :1;
            uint32_t rx  :1;
            uint32_t tx  :1;
            uint32_t rt  :1;
            uint32_t fe  :1;
            uint32_t pe  :1;
            uint32_t be  :1;
            uint32_t oe  :1;
            uint32_t reserved1 :21;
        };
    };
} UART0_INT_REG;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t itcr0  :1;
            uint32_t itcr1  :1;
            uint32_t reserved1 :30;
        };
    };
} UART0_ITCR;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t itip0     :1;
            uint32_t reserved1 :2;
            uint32_t itip3     :1;
            uint32_t reserved2 :28;
        };
    };
} UART0_ITIP;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t itip0     :1;
            uint32_t reserved1 :2;
            uint32_t itip3     :1;
            uint32_t reserved2 :2;
            uint32_t itip6     :1;
            uint32_t itop7     :1;
            uint32_t itop8     :1;
            uint32_t itop9     :1;
            uint32_t itop10    :1;
            uint32_t itop11    :1;
            uint32_t reserved3 :20;           
        };
    };
} UART0_ITOP;

typedef struct {
    union {
        uint32_t val;
        struct {
            uint32_t tdr10_0    :11;
            uint32_t reserved   :21;
        };
    };
} UART0_TDR;

struct UART0 {
    // 0x00
    UART0_DR      data;     
    // 0x04    
    UART0_RSRECR  rx_status;
    // 0x08, 0x0C, 0x10, 0x14
    uint32_t      reserved1[4]; 
    // 0x18
    UART0_FR      flags;
    // 0x1C
    uint32_t      reserved2;
    // 0x20
    uint32_t      ILPR;
    // 0x24
    UART0_IBRD    int_baud_rate_div;
    //0x28
    UART0_FBRD    frac_baud_rate_div;
    //0x2C
    UART0_LCRH    line_control;
    //0x30
    UART0_CR      control;
    //0x34
    UART0_IFLS    int_fifo_sel;
    //0x38
    UART0_INT_REG int_mask_set_clear;
    //0x3C
    UART0_INT_REG raw_int_status;
    //0x40
    UART0_INT_REG mask_int_status;
    //0x44
    UART0_INT_REG int_clear;
    // 0x48
    uint32_t      dmacr;
    // 0x4C - 0x7C
    uint32_t      reserved3[12];
    // 0x80
    UART0_ITCR    test_control;
    //0x84
    UART0_ITIP    test_input;
    // 0x88
    UART0_ITOP    test_output;
    //0x8C
    UART0_TDR     test_data;
};

#endif