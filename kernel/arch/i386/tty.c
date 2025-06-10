#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

const char* arch_logo[] = {
    "      /\\      ",
    "     /  \\     ",
    "    / /\\ \\    ",
    "   / ____ \\   ",
    "  /_/    \\_\\  ",
    "              ",
    "   Arch OS     ",
};


void terminal_scroll() {
	for (int row = 1; row < VGA_HEIGHT; row++) {
      	   for(int coloumn = 0; coloumn < VGA_WIDTH; coloumn++){
      		terminal_buffer[(row - 1) * VGA_WIDTH + coloumn] = terminal_buffer[row * VGA_WIDTH + coloumn];
      }
	}

	for (int col = 0; col < VGA_WIDTH; col++) {
      		terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = (uint16_t)' ' | (terminal_color << 8);
	}
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{

	if(c == '\n') {
		terminal_row++;
		terminal_column = 0;
            if (terminal_row >= VGA_HEIGHT) {
                terminal_scroll();
                terminal_row = VGA_HEIGHT - 1;
              }
          return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
		if (terminal_row >= VGA_HEIGHT){
			terminal_scroll();
			terminal_row = VGA_HEIGHT - 1;
		}
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void print_arch_logo(void) {
    terminal_color = vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK);
    for (size_t i = 0; i < sizeof(arch_logo)/sizeof(arch_logo[0]); i++) {
        terminal_writestring(arch_logo[i]);
        terminal_putchar('\n');
    }
}

void print_color_palette(void) {
    terminal_writestring("\n VGA Color Palette:\n");
    for (int i = 0; i < 16; i++) {
        terminal_color = vga_entry_color(i, VGA_COLOR_BLACK);
        terminal_writestring("##"); // use full block or "[]"/"##" if block char is odd
    }
    terminal_writestring("\n");
}
