#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <stdio.h>

extern void handler_IT();
extern void handler_time();
extern void handler_syscall();


void init_irq() {
    init_irq_entry(50, (uint32_t)handler_IT);
    init_irq_entry(0x20,(uint32_t)handler_time);
}

void handler_en_C() {
    printf("Interputation ! \n");
}
