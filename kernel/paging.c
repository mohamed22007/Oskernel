#include <n7OS/paging.h>
#include <stddef.h> // nécessaire pour NULL


PageTable page_diectory = NULL ;

void initialise_paging() {
    // Allouer le répertoire de pages 
    page_diectory = (PageTable) kmalloc_a(sizeof(PTE) * 1024);

    // Initialiser tout à 0
    for (int i = 0; i < 1024; i++) {
        page_diectory[i].value = 0;
    }

    // IDENTITY MAPPING des 16 premiers Mo
    for (int t = 0; t < 4; t++) {
        PageTable table = (PageTable) kmalloc_a(sizeof(PTE) * 1024);
        for (int p = 0; p < 1024; p++) {

            uint32_t addr = (t * 1024 * 4096) + (p * 4096);
            table[p].value = addr | 3; // Present + RW
        }
        // On place la table dans le répertoire
        page_diectory[t].value = ((uint32_t)table & 0xFFFFF000) | 3;
    }

    // Charger CR3
    __asm__ __volatile__("mov %0, %%cr3":: "r"(page_diectory));
    // Activer la pagination
    uint32_t cr0;
    __asm__ __volatile__("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    __asm__ __volatile__("mov %0, %%cr0":: "r"(cr0));
}

PageTable alloc_page_entry(uint32_t address, int is_writeable, int is_kernel) {

    // Récupère la page de la mémoire virtuelle en fonction de l'adresse
    uint32_t pde_index = address >> 22;
    uint32_t pte_index = (address >> 12) & 0x03FF; // masque 10 bits
    
    // Si la table de page n'existe pas encore dans le répertoire, on la crée
    if (page_diectory[pde_index].page_entry.present == 0) {
        PageTable new_table = (PageTable) kmalloc_a(sizeof(PTE) * 1024);
        for(int i = 0; i < 1024; i++) {
            new_table[i].value = 0;
        }
        page_diectory[pde_index].page_entry.present = 1;
        page_diectory[pde_index].page_entry.rw = 1;
        page_diectory[pde_index].page_entry.using = 1;
        page_diectory[pde_index].page_entry.page = ((uint32_t)new_table >> 12);
    }
    
    // On récupère le pointeur vers la table de page correspondante
    PageTable pt = (PageTable) (page_diectory[pde_index].page_entry.page << 12);
    
    // Recherche une page de la mémoire physique libre
    uint32_t phys_page = findfreePage();
    if (phys_page == 0) {
        return NULL; // Plus de mémoire disponible !
    }
    
    // Associe la page physique trouvée à l'adresse virtuelle
    pt[pte_index].page_entry.present = 1;
    pt[pte_index].page_entry.rw = is_writeable;
    pt[pte_index].page_entry.using = (is_kernel == 1) ? 0 : 1;
    pt[pte_index].page_entry.accses = 0;
    pt[pte_index].page_entry.dirty = 0;
    pt[pte_index].page_entry.unsed = 0;
    pt[pte_index].page_entry.page = (phys_page >> 12);


    return pt;
}
