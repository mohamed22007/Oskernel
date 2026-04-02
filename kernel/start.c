#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>
#include <n7OS/mem.h>  
#include <n7OS/paging.h>  
#include <stddef.h>

void kernel_start(void)
{
    init_console();
    printf("Debut du test de pagination...\n");

    // Initialiser la gestion de la memoire physique
    init_mem();
    print_mem(); // Doit afficher 4095 pages libres 

    // Initialiser la pagination
    initialise_paging();
    printf("Pagination activee avec succes !\n");

    // Tester l'allocation d'une page
    uint32_t v_addr = 0x40000000;
    PageTable test_pt = alloc_page_entry(v_addr, 1, 0);

    // On tente de mapper l'adresse virtuelle 0x40000000
    if (test_pt != NULL) {
        printf("Mapping reussi pour l'adresse 0x%x\n", v_addr);
    }



    // Verifier que la memoire physique a ete consommee
    print_mem(); 

    while (1) {
        hlt();
    }
}