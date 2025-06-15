#include <stdio.h>
#include <../thread/thread.h>

#include <kernel/tty.h>
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

// Your thread function
void thread_func1(void) {
    while (1) {
        terminal_writestring("Thread 1 lives!\n");
        for (volatile int i = 0; i < 1000000; i++); // crude delay
    }
}

// Create thread and call function directly (for now)
void test_thread_create(void) {
    thread_t *t = thread_create(thread_func1);
    // For now, just call the function directly
    t->entry();
}


void kernel_main(void) 
{
	terminal_initialize();
	print_arch_logo();
	terminal_writestring("\n");
	print_color_palette();
	terminal_writestring("works");
	terminal_writestring("works2!");
	test_thread_create();
	
}
