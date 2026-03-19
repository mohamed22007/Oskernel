#include <n7OS/paging.h>
#include <stddef.h> // nécessaire pour NULL


PageTable page_diectory = NULL ;

void initialise_paging() {
    page_diectory = (PageTable) kmalloc(sizeof(PTE)*1024);
    for (int i = 0; i < 1024; i++) {
        page_diectory[i].value = 0;
    }

    // Charger l'adresse du répertoire de pages dans le registre CR3
    __asm__ __volatile__("mov %0, %%cr3":: "r"(page_diectory));

    // Activer la pagination 
    uint32_t cr0;
    __asm__ __volatile__("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    __asm__ __volatile__("mov %0, %%cr0":: "r"(cr0));
}

PageTable alloc_page_entry(uint32_t address, int is_writeable, int is_kernel) {
    // Allouer l'espace pour ne pas faire planter le noyau
    PageTable pgtab = (PageTable) kmalloc_a(sizeof(PTE));
    
    // Assigner les valeurs selon votre structure
    pgtab->page_entry.present = 1;                     // La page est mappée
    pgtab->page_entry.rw = is_writeable;               // 1 pour rw, 0 pour read-only
    
    pgtab->page_entry.using = (is_kernel == 1) ? 0 : 1; 
    
    pgtab->page_entry.accses = 0;                      // Sera géré par le processeur
    pgtab->page_entry.dirty = 0;                       // Sera géré par le processeur
    pgtab->page_entry.unsed = 0;
    
    
    pgtab->page_entry.page = (address >> 12); 
    
    return pgtab;
}
