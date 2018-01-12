#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/system.h>
#include <kernel/multiboot.h>

typedef struct multiboot_memory_map_t {
	unsigned int size;
	unsigned int base_addr_low,base_addr_high;
// You can also use: unsigned long long int base_addr; if supported.
	unsigned int length_low,length_high;
// You can also use: unsigned long long int length; if supported.
	unsigned int type;
};

void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
    /* setup paging first */
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
    keyboard_install();
    multiboot_memory_map_t* mmap = mbd->mmap_addr;
	while(mmap < mbd->mmap_addr + mbd->mmap_length) {
		mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
	}
    paging_install();
    for (;;);
}
