#ifndef __IO_H
#define __IO_H
extern unsigned char inportb(unsigned short port);
extern void outportb(unsigned short port, unsigned char data);
extern void stopints(void);
#endif
