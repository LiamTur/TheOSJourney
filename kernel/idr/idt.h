#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "registers.h"

void idt_install(void);
void isr_handler(registers_t *r);

typdef void (*isr_t)(register_t *r);
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif
