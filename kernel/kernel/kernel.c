#include <stdio.h>
#include <../thread/thread.h>

#include <kernel/tty.h>
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void thread_ping(void) {
    while (1) {
        terminal_writestring("ping\n");
        thread_yield();
    }
}

void thread_pong(void) {
    while (1) {
        terminal_writestring("pong\n");
        thread_yield();
    }
}

void thread_main(void) {
    while (1) {
        thread_yield();
    }
}


void kernel_main2(void) {
    thread_init(thread_main); // This calls thread_create and sets up main thread from wich I can spawn new ones and keep track on current thread

    thread_t *ping = thread_create(thread_ping);
    thread_add(ping);

    thread_t *pong = thread_create(thread_pong);
    thread_add(pong);

    // Start running threads here and hope to GOD I see ducking ping pong
    while (1) {
        thread_yield();
    }
}




void kernel_main(void) 
{
	terminal_initialize();
	print_arch_logo();
	terminal_writestring("\n");
	print_color_palette();
	terminal_writestring("works");
	terminal_writestring("works2!");
	kernel_main2();
	
}
