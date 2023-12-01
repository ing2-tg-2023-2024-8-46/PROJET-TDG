//
// Created by lasbo on 24/11/2023.
//


#ifndef PROJET_TDG_CONTRAINTE_PRECEDENCES_H
#define PROJET_TDG_CONTRAINTE_PRECEDENCES_H

#include "operations.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct stravail {

    int nb_operations;
    int* tab_operations;
    t_operation** tab_operations_struct;

}t_station_travail;

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

typedef struct Graphe {

    int taille;
    int ordre;
    int orientation;
    Sommet** tabSommet;

}Graphe;
void contrainte_precedences(t_infos* infos, t_operation** tab_operations);
Graphe* graph_precedences(t_infos* infos, t_operation** tab_operations);
void CreerArete(Sommet** sommet, int s1, int s2, int poids);
void afficherGraphe(Graphe* g);

#endif //PROJET_TDG_CONTRAINTE_PRECEDENCES_H
