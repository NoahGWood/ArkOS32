#import <stdint.h>

/* Setup paging in 32Bit Legacy Mode for now.
* In the future, we'll probably want to setup
* PAE and some other things, so let's do our 
* best to comment this code. */

/* Get the ASM */
extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

void paging_install() {
    /* Create a blank page directory */
    uint32_t page_directory[1024] __attribute__((aligned(4096)));
    /* TEMP. Static object, make dynamic ASAP */

    /* Create a blank page table */
    uint32_t first_page_table[1024] __attribute__((aligned(4096)));
    /* TEMP. Static object, make dynamic ASAP */
    int i;
    for(i = 0; i < 1024; i++) {
        /* This sets the following flags to the pages"
         *  Supervisor: Only Kernel-mode can access
         *  Write Enabled: Can both be read from and written to
         *  Not Present: the page table is not present */
        page_directory[i] = 0x00000002;
    }
    /* This function fills each index in the table with an address
     * To which the MMU will map that page. */
    unsigned int x;
    for(x = 0; x < 1024; x++) {
        /* As the address is page aligned, it will always leave
         * 12 bits zeroed. Those bits are used by the attributes. */
        first_page_table[x]= (x * 0x1000) | 3;
        /* Attributes: Supervisor Level, Read/Write, Present. */
    }
    page_directory[0] = ((unsigned int)first_page_table) | 3;
    /* Attributes: Supervisor Level, Read/Write, Present. */
    printf("Loading Page Dir\n");
    loadPageDirectory(page_directory);
    printf("Page Directory Loaded\n");
    printf("Enabling Paging\n");
    enablePaging();
    printf("Paging Enabled\n");
    return;
}
