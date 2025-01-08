#include "structure.h"
#include <stdio.h>



//methode de la structure Pile 
Pile* initialiser_pile() {
    Pile *p = malloc(sizeof(Pile));
    if (p == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }
    p->sommet = NULL;
    p->taille = 0;
    return p;
}

void empiler(Pile *p, char c) {
    Element *nouvel_element = malloc(sizeof(Element));
    if (nouvel_element == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }
    nouvel_element->caractere = c;
    nouvel_element->suivant = p->sommet;
    p->sommet = nouvel_element;
    p->taille++;
}

char depiler(Pile *p) {
    if (p->sommet == NULL) {
        fprintf(stderr, "Erreur : pile vide\n");
        return '\0';
    }
    char c = p->sommet->caractere;
    Element *temp = p->sommet;
    p->sommet = p->sommet->suivant;
    free(temp);
    p->taille--;
    return c;
}bool est_vide(Pile *p) {
    return p->sommet == NULL;
}





char sommet(Pile *p) {
    if (p->sommet == NULL) {
        fprintf(stderr, "Erreur : pile vide\n");
        return '\0';
    }
    return p->sommet->caractere;
}

void liberer_pile(Pile *p) {
    while (!est_vide(p)) {
        depiler(p);
    }
    free(p);
}

void afficher_pile(Pile *p) {
    printf("Etat de la pile du sommet au fond de pile (: ");
    Element *courant = p->sommet;
    while (courant != NULL) {   
        printf("%c ", courant->caractere);
        courant = courant->suivant;
    }
    printf("\n");
}

//methode de la structure Automate a pile

Automate_a_pile* initialiser_automate() {
    Automate_a_pile*a = malloc(sizeof(Automate_a_pile));
    if (a == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }
    a->etat_initial = 0;
    a->symbole_fond_de_pile = '#';
    a->nb_etats = 0;
    printf("automate initialisé\n");
    
    return a;


}


Pile* copier_pile(Pile* original) {
    Pile* temp = initialiser_pile();
    Pile* copie = initialiser_pile();
    
    // Copier dans temp (ordre inversé)
    Element* elem = original->sommet;
    while (elem != NULL) {
        empiler(temp, elem->caractere);
        elem = elem->suivant;
    }
    
    // Copier de temp à copie (ordre restauré)
    while (!est_vide(temp)) {
        empiler(copie, depiler(temp));
    }
    
    liberer_pile(temp);
    return copie;
}


bool  est_etat_accepteur(Automate_a_pile *a, int etat) {
    for (int i = 0; i < a->nb_etats_accepteurs; i++) {
        if (a->etats_accepteurs[i] == etat) {
            return true;
        }
    }
    return false;
}


bool est_un_caractere_special(char c,Automate_a_pile *automate){

    for (int i = 0; i < automate->nb_transitions; i++) {
        Transition *transition = &automate->transitions[i];
        if (transition->caractere_lu == c) {
            return true;
        }
    }
    return false;
}





Transition** trouver_transitions(Automate_a_pile *a, int etat, char caractere_lu, char caractere_depile, int* nb_transitions) {
    Transition** transitions = malloc(sizeof(Transition*) * a->nb_transitions);
    *nb_transitions = 0;

    for (int i = 0; i < a->nb_transitions; i++) {
        Transition *t = &a->transitions[i];
        if (t->eta_depart == etat && 
            (t->caractere_lu == caractere_lu || t->caractere_lu == EPSILON) && 
            (t->caractere_depile == caractere_depile || t->caractere_depile == EPSILON)) {
            transitions[*nb_transitions] = t;
            (*nb_transitions)++;
        }
    }
    if (nb_transitions==0){
        return NULL;
    }
    return transitions;
}

