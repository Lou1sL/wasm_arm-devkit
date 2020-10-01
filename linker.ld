OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_bootloader)

MEMORY { RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 32m }

SECTIONS {

    .reset : {
        *bootloader.o (.text)
    .    = ALIGN(0x4);
    } >RAM

    .text : {
        CREATE_OBJECT_SYMBOLS
        *(.text .text.* .gnu.linkonce.t.*)
        *(.plt)
        *(.gnu.warning)
        *(.glue_7t) *(.glue_7)
        . = ALIGN (4);
        /* These are for static constructors and destructors under ELF */
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))

        *(.rodata .rodata.* .gnu.linkonce.r.*)

        *(.ARM.extab* .gnu.linkonce.armextab.*)
        *(.gcc_except_table)
        *(.eh_frame_hdr)
        *(.eh_frame)

        *(.init)
        *(.fini)

        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >RAM

    /* You could eliminate this section by compiling with -fno-exceptions -fno-unwind-tables */
    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } >RAM
    _etext = .;

    /* No need to copy stuff like on real machine with ROM */
    .data : {
        __data_start = .;
        KEEP(*(.jcr))
        *(.got.plt) *(.got)
        *(.shdata)
        *(.data .data.* .gnu.linkonce.d.*)
        . = ALIGN (4);
        __data_end = .;
    } >RAM

    .bss : {
        __bss_start__ = . ;
        *(.shbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN (4);
        __bss_end__ = .;
    } >RAM

    .stack : {
        __stack_start__ = . ;
        . += 0x0100; . = ALIGN (4); __irq_stack_top__ = . ;
        . += 0x0100; . = ALIGN (4); __fiq_stack_top__ = . ;
        . += 0x0100; . = ALIGN (4); __svc_stack_top__ = . ;
        . += 0x0100; . = ALIGN (4); __abt_stack_top__ = . ;
        . += 0x0100; . = ALIGN (4); __und_stack_top__ = . ;
        . += 0x1000; . = ALIGN (4); __sys_stack_top__ = . ;
        __stack_end__ = .; 
    } >RAM

    .heap : {
        __heap_start = . ;
        KEEP(*(.heap))
        __heap_end = . ;
    } >RAM

    _end = . ;
    __end = . ;
    __end__ = . ;
    PROVIDE(end = .);

    .stab 0 (NOLOAD) : { *(.stab) }
    .stabstr 0 (NOLOAD) : { *(.stabstr) }
}