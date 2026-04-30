#include <inttypes.h>
#include <n7OS/irq.h>
#include <n7OS/segment.h>

extern unsigned long long idt[]; 

void init_irq_entry(int irq_num, uint32_t addr) {
    idt_entry_t *entry = (idt_entry_t *)&idt[irq_num];

    entry->offset_inf = (uint16_t)(addr & 0xFFFF);
    entry->offset_sup = (uint16_t)((addr >> 16) & 0xFFFF);
    entry->sel_segment = KERNEL_CS;
    entry->zero = 0;
    entry->type_attr = 0x8E;
}