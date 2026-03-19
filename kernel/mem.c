#include <n7OS/mem.h>

uint32_t free_page_tabel[NMB_PAGES/32] = {0};

/**
 * @brief Marque la page allouée
 * 
 * Lorsque la page a été choisie, cette fonction permet de la marquer allouée
 * 
 * @param addr Adresse de la page à allouer
 */
void setPage(uint32_t addr) {
    uint32_t offset = addr / PAGE_SIZE ;
    uint32_t index = offset / 32 ;
    uint32_t bit_index = index %32 ;
    free_page_tabel[index] |= (1 << bit_index);
}

/**
 * @brief Désalloue la page
 * 
 * Libère la page allouée.
 * 
 * @param addr Adresse de la page à libérer
 */
void clearPage(uint32_t addr) {
    uint32_t offset = addr / PAGE_SIZE ;
    uint32_t index = offset / 32 ;
    uint32_t bit_index = index %32 ;
    free_page_tabel[index] &= ~(1 << bit_index);
    
}

/**
 * @brief Fourni la première page libre de la mémoire physique tout en l'allouant
 * 
 * @return uint32_t Adresse de la page sélectionnée
 */
uint32_t findfreePage() {
    for (int i =0 ; i < 128 ; i++){
        if (free_page_tabel[i] != 0xFFFFFFFF){
            for (int j = 0; j < 32; j++) {
                uint32_t bit = 1 << j;
                if (!(free_page_tabel[i] & bit)) {
                    // Calcul de l'adresse physique de la page
                    uint32_t addr = (i * 32 + j) * PAGE_SIZE;
                    
                    // On marque la page comme occupée
                    setPage(addr);
                    
                    return addr;
                }
            }
        }
    }
    return 0 ;
}

/**
 * @brief Initialise le gestionnaire de mémoire physique
 * 
 */
void init_mem() {
    // Initialiser tout le tableau à 0 (0 = page libre)
    for (int i = 0; i < NMB_PAGES / 32; i++) {
        free_page_tabel[i] = 0; 
    }
    
    // on marque la toute première page (adresse 0x0)
    setPage(0);
}

/**
 * @brief Affiche l'état de la mémoire physique
 * 
 */
void print_mem() {
    int free_pages = 0;
    int used_pages = 0;
    
    // Parcourir tout le tableau de bits
    for (int i = 0; i < NMB_PAGES / 32; i++) {
        for (int j = 0; j < 32; j++) {
            uint32_t bit = 1 << j;
            if (free_page_tabel[i] & bit) {
                used_pages++; // Le bit est à 1
            } else {
                free_pages++; // Le bit est à 0
            }
        }
    }
    
    // Affichage des statistiques
    printf("Pages libres   : %d\n", free_pages);
    printf("Pages occupees : %d\n", used_pages);
}