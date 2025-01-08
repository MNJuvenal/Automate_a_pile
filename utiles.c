#include <stdio.h>
#include "utiles.h"


int compter_lignes(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    int nb_lignes = 0;
    int caractere;

    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere == '\n') {
            nb_lignes++;
        }
    }

    fclose(fichier);

    return nb_lignes;
}


// Fonction pour calculer la longueur maximale
int calculer_max_length(int nb_etats) {
    int longueur = nb_etats * 2;
    return (longueur > 5) ? longueur : 5; // Retourne le maximum entre 5 et nb_etats * 2
}