

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
	b _warm_init /* RST */
	b .          /* UND */
	b .          /* SWI */
	b .          /* PFA */
	b .          /* DTA */
	b .          /* --- */
	b .          /* IRQ */
	b .          /* FIQ */

	.string "2020 ryubai.com by RyuBAI for WASM_ARM platform."
	.align 4

_warm_init:
	/* Relocate .data */
	ldr r0, =__data_load
	ldr r1, =__data_start
	ldr r2, =__data_end
1:
	cmp     r1, r2
	ldmltia r0!, {r3}
	stmltia r1!, {r3}
	blt		1b

	/* Relocate .bss */
	ldr     r1, =__bss_start__
	ldr     r2, =__bss_end__
	mov     r3, #0
1:
	cmp     r1, r2
	stmltia r1!, {r3}
	blt		1b

	/* Initialize .stack */
	ldr     r1,  =__stack_start__
	ldr     r2,  =__stack_end__
	ldr     r3,  =STACK_FILL
1:
	cmp     r1,  r2
	stmltia r1!, {r3}
	blt     1b

	/* Initialize Stack pointer */
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
	msr CPSR_c, #(SYS | I | F)
	ldr sp    , =__sys_stack_top__

	/* Execute static constructors */
	ldr r12, =__libc_init_array
	mov lr, pc
	bx r12

	/* Execute C/C++ main */
	ldr r12, =main
	mov lr, pc
	bx r12

	swi 0xffffff

	.size _bootloader, . - _bootloader
	.endfunc

	.end
