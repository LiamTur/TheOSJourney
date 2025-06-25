#include "../thread/thread.h"
#include <stdint.h>
#include "../interrupts/idt.h" 

#define PIT_FREQUENCY 1000  // 1000 Hz = 1ms tick

static uint32_t tick = 0;

void pit_callback(void) {
    tick++;
    thread_yield();  
}

void init_pit() {
    uint32_t divisor = 1193180 / PIT_FREQUENCY;
    
    outb(0x43, 0x36);  // Command byte
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);

    register_interrupt_handler(32, pit_callback);  // IRQ0 -> INT 32
}

