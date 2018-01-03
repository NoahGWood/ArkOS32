#include <kernel/system.h>

/* Defines an IDT entry */
struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;     /* Our kernel segment goes here */
    unsigned char always0;  /* This will always be set to 0 */
    unsigned char flags;    /* Set using the above table */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. If any undefined IDT entry is
* hit, it normally will cause an "Unhandled INterrupt" exception. * Any descriptor for which the 'presence' bit is cleared (0) will
* generate an unhandled interrupt exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* this exists in boot.s and is used to load our IDT */
extern void idt_load();

/* Use this function to set an entry into the IDT. A lot simpler
* than twiddling with the GDT */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFF;
//    idt[num].base_hi = (base >> 24) & 0xFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install() {
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) -1;
    idtp.base = &idtp;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISR'sto the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}
