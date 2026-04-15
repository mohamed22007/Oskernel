#include <n7OS/time.h>

uint32_t clk = 0;

void handler_time_C(){
    clk ++;
    outb(0x20,0x20);
}

void init_time(){
    uint16_t frequence = F_OSC / KHZ ;
    clk = 0;
    outb(0x34,0x43);
    outb(frequence & 0xFF,0x40);
    outb((frequence >> 8) & 0xFF, 0x40);
    outb(inb(0x21)&0xfe, 0x21);
}

time heure(){
    time heure;
    heure.seconde = (clk/KHZ)%60;
    heure.minute = (clk/KHZ)/60 ;
    return heure;
}

void afficher_time(time h){
    printf("minute = %d ",h.minute);
    printf("/ seconde = %d ", h.seconde);
}