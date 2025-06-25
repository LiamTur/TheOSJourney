extern void isr_stub_0();
extern void isr_stub_1();
extern void isr_stub_2();
extern void isr_stub_3();
extern void isr_stub_4();
extern void isr_stub_5();
extern void isr_stub_6();
extern void isr_stub_7();
extern void isr_stub_8();
extern void isr_stub_9();
extern void isr_stub_10();
extern void isr_stub_11();
extern void isr_stub_12();
extern void isr_stub_13();
extern void isr_stub_14();
extern void isr_stub_15();
extern void isr_stub_16();
extern void isr_stub_17();
extern void isr_stub_18();
extern void isr_stub_19();
extern void isr_stub_20();
extern void isr_stub_21();
extern void isr_stub_22();
extern void isr_stub_23();
extern void isr_stub_24();
extern void isr_stub_25();
extern void isr_stub_26();
extern void isr_stub_27();
extern void isr_stub_28();
extern void isr_stub_29();
extern void isr_stub_30();
extern void isr_stub_31();

typedef struct {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

idt_entry_t idt[256];
idt_ptr_t idtp;

extern void idt_load(); 

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_high = (base >> 16) & 0xFFFF;
}

typedef void (*isr_t)(registers_t *);
isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void idt_install() {
    idtp.limit = (sizeof(idt_entry_t) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    idt_set_gate(0, (uint32_t)isr_stub_0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr_stub_1, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr_stub_31, 0x08, 0x8E);

    idt_load(); // Loads IDT from idtp
}

void isr_handler(registers_t *r) {
    if(interrupt_handler[r->int_no]; {
		isr_t handler = interrupt_handlers[r->int_no];
		handler(r);
	} else {
		terminal_writestring("Unhandled interrupt: ");
		terminal_write_dec(r->int_no);
		terminal_writestring("\n");
	}
    terminal_writestring("Received interrupt: ");
    terminal_write_dec(r->int_no);
    terminal_writestring("\n");
}
