#include <stdio.h>

#include <kernel/tty.h>
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	terminal_initialize();
	print_arch_logo();
	terminal_writestring("\n");
	print_color_palette();
	terminal_writestring("works");
	terminal_writestring("works2!");
	
}
