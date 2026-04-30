#include <n7OS/keyboard.h>
#include <n7OS/irq.h>
#include <n7OS/cpu.h>

extern void handler_clavier();

char A = 'R';

void init_keyboard() {
    init_irq_entry(0x21,(uint32_t)handler_clavier);
    outb(inb(0x21) & ~0x02, 0x21);
}

void handler_clavier_C(){
    uint8_t res = inb(0x60);
    if (!(res & 0x80)){
        A = scancode_map[res];
    }
    outb(0x20,0x20);
}

char kgetch() {
    return A;
}