#include <kernel/system.h>

/* This will track how many ticks the system has been running for */
int timer_ticks = 0;

/* Handles the timer. Increment timer_ticks every
* time the timer fires. By default, the timer fires 
* 18.222 times per second. */
void timer_handler(struct regs *r) {
    printf("Timer Tick\n");
    /* increment tick count */
    timer_ticks++;
    /* Ever 18 clocks, display a message */
    if (timer_ticks % 18 == 0) {
        printf("One second has passed\n");
    }
}

/* installs timer handler into irq0 */
void timer_install() {
    printf("Installing Timer\n");
    irq_install_handler(0, timer_handler);
}
