#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>
#include <n7OS/mem.h>  
#include <n7OS/paging.h>  
#include <stddef.h>
#include <n7OS/time.h>
#include <unistd.h>
#include <n7OS/sys.h>

extern void handler_IT();



void kernel_start(void)
{
    init_console();
    setup_base(0);
    init_time();
    
    // Initialiser la gestion de la memoire physique
    init_mem();
    
    // Initialiser la pagination
    initialise_paging();
    
    // Tester l'allocation d'une page
    uint32_t v_addr = 0x40000000;
    PageTable test_pt = alloc_page_entry(v_addr, 1, 0);

    // Initialiser le handler d'interruptions
    init_irq();

    uint32_t last_clk = clk;
    // On efface l'écran EN PREMIER
            printf("\f");

            // On affiche tout l'état du système
            printf("Test handler : \n");
            __asm__ __volatile__("int $50");

            // On tente de mapper l'adresse virtuelle
            if (test_pt != NULL) {
                printf("Addresse : 0x%x\n", v_addr);
            }

            

    // Verifier que la memoire physique a ete consommee
    print_mem(); 

    init_syscall();
    sti();

    if (example() == 1){
        printf ( "Appel systeme example ok \n" );
    }

    

    while (1) {

        if (last_clk != clk) {
            last_clk = clk;

            // Afficher l'heure
            afficher_time(heure());
            printf("\r");
            
        }
        hlt();
    }
}