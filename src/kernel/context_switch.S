# context switch assembly funcition (from https://jsandler18.github.io/tutorial/process.html)
# pushes r0-r12 and cpsr onto the stack
# the function prototype for this would be:
# void context_switch(proc_control_block_t *p1, proc_control_block_t *p2)
context_switch:
    push    {lr}
    mrs     r12, cpsr
    push    {r0-r12}
    str     sp, [r0]
    ldr     sp, [r1]
    pop     {r0-r12}
    msr     cpsr_c, r12
    pop     {lr, pc}