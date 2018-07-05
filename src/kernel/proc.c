#include <stdint.h>

#include <kernel/proc.h>
#include <common/stdio.h>
#include <common/strings.h>

typedef struct {
    uint32_t r[12];
    uint32_t cpsr;
    uint32_t sp;
    uint32_t lr;
} proc_state_t;

typedef struct {
    proc_state_t  *state;   // pointer to location of saved state. for now, should point somewhere in .data section?
    uint32_t pid;
} proc_control_block_t;

extern void context_switch(proc_control_block_t *p1, proc_control_block_t *p2);

#define PCB_LEN 5

// for now, just have two tasks running that are known at compile time
static proc_control_block_t pcb[PCB_LEN];
static proc_state_t process_states[PCB_LEN];

// index into pcb/process_states array
static int curr_proc_handle;   

void yield(void);

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

static void task3(void) {
    while (1) {
        printf("Task 3 running\n");
        yield();
    }
}

static void task4(void) {
    while (1) {
        printf("Task 4 running\n");
        yield();
    }
}

static void task5(void) {
    while (1) {
        printf("Task 5 running\n");
        yield();
    }
}

// initializes processes - because we don't have any memory management yet,
// all processes need to be known at compile time
void proc_init(void) {
    // zero out registers
    int i = 0;
    for (i = 0; i < PCB_LEN; i++) {
        // zero out saved state. not sure if necessary
        memset(&process_states[i], 0, sizeof(proc_state_t));
        
        // set pcb state to point to where process states is stored in memory
        pcb[i].state = &process_states[i];
        pcb[i].pid = i; // placeholder
    }

    // set lr to task1 and task2 so that we can jump to them
    process_states[0].lr = (uint32_t)task1;
    process_states[1].lr = (uint32_t)task2;
    process_states[2].lr = (uint32_t)task3;
    process_states[3].lr = (uint32_t)task4;
    process_states[4].lr = (uint32_t)task5;

    // then I just call task1() to start it?
    curr_proc_handle = 4;
    task5();

    // shouldn't get here
}

void yield(void) {
    // need handles for previous and current process
    int prev_proc_handle = curr_proc_handle++;
    if (curr_proc_handle >= PCB_LEN) {
        curr_proc_handle = 0;
    }
    printf("Switching from task %d to %d: ", prev_proc_handle+1, curr_proc_handle+1);
    // switch from previous to current
    context_switch(&pcb[prev_proc_handle], &pcb[curr_proc_handle]); 

    // It is important that context_switch is the last line in this function,
    // otherwise the link register doesn't get set correctly, ie, if I put a print
    // then when we return to some task, it will jump to that print statement
    // since the link register will be set when we call context_switch
    // if there's no instructions here, the link register doesn't get changed
    // so it will be the correct instruction in the task that called yield()
    return;
}