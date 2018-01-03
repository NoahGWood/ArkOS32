# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start

# Setup Page Directories
.global loadPageDirectory
loadPageDirectory:
push %ebp
mov %esp, %ebp
mov 8(%esp), %eax
mov %eax, %cr3
mov %ebp, %esp
pop %ebp
ret

# Enable Paging | SETUP GDT FIRST
.global enablePaging
enablePaging:
push %ebp
mov %esp, %ebp
mov %cr0, %eax
or $0x80000000, %eax
mov %eax, %cr0
mov %ebp, %esp
pop %ebp
ret

# Setup GDT
.global gdt_flush
.extern gp
gdt_flush:
    lgdt gp
    mov %ax, 0x10
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    ret

# Setup Interrupt Descriptor Table
.global idt_load
.extern idtp
idt_load:
    lidt idtp
    ret

# Interrupt Service Routines
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

# 0: Divide By Zero Exception
isr0:
    cli
    push 0 # A normal ISR stub that pops a dummy error code 
                # keep a uniform stack
    push 0
    jmp isr_common_stub

# 1: Debug Exception
isr1:
    cli
    push 0
    push 1
    jmp isr_common_stub

# 2: Non Maskable Interrupt Exception
isr2:
    cli
    push 0
    push 2
    jmp isr_common_stub

# 3: Breakpoint Exception
isr3:
    cli
    push 0
    push 3
    jmp isr_common_stub

# 4: Into Detected Overflow Exception
isr4:
    cli
    push 0
    push 4
    jmp isr_common_stub

# 5: Out of Bounds Exception
isr5:
    cli
    push 0
    push 5
    jmp isr_common_stub

# 6: Invalid Opcode Exception
isr6:
    cli
    push 0
    push 6
    jmp isr_common_stub

# 7: No Coprocessor Exception
isr7:
    cli
    push 0
    push 7
    jmp isr_common_stub

# 8: Double Fault Exception
isr8:
    cli
    push 8
    jmp isr_common_stub

# 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push 0
    push 9
    jmp isr_common_stub

# 10: Bad TSS Exception
isr10:
    cli
    push 10
    jmp isr_common_stub

# 11: Segment Not Present Exception
isr11:
    cli
    push 11
    jmp isr_common_stub

# 12: Stack Fault Exception
isr12:
    cli
    push 12
    jmp isr_common_stub

# 13: General Protection Fault Exception
isr13:
    cli
    push 13
    jmp isr_common_stub

# 14: Page Fault Exception
isr14:
    cli
    push 14
    jmp isr_common_stub

# 15: Unknown Interrupt Exception
isr15:
    cli
    push 0
    push 15
    jmp isr_common_stub

# 16: Coprocessor Fault Exception
isr16:
    cli
    push 0
    push 16
    jmp isr_common_stub

# 17: Alignment Check Exception (486+)
isr17:
    cli
    push 0
    push 17
    jmp isr_common_stub

# 18: Machine Check Exception (Pentium/586+)
isr18:
    cli
    push 0
    push 18
    jmp isr_common_stub

# 19-31: Reserved Exceptions
isr19:
    cli
    push 0
    push 19
    jmp isr_common_stub
isr20:
    cli
    push 0
    push 20
    jmp isr_common_stub
isr21:
    cli
    push 0
    push 21
    jmp isr_common_stub
isr22:
    cli
    push 0
    push 22
    jmp isr_common_stub
isr23:
    cli
    push 0
    push 23
    jmp isr_common_stub
isr24:
    cli
    push 0
    push 24
    jmp isr_common_stub
isr25:
    cli
    push 0
    push 25
    jmp isr_common_stub
isr26:
    cli
    push 0
    push 26
    jmp isr_common_stub
isr27:
    cli
    push 0
    push 27
    jmp isr_common_stub
isr28:
    cli
    push 0
    push 28
    jmp isr_common_stub
isr29:
    cli
    push 0
    push 29
    jmp isr_common_stub
isr30:
    cli
    push 0
    push 30
    jmp isr_common_stub
isr31:
    cli
    push 0
    push 31
    jmp isr_common_stub

# Need to call a C function here to let assembler know
# That 'fault_handler' exists in a nother file
.extern fault_handler

# This is our common ISR stub. It saves the processor stat, sets
# up for kernel mode segments, calls the C-level fault handler
# and finally restores the stack frame.
isr_common_stub:
    pusha
    push    %ds
    push    %es
    push    %fs
    push    %gs
    mov %ax, 0x10    # Load the Kernel Data Segment descriptor
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %eax, %esp    # Push us the stack
    push %eax
    mov %eax, fault_handler
    call %eax        # Special call, preserves the 'eip' register
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add %esp, 8    # Cleans up the error code and pushed ISR number
    iret           # Pops 5 things at once: CS,EIP, EFLAGS, SS, ESP


