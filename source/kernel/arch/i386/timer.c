#include <kernel/system.h>

/* This will track how many ticks the system has been running for */
int timer_ticks = 0;
/* This will track the number of seconds the system has been running for */
int seconds;
seconds = 0;

void timer_phase(int hz) {
    int divisor = 1193180 / hz;       /* Calculate divisor */
    outportb(0x43, 0x36);             /* Set command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}
		

/* Handles the timer. Increment timer_ticks every
* time the timer fires. By default, the timer fires 
* 18.222 times per second. */
void timer_handler(struct regs *r) {
    /* increment tick count */
    timer_ticks++;
    /* Every second print a message */
    if (timer_ticks % 100 == 0) {
        seconds++;
        char c = seconds;
//        printf("%c Seconds Since Boot\n", c);
    }
}

/* installs timer handler into irq0 */
void timer_install() {
    printf("Installing Timer\n");
    irq_install_handler(0, timer_handler);
    timer_phase(100);
}
