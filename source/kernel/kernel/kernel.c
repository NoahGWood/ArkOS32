#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Welcome to ArkOS!\n");
    printf("We are currently undergoing some development.\n");
    printf("Pardon our dust");
}
