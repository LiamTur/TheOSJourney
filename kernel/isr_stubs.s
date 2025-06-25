.global isr_stub_0
.global isr_stub_1
.global isr_stub_2
.global isr_stub_3
.global isr_stub_4
.global isr_stub_5
.global isr_stub_6
.global isr_stub_7
.global isr_stub_8
.global isr_stub_9
.global isr_stub_10
.global isr_stub_11
.global isr_stub_12
.global isr_stub_13
.global isr_stub_14
.global isr_stub_15
.global isr_stub_16
.global isr_stub_17
.global isr_stub_18
.global isr_stub_19
.global isr_stub_20
.global isr_stub_21
.global isr_stub_22
.global isr_stub_23
.global isr_stub_24
.global isr_stub_25
.global isr_stub_26
.global isr_stub_27
.global isr_stub_28
.global isr_stub_29
.global isr_stub_30
.global isr_stub_31
.global isr_common_stub

.macro ISR_NOERR num
isr_stub_\num:
    cli
    pushl $0
    pushl $\num
    jmp isr_common_stub
.endm

.macro ISR_ERR num
isr_stub_\num:
    cli
    pushl $\num
    jmp isr_common_stub
.endm

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR   8
ISR_NOERR 9
ISR_ERR   10
ISR_ERR   11
ISR_ERR   12
ISR_ERR   13
ISR_ERR   14
ISR_NOERR 15
ISR_NOERR 16
ISR_ERR   17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

isr_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    push %esp
    call isr_handler
    add $4, %esp
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    sti
    iret

