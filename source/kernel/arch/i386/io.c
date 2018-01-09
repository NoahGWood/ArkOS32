#include <stdio.h>
#include <kernel/io.h>

/* Input a byte from a port */
inline unsigned char inportb(unsigned short port)
{
   unsigned char ret;
   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   return ret;
}


/* Output a byte to a port */
inline void outportb(unsigned short port,unsigned char data)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (data));
}


/* Stop Interrupts */
inline void stopints()
{
  asm ("cli");
}

