.section ".text.boot"

.globl _start

_start:
    // stopping all cpus except cpu 0
    mrc p15, #0, r1, c0, c0, #5
    and r1, r1, #3
    cmp r1, #0
    bne halt

    // setup the stack starting at 0x8000
    mov sp, #0x8000

    // clear out bss
    ldr r4, =__bss_start
    ldr r9, =__bss_end
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b   2f

1:
    // store multiple at r4
    stmia r4!, {r5-r8}

2:
    cmp r4, r9
    blo 1b

    // call kernel_main
    ldr r3, =kernel_main
    blx r3

halt:
    // stop cpu
    wfe
    b halt