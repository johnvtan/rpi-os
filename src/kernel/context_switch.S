# context switch assembly function (from https://jsandler18.github.io/tutorial/process.html)
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

# When I implement dynamic process creation, I'll need to change the context switch
# to point to wherever on the stack the saved state exists. I'll also need to add stuff
# for process creation, which actually puts the saved state on the stack.

# OK, so I should set the PC to the saved state's LR since it should jump back to
# the instruction after the yield() call (or later exception), which is what LR stores.

# I think for now I can safely make a few assumptions about the system. Ie, the processes
# will run forever (so no need to deal with clean up yet), they are known at compile time,
# and really all I'm trying to get working is the cooperative context switching stuff. 