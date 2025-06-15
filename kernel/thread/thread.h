#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>

typedef enum {
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_BLOCKED,
    THREAD_TERMINATED
} thread_state_t;

typedef struct thread {
    uint32_t *stack_ptr;          // Saved stack pointer
    int id;
    thread_state_t state;
    void (*entry)(void);
    struct thread *next;
} thread_t;

// API
thread_t *thread_create(void (*entry)(void));
//void thread_init();
//void thread_yield();

#endif

