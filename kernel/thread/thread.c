#include <stddef.h>
#include "thread.h"
#include "../km/kmalloc.h"

#define STACK_SIZE 4096

static thread_t *thread_list = NULL;
static thread_t *current_thread = NULL;


thread_t *thread_create(void (*entry)(void)) {
	thread_t *t = (thread_t *)kmalloc(sizeof(thread_t));
	uint32_t *stack = (uint32_t *)kmalloc_aligned(STACK_SIZE, 16);

	for (size_t i = 0; i < STACK_SIZE / sizeof(uint32_t); i++){
		stack[i] = 0;
	}

	uint32_t *stack_top = stack + (STACK_SIZE / sizeof(uint32_t));

	*(--stack_top) = (uint32_t )entry;

	t->stack_ptr = stack_top;
	t->entry = entry;
	t->next = NULL;

	return t;
}
