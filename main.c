#include "main.h"
#include "structure.h"
#include "construire_automate.h"












int main(int argc, char *argv[]) {
   
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <automate> <mot>\n", argv[0]);
        return 1;
    }

    Automate_a_pile *automate = lire_automate(argv[1]);
    printf("etat initial : %d\n",automate->etat_initial);
    printf("symbole de fond de pile : %c\n",automate->symbole_fond_de_pile);

    
    if (automate == NULL) {
        return 1;
    }

    
    executer_automate(automate, argv[2]);

    
    

    free(automate->etats_accepteurs);
    free(automate->transitions);
    free(automate);


    return 0;
}
