#include <stdio.h>

#include <kernel/tty.h>
#include "kernel/paging.c"

void kernel_main(void) {
    page_init();
	terminal_initialize();
	printf("Welcome to ArkOS!\n");
    printf("We are currently undergoing some development.\n");
    printf("Pardon our dust\n");
}
