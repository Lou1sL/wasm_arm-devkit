

    .equ    I,     0b10000000
    .equ    F,     0b01000000
    .equ    USR,   0b00010000
    .equ    FIQ,   0b00010001
    .equ    IRQ,   0b00010010
    .equ    SVC,   0b00010011
    .equ    ABT,   0b00010111
    .equ    UND,   0b00011011
    .equ    SYS,   0b00011111
    .equ    STACK_FILL, 0xCCCCCCCC

	.text
	.code 32
	.global _bootloader
	.func   _bootloader

_bootloader:
	/* Exception Vector */
	b _rst
	b _und
	b _swi
	b .    /* Not implemented in WASM_ARM */
	b .    /* Not implemented in WASM_ARM */
	b .
	b _irq
	b .    /* Not implemented in WASM_ARM */

	.string "2020 ryubai.com by RyuBAI for WASM_ARM platform."
	.align 4

_rst:
	/* .bss must be init to 0 */
	ldr     r1, =__bss_start__
	ldr     r2, =__bss_end__
	mov     r3, #0
1:
	cmp     r1, r2
	stmltia r1!, {r3}
	blt		1b

	/* .stack coloring
    ldr     r1,  =__stack_start__
    ldr     r2,  =__stack_end__
    ldr     r3,  =STACK_FILL
1:
    cmp     r1,  r2
    stmltia r1!, {r3}
    blt     1b  */

	/* Initialize sp for each bank */
	msr CPSR_c, #(IRQ | I | F)
	ldr sp    , =__irq_stack_top__
	msr CPSR_c, #(FIQ | I | F)
	ldr sp    , =__fiq_stack_top__
	msr CPSR_c, #(SVC | I | F)
	ldr sp    , =__svc_stack_top__
	msr CPSR_c, #(ABT | I | F)
	ldr sp    , =__abt_stack_top__
	msr CPSR_c, #(UND | I | F)
	ldr sp    , =__und_stack_top__
	msr CPSR_c, #(SYS | I | F) /* Enable IRQ */
	ldr sp    , =__sys_stack_top__

	/* Execute static c++ constructors */
	ldr r12, =__libc_init_array
	mov lr, pc
	bx r12

	/* Execute c/c++ main */
	ldr r12, =main
	mov lr, pc
	bx  r12
	swi 0xffffff


_und:
	sub r1, lr, #4
	msr cpsr_c, #(SYS | I | F)
	ldr r12, =und_handler
	mov lr, pc
	bx  r12
	b   .


_swi:
	sub r1, lr, #4
	msr cpsr_c, #(SYS | I | F)
	ldr r12, =swi_handler
	mov lr, pc
	bx  r12
	b   .


_irq:
	/* https://web.eecs.umich.edu/~prabal/teaching/resources/eecs373/ARM-AAPCS-EABI-v2.08.pdf */
	mov r13, r0
	sub  r0, lr, #4
	mov  lr, r1
	mrs  r1, spsr

	msr   cpsr_c, #(SYS | I)
    stmfd sp!, {r0, r1}
    stmfd sp!, {r2-r3, r12, lr}
    mov   r0, sp
    SUB   sp, sp, #(2*4)

    msr   cpsr_c, #(IRQ | I)
    stmfd r0!, {r13, r14}

    msr   cpsr_c, #(SYS | I)
	
	/* Enter Handler */
    ldr   r12, =irq_handler
    mov   lr, pc
    bx    r12

    msr   cpsr_c, #(SYS | I | F)
    mov   r0, sp
    ADD   sp, sp, #(8*4)

    msr   cpsr_c, #(SYS | I | F)
    mov   sp, r0
    ldr   r0, [sp, #(7*4)]
    msr   spsr_cxsf, r0

    LDMFD sp, {r0-r3, r12, lr}^
    NOP
    ldr   lr, [sp, #(6*4)]
    movs  pc, lr

	.size _bootloader, . - _bootloader
	.endfunc


	.global lock_interrupt
	.func   lock_interrupt
lock_interrupt:
	mrs r0, cpsr
	msr cpsr_c, #(SYS | I | F)
	bx lr
	.size   lock_interrupt, . - lock_interrupt
    .endfunc


	.global unlock_interrupt
	.func   unlock_interrupt
unlock_interrupt:
	msr cpsr, r0
	bx lr
	.size   unlock_interrupt, . - unlock_interrupt
    .endfunc


	.end
