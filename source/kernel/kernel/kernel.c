#include <stdio.h>
#include <kernel/tty.h>

#include "kernel/gdt.c"
#include "kernel/paging.c"
#include "kernel/idt.c"
#include "kernel/isrs.c"
#include "kernel/test.c"

void kernel_main(void){
    gdt_install();
    isrs_install();
   	terminal_initialize();
    page_init();
	printf("\nWelcome to ArkOS!\n");
    printf("We are currently undergoing some development.\n");
    printf("Pardon our dust\n");
}
