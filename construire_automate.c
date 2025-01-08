#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utiles.h"







Automate_a_pile* lire_automate(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    Automate_a_pile* automate = initialiser_automate();
    if (automate == NULL) {
        fclose(file);
        return NULL;
    }

    int MAX_SYMBOL_LENGTH = 100; // Augmenter la taille pour lire des lignes plus longues
    char line[MAX_SYMBOL_LENGTH];

    // Lire le nombre d'états
    if (fgets(line, sizeof(line), file) == NULL) {
        free(automate);
        fclose(file);
        return NULL;
    }
    sscanf(line, "%d", &automate->nb_etats);

    // Lire les états accepteurs
    if (fgets(line, sizeof(line), file) == NULL) {
        free(automate);
        fclose(file);
        return NULL;
    }
    automate->etats_accepteurs = malloc(automate->nb_etats * sizeof(int));
    automate->nb_etats_accepteurs = 0;

    char *ptr = line;
    int etat;

    while (sscanf(ptr, "%d", &etat) == 1) {
        automate->etats_accepteurs[automate->nb_etats_accepteurs++] = etat;
        ptr = strchr(ptr, ' ');
        if (ptr == NULL) break;
        ptr++; // Passer l'espace
    }

    // Compter le nombre total de lignes dans le fichier
    int total_lignes = compter_lignes(filename);

    // Le nombre de transitions est égal au nombre total de lignes moins 2 (états + états accepteurs)
    automate->nb_transitions = total_lignes ; // -2 pour le nombre d'états et les états accepteurs
    automate->transitions = malloc(automate->nb_transitions * sizeof(Transition));

    // Lire les transitions à partir de la troisième ligne
    automate->nb_transitions = 0; // Initialiser le compteur de transitions
    while (fgets(line, sizeof(line), file) != NULL) {
            Transition t;

            int eta_depart, etat_arrive;
            char caractere_lu, caractere_depile, caractere_empile;
            
            char *ptr = line;
            eta_depart = strtol(ptr, &ptr, 10);
            ptr++; // Ignorer l'espace
            caractere_lu = *ptr;
            ptr += 2; // Ignorer le caractère lu et l'espace
            caractere_depile = *ptr;
            ptr += 2; // Ignorer le caractère dépilé et l'espace
            etat_arrive = strtol(ptr, &ptr, 10);
            ptr++; // Ignorer l'espace
            caractere_empile =  *ptr;



            t.eta_depart = eta_depart;
            t.caractere_lu = caractere_lu;
            t.caractere_depile = caractere_depile;
            t.caractere_empile = caractere_empile;
            t.etat_arrive = etat_arrive;

            automate->transitions[automate->nb_transitions++] = t;
            printf("Transition %d: %d %c %c %d %c\n", automate->nb_transitions, eta_depart, t.caractere_lu, t.caractere_depile,etat_arrive, t.caractere_empile);
        }    


    fclose(file);
    return automate;

}
