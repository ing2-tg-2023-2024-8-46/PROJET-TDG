//
// Created by lasbo on 02/12/2023.
//

#ifndef PROJET_TDG_CREATION_GRAPH_H
#define PROJET_TDG_CREATION_GRAPH_H

#define R 0
#define G 1
#define B 2
#define Y 3
#define C 4
#define M 5

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define GOLD "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RESET_BOLD "\033[21m"
#define RESET_COLOR "\033[39m"


typedef struct Arrete {

    int sommet; // Numero du sommet attaché
    int poids; // Poids de l'arrete
    struct Arrete* arrete_suivante; // Pointeur

}Arrete;

typedef struct Sommet {

    int is_valid;
    int valeur;
    int degre;
    int couleur;
    int etape_traitement;
    Arrete* arrete;

}Sommet;

typedef struct Graphe{

    int taille;
    int ordre;
    int orientation;
    Sommet **tabSommet;

}Graphe;


void CreerArete(Sommet** sommet, int s1, int s2, int poids);
void afficherGraphe(Graphe* g);
void afficherGrapheColoration(Graphe* g);



#endif //PROJET_TDG_CREATION_GRAPH_H
