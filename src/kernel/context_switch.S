// context switch assembly function (from https://jsandler18.github.io/tutorial/process.html)

// pushes r0-r12 and cpsr onto the stack
// the function prototype for this would be:
// void context_switch(proc_control_block_t *p1, proc_control_block_t *p2)
// we switch from p1 to p2
// ARM calling convention is that first 4 params are stored in r0-r3, rest on stack
// so p1 is in r0 and p2 is in r1

.globl context_switch

context_switch:
    // saving state from previous task
    
    // dereferencing pointers to saved state
    ldr     r0, [r0]

    mrs     r12, cpsr
    stmia   r0!, {r0-r12}
    str     sp, [r0], #4
    str     lr, [r0], #4

    // loading state from next task
    ldr     sp, [r1]
    ldmia   sp!, {r0-r11}
    ldr     r12, [sp], #4
    msr     cpsr_c, r12
    mov     r1, sp
    ldr     lr, [r1], #4
    ldr     pc, [r1], #4
    nop

/*
context_switch:

    // since I'm statically allocating tasks
    //ldr sp, [r0]

    // save link reg, sp
    push    {lr}
    push    {sp}

    // r12 is caller-save, so we can mess with it
    // save current process state reg in r12
    mrs     r12, cpsr

    // save r0-r12 on the stack for previous process
    push    {r0-r12}

    // store the stack pointer back at the memory address in r0, which is pcb[prev_proc_handle].state
    // and load memory address from r1, which is pcb[curr_proc_handle].state
    str     sp, [r0]
    ldr     sp, [r1]

    // with new sp, pop r0-r12
    // pop in reverse order since stack is fifo
    pop     {r0-r12}

    // since we're saving cpsr in r12, we read from r12 to restore cpsr
    msr     cpsr_c, r12

    // then pop off lr, pc from the stack
    // lr gets value from prev sp, pc gets from prev lr
    // then it process should jump to previous lr, which should be the instruction
    // after call to yield() (or later, return from interrupt) in that task
    // for now, tasks never end so I'm not worrying about what goes into the lr
    // but later it should not be too difficult to implement tasks that can terminate
    // and this lr points to some task cleanup function.
    pop     {lr, pc}
*/