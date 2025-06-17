#include "context_switch.h"

void context_switch(thread_t *current, thread_t *next) {
    asm volatile (
        // Save current stack pointer for now only do ESP and EBP since I have no US WHEN that comes remember fix syscalls TSS structer and use SS
        "movl %%esp, %0\n\t"
        "movl %%ebp, %1\n\t"
        // Load next stack pointer
        "movl %2, %%esp\n\t"
        "movl %3, %%ebp\n\t"
        :
        "=m"(current->stack_ptr),
        "=m"(current->base_ptr)
        :
        "m"(next->stack_ptr),
        "m"(next->base_ptr)
    );
}