bool executer_automate_recursif(Automate_a_pile* automate, int etat_courant, const char* mot_restant) {
    Pile* pile = automate->Pile;
    
    if (*mot_restant == '\0') {
        // Appliquer les transitions epsilon
        while (true) {
            char caractere_depile = '#';
            int nb_transitions;
            Transition** transitions = trouver_transitions(automate, etat_courant, EPSILON, caractere_depile, &nb_transitions);
            
            if (nb_transitions == 0) break;
            
           
            for (int i = 0; i < nb_transitions; i++) {
                Transition* t = transitions[i];
                Pile* nouvelle_pile = copier_pile(pile);

                // Appliquer la transition
                if (sommet(nouvelle_pile) =='#') {
                    depiler(nouvelle_pile);
                }
                automate->Pile = nouvelle_pile;
                etat_courant=t->etat_arrive;
                printf("mot restant : %s\n", mot_restant);
                printf("etat courant: %d\n",etat_courant);
                
                afficher_pile(nouvelle_pile);
                
                
                if (est_etat_accepteur(automate, etat_courant) && est_vide(nouvelle_pile)) {
                
                return true;
                }
            
            }
            afficher_pile(pile);
            printf("estvide : %d\n",est_vide(pile));
            return false;
        }
        
    }

     char caractere_lu = *mot_restant ;
    int nb_transitions;
    Transition** transitions = trouver_transitions(automate, etat_courant, caractere_lu, sommet(pile), &nb_transitions);
    printf("nb_transitions possible  : %d\n",nb_transitions);
    /*if (nb_transitions==0&&(!est_un_caractere_special(caractere_lu,automate))&&mot_restant[0]!='\0') {
        printf("caractere qui va etre sauter: %c\n",caractere_lu);
        mot_restant++;
        return executer_automate_recursif(automate, etat_courant, mot_restant, pile);

    }*/
        
    for (int i = 0; i < nb_transitions; i++) {
        Transition* t = transitions[i];
        Pile* nouvelle_pile = initialiser_pile();
        
        nouvelle_pile = copier_pile(pile);

        // Appliquer la transition
        if (t->caractere_depile != EPSILON) {
            depiler(nouvelle_pile);
        }
        if (t->caractere_empile != EPSILON) {
            empiler(nouvelle_pile, t->caractere_empile);
        }
        automate->Pile = nouvelle_pile;
        mot_restant++;
        printf("caractere lu : %c\n", caractere_lu);
        printf("caractere depile : %c\n", t->caractere_depile);
        printf("caractere empile : %c\n", t->caractere_empile);
        printf("etat courant: %d\n", t->etat_arrive);
        printf("mot restant : %s\n", mot_restant);
        afficher_pile(nouvelle_pile);
        // Appel récursif
        printf("on est sur un appel recursif \n");
        if (executer_automate_recursif(automate, t->etat_arrive, 
                                        mot_restant  )) {
                
            

            liberer_pile(nouvelle_pile);
            free(transitions);
            return true;
        }

        
    }

    free(transitions);
    
    return false;
    
}

void executer_automate(Automate_a_pile* automate, const char* mot) {
    Pile* pile_initiale = initialiser_pile();
    empiler(pile_initiale, automate->symbole_fond_de_pile);
    automate->Pile = pile_initiale;
    bool resultat = executer_automate_recursif(automate, automate->etat_initial, mot);

    if (resultat) {
        printf("************************\n");
        printf("\033[1;32m Le mot est accepté(: \033[0m\n");

    } else {
        printf("\033[1;31mLe mot est refusé\033[0m\n");
    }

   
}




/*
Transition* trouver_transition(Automate_a_pile *a, int etat, char caractere_lu, char caractere_depile) {
    for (int i = 0; i < a->nb_transitions; i++) {
        Transition *t = &a->transitions[i];
        if (t->eta_depart == etat && (t->caractere_lu == caractere_lu || t->caractere_lu == ' ') && (t->caractere_depile == caractere_depile || t->caractere_depile == ' ')) {
            printf("transition trouvee  %d %c %c %c %d\n",t->eta_depart,t->caractere_lu,t->caractere_depile,t->caractere_empile,t->etat_arrive);
            return t;
        }
    }
      return NULL;
}*/


