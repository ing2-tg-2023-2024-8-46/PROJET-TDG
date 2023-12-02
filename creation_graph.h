//
// Created by lasbo on 02/12/2023.
//

#ifndef PROJET_TDG_CREATION_GRAPH_H
#define PROJET_TDG_CREATION_GRAPH_H


typedef struct Arrete {

    int sommet; // Numero du sommet attaché
    int poids; // Poids de l'arrete
    struct Arrete* arrete_suivante; // Pointeur

}Arrete;

typedef struct Sommet {

    int is_valid;
    int valeur;
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



#endif //PROJET_TDG_CREATION_GRAPH_H
