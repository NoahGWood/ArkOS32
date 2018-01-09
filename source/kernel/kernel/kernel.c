#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/system.h>

void kernel_main(void) {
    terminal_initialize();
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    __asm__ __volatile__ ("sti");
    printing_test();
	printf("Welcome to ArkOS!\n");
    printf("We are currently undergoing some development.\n");
    printf("Pardon our dust\n");
    timer_install();
    for (;;);
}
