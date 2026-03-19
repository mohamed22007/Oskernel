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
            
        }
    }
}

/**
 * @brief Initialise le gestionnaire de mémoire physique
 * 
 */
void init_mem() {

}

/**
 * @brief Affiche l'état de la mémoire physique
 * 
 */
void print_mem() {
    
}