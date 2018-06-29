# context switch assembly funcition (from https://jsandler18.github.io/tutorial/process.html)
# pushes r0-r12 and cpsr onto the stack
# the function prototype for this would be:
# void context_switch(proc_control_block_t *p1, proc_control_block_t *p2)
.globl context_switch
context_switch:

    # why save link reg?
    push    {lr, sp}

    # r12 is caller-save, so we can mess with it
    # save current process tate reg in r12
    mrs     r12, cpsr

    # save r0-r12 on the stack for process about to be switched from
    push    {r0-r12}

    # actual switching occurs here - not sure how this works yet
    # i'm not sure what's actually being put in the stack pointer after this
    str     sp, [r0]
    ldr     sp, [r1]

    # with new sp, pop r0-r12
    pop     {r0-r12}

    # since we're saving cpsr in r12, we read from r12 to restore cpsr
    msr     cpsr_c, r12

    # then pop off lr, pc from the stack
    pop     {lr, pc}


# Some thoughts:
# I don't think the process blocks actually exist on the stack - they should
# be in the data segment since they're statically allocated for me. So maybe
# it doesn't make sense to be using the stack pointer and push/pop here.
# Instead, I should be manually loading/storing from an offset from r0/r1
# to save/load registers. 

# I still am not sure how it starts running the new process. The link register
# gets put into the PC, so it starts running from where the link register says.
# But what's in the link register? Maybe that's the source of the confusion for me.

# It would make more sense to me to save the PC value somewhere and load that into 
# the current PC, but I don't understand why that doesn't happen.

# He is probably saving the LR to the PC since in his code, context switches are
# only called during timer interrupts, so the PC would point to code in the IRQ handler
# and the LR would be pointing to where the program should resume running.

# So since I'm doing cooperative scheduling right now, I should be saving/restoring
# the PC value because the LR doesn't really do anything for me as of now.
# Also still need to figure out the stack stuff