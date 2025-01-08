# Automate_a_pile

Objectif:

Ce projet vise à implémenter en C un type de données abstrait pour les automates à pile, accompagné d'une fonction d'exécution. L'objectif est double : créer une structure de données efficace et développer un algorithme simulant le comportement de ces automates.

Le fichier texte represantant l'autoate  indique donc sur une première ligne le nombre d’états, sur une
deuxième les états accepteurs séparés par des espaces,
puis pour chaque transition, les cinq valeurs qui la définissent sont 
(eta_depart; caractere_lu;caractere_depile; etat_arrive;caractere_empile;).
le mot vide est representé par  un espace exemple de transiton 
0 b   0 i \ si on est a l'etat 0 et on lit b on passe a l'etat 0 et on empile idans la pile .

Pour pouvoir executer et tester le code :

  *Placer vous dans le dossier  principale 
  *taper "make clean" et/ou "make"
  *taper ./AP "le_fichier_texte_represantant l'automate" "le_mot_a_tester_"   
un automate a tester est disponible et il reconais les mots de la forme b^n.a^n .

donc il suffit de Taper  [  ./AP  "test.txt" "bbbaaa"  ] 
