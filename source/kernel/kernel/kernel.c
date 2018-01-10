#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/system.h>
#include <kernel/multiboot.h>

void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
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
    int i = 102;
    printf("%s\n", i);
    timer_install();
    keyboard_install();
    for (;;);
}
