#include <kernel/proc.h>
#include <common/stdio.h>

typedef struct {
    uint32_t r[12];
    uint32_t cpsr;
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
} proc_state_t;

typedef struct {
    proc_state_t state;
    uint32_t pid;
} proc_control_block_t;

extern void context_switch(proc_control_block_t *p1, proc_control_block_t *p2);

#define PCB_LEN 2

// for now, just have two tasks running that are known at compile time
static process_control_block_t pcb[PCB_LEN];

// index into pcb
static int curr_proc_handle = 0;   

// example tasks for scheduling
static void task1(void) {
    while (1) {
        printf("Task 1 running\n");
        yield();
    }
}

static void task2(void) {
    while (1) {
        printf("Task 2 running\n");
        yield();
    }
}

// initializes processes - because we don't have any memory management yet,
// all processes need to be known at compile time
void proc_init(void) {
    return;
}

void proc_run_next(void) {
    // context switch to curr_proc
    return;
}

// cooperative scheduling - allows a running process to give up CPU
void yield(void) {
    // TODO: save context on stack, load other context
}