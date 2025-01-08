#ifndef PILE_H
#define PILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define EPSILON  ' '


//structure de la pile

typedef struct Element {
    char caractere;
    struct Element *suivant;
} Element;

typedef struct {
    Element *sommet;
    int taille;
} Pile;



//structure de l'automate a pile

typedef struct {
    int eta_depart;
    char caractere_lu;
    char caractere_depile;
    int etat_arrive;
    char caractere_empile;
    
} Transition;


typedef struct {
    int nb_etats; //Q ensemble des etats comme on par de 0 il suffit de trouver le dernier etat 
    int nb_transitions;  
    int nb_etats_accepteurs; 
    int *etats_accepteurs; //F ensemble des etats accepteurs
    Transition *transitions; // deltat ensemble des transitions
    char symbole_fond_de_pile; //Z symbole de fond de pile
    int etat_initial ; //s etat initial de l'automate
    Pile *Pile;

} Automate_a_pile;

/*typedef struct {
    Automate_a_pile  *automate;
    Pile *pile;
    int etat_courant;
    char *mot_restant;
} EtatExecution;*/

//prototypes des fonctions de l'automate a pile

Automate_a_pile* initialiser_automate();
bool  est_etat_accepteur(Automate_a_pile *a, int etat);
bool est_etat_initial(Automate_a_pile *a, int etat);
Transition* trouver_transition(Automate_a_pile *a, int etat, char caractere_lu, char caractere_depile);
//void executer_transition(EtatExecution *etat_execution, Transition *t);
bool executer_automate_recursif(Automate_a_pile* automate, int etat_courant, const char* mot_restant) ;

void  executer_automate(Automate_a_pile* automate, const char* mot);
void liberer_automate(Automate_a_pile* automate);
void afficher_transition(Transition *t );
bool est_un_caractere_special(char c,Automate_a_pile *automate);


//prototypes des fonctions de la Pile 
Pile* initialiser_pile();
void empiler(Pile *p, char c);
char depiler(Pile *p);
bool est_vide(Pile *p);
char sommet(Pile *p);
void liberer_pile(Pile *p);
void afficher_pile(Pile *p);
Automate_a_pile* lire_automate(const char *nom_fichier);
Pile* copier_pile(Pile *p);


#endif // PILE_H
