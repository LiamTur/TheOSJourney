#include <stddef.h>
#include "thread.h"
#include "../arch/i386/context_switch.h"
#include "../km/kmalloc.h"

#define STACK_SIZE 4096

static thread_t *thread_list = NULL;
static thread_t *current_thread = NULL; // more or less  debugging tool I have another way of checking current so if the ./iso.sh does not warn about unused stuff something is wrong

extern void start_thread(void);

void thread_exit(void) {
    while (1) __asm__ volatile("hlt");
}

void thread_init(void (*main_entry)(void)) {
    thread_t *main_thread = thread_create(main_entry);
    thread_list = main_thread;
    current_thread = main_thread;
}

thread_t *thread_create(void (*entry)(void)) {
	thread_t *t = (thread_t *)kmalloc(sizeof(thread_t));
	uint32_t *stack = (uint32_t *)kmalloc_aligned(STACK_SIZE, 16);

	for (size_t i = 0; i < STACK_SIZE / sizeof(uint32_t); i++){
		stack[i] = 0;
	}

	uint32_t *stack_top = stack + (STACK_SIZE / sizeof(uint32_t));

	*(--stack_top) = (uint32_t)thread_exit;     // Return address after entry returns
	*(--stack_top) = (uint32_t)entry;           // Argument to start_thread (entry func)
	*(--stack_top) = (uint32_t)start_thread;    // "Return address" for context switch
	
	t->stack_ptr = stack_top;
	t->base_ptr = 0;
	t->entry = entry;
	t->next = NULL;
	
	return t;
}

void thread_add(thread_t *t) {
    if (!thread_list) {
        thread_list = t;
        t->next = t;
    } else {
        t->next = thread_list->next;
        thread_list->next = t;
    }
}

thread_t *thread_get_current(void) {
    return current_thread;
}

thread_t *thread_get_list(void) {
    return thread_list;
}

thread_t *pick_next_thread(void) {
	if (!current_thread) return thread_list;
	if (current_thread->next) return current_thread->next;
	return thread_list;
}

void thread_yield(void) {
    thread_t *prev = current_thread;
    thread_t *next = pick_next_thread();

    if (next == NULL || next == prev) {
        return;
    }

    current_thread = next;
    context_switch(prev, next);
}