/*
void executer_transition(EtatExecution *etat_execution, Transition *t) {
    etat_execution->etat_courant = t->etat_arrive;
    if (t->caractere_depile != EPSILON) {

        char sommet = depiler(etat_execution->pile);
        if (sommet != t->caractere_depile) {
            fprintf(stderr, "Erreur : caractère dépilé incorrect\n");
            fflush(stdout);
        }
    }
    if (t->caractere_empile != EPSILON) {
        empiler(etat_execution->pile, t->caractere_empile);
        printf("caractere empile : %c\n",t->caractere_empile);
        fflush(stdout);

    }
    if (t->caractere_lu != EPSILON) {
        etat_execution->mot_restant++;
        printf("caractere lu : %c\n",t->caractere_lu);
        fflush(stdout);

        printf("mot restant : %s\n",etat_execution->mot_restant);
        fflush(stdout);

    }
   
             
    
    if (t->caractere_lu == EPSILON) {
        printf("caractere lu 'epsilon': %c\n",t->caractere_lu);
        fflush(stdout);

        printf("mot restant : %s\n",etat_execution->mot_restant);
        fflush(stdout);

    }
    
}
void  executer_automate(Automate_a_pile* automate, const char* mot) {
    EtatExecution etat_execution;
    etat_execution.automate = automate;
    etat_execution.pile = initialiser_pile();
    empiler(etat_execution.pile, automate->symbole_fond_de_pile);
    etat_execution.etat_courant = 0;
    etat_execution.mot_restant = (char*)mot;
    bool resultat = true;

    while (*etat_execution.mot_restant != '\0') {
        char caractere_lu = etat_execution.mot_restant[0];
        Transition *t = trouver_transition(automate, etat_execution.etat_courant, caractere_lu, sommet(etat_execution.pile));
       if (t== trouver_transition(automate, etat_execution.etat_courant, EPSILON, sommet(etat_execution.pile))&&etat_execution.mot_restant[0]!='\0') {
            t=NULL;
        }
        if (t == NULL) {
            if (est_un_caractere_special(caractere_lu, automate)) {
                printf("Erreur : aucune transition valide pour le caractère spécial %c\n", caractere_lu);
                resultat = false;
                break;
            } else {
                printf("Caractère ignoré : %c\n", caractere_lu);
                etat_execution.mot_restant++;
                continue;
            }
        }
       if (t == NULL&&etat_execution.mot_restant[0]!='\0'&&!est_un_caractere_special(etat_execution.mot_restant[0],automate)) {
            printf("carectere qui va etre sauter: %c\n",caractere_lu);
            etat_execution.mot_restant++;
            continue;
        }
        



        executer_transition(&etat_execution, t);
        printf("caractere depile : %c\n", t->caractere_depile);
        afficher_pile(etat_execution.pile);
    }
   
    Transition *t = trouver_transition(automate, etat_execution.etat_courant, EPSILON, sommet(etat_execution.pile));
   
    if (t != NULL&&(resultat)) {
        printf("lerrur est ici\n");
        executer_transition(&etat_execution, t);
        afficher_pile(etat_execution.pile);
    }
    
    
    resultat = (est_etat_accepteur(automate, etat_execution.etat_courant)) && (est_vide(etat_execution.pile));
    printf("etat_courant : %d\n", etat_execution.etat_courant);
    printf("est etat acepteur : %d\n", est_etat_accepteur(automate, etat_execution.etat_courant));
    printf("est vide : %d\n", est_vide(etat_execution.pile));
    afficher_pile(etat_execution.pile);
    fflush(stdout);

    printf("valeur de resultat : %d\n", resultat);
    fflush(stdout);

    if (resultat) {
        printf("Le mot est accepté\n");
    } else {
        printf("Le mot est refusé\n");
    }
}

void afficher_transition(Transition *t) {
    printf("Transition : %d %c %c %c %d\n", t->eta_depart, t->caractere_lu, t->caractere_depile, t->caractere_empile, t->etat_arrive);
}
*/
 
    


