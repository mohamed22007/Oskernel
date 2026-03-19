#include <n7OS/console.h>
#include "../include/n7OS/cpu.h"

uint16_t *scr_tab;
uint16_t curs_pos = 0 ;

void init_console() {
    scr_tab= (uint16_t *) SCREEN_ADDR;
    // Effacer tout l'écran
    for (int i = 0; i < 80 * 25; i++) {
        scr_tab[i] = CHAR_COLOR << 8 | ' ';
    }
    
    curs_pos = 0;
    pos_curseur(0);
}

// Position de le curseur sur l'ecran
void pos_curseur(uint16_t pos ){
    outb(0xF,0x3D4);
    outb((uint8_t) (pos & 0xFF),0x3D5);

    outb(0xE,0x3D4);
    outb((uint8_t) ((pos >> 8) & 0xFF),0x3D5);

}

// Console pour afficher des carcteres
void console_putchar(const char c) {
    if (c > 31 && c < 127) {
        scr_tab[curs_pos]= CHAR_COLOR<<8|c;
        curs_pos += 1 ;
        pos_curseur(curs_pos);}
    // Retour a la ligne
    else if (c == '\n'){
        curs_pos = ((curs_pos/80 + 1)*80);
        pos_curseur(curs_pos);
    }
    // Retour une case
    else if (c == '\b'){
        if (curs_pos != 0){
            curs_pos = curs_pos - 1 ;
        }
        pos_curseur(curs_pos);
    }
    // Decalage en avance 
    else if (c == '\t'){
        curs_pos = curs_pos + 1;
        pos_curseur(curs_pos);
    }
    // Retour au debut de ligne 
    else if (c == '\r'){
        curs_pos = (curs_pos / 80) * 80;
        pos_curseur(curs_pos);
    // Effacer Tout
    } else if (c == '\f'){
        curs_pos = 0 ;
        pos_curseur(0);
        for (int i = 0; i < 80*25 ; i++){
            scr_tab[i] = CHAR_COLOR<<8|' ';
        }
    }
}

// Fonction pour affcher une chane de caractere 
void console_putbytes(const char *s, int len) {
    for (int i= 0; i<len; i++) {
        console_putchar(s[i]);
    }
}