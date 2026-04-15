#ifndef __TIME_H__
#define __TIME_H__

#define F_OSC 0x1234BD
#define KHZ 1000

#include <n7OS/cpu.h>
#include <stdio.h>
#include <inttypes.h>

typedef struct 
{
    int minute;
    int seconde;
} time ;

extern uint32_t clk;


void init_time();

time heure();

void afficher_time(time h);

#endif