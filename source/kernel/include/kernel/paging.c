#include <stdint.h>


extern void loadPageDirectory(uint32_t*);
extern void enablePaging();

void page_init(void) {
    uint32_t page_directory[1024] __attribute__((aligned(4096))); //create a page directory
    //seteach entry to not present
    int i;
    for(i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }
    // Create page tables
    uint32_t first_page_table[1024] __attribute__((aligned(4096)));
    // holds physical address we start mapping
    // for the first we'll map to the very beginning of memory
    unsigned int x;
    // fill all 1024 entries in the table, mapping 4MB
    for(x = 0; x < 1024; x++) {
        first_page_table[x] = (x * 0x1000) | 3;
    }
    // insert page table to page dir
    page_directory[0] = ((unsigned int) first_page_table) | 3;
    loadPageDirectory(page_directory);
    enablePaging();
    printf("Paging Enabled Successfully\n");
}
