//
// Created by lasbo on 24/11/2023.
//


#ifndef PROJET_TDG_CONTRAINTE_PRECEDENCES_H
#define PROJET_TDG_CONTRAINTE_PRECEDENCES_H

#include "operations.h"
#include "creation_graph.h"
#include <stdio.h>
#include <stdlib.h>

// PERMET DE CREER UN GRAPHE A PARTIR DES PRECEDENCES
Graphe* graph_precedences(t_infos* infos, t_operation** tab_operations);


// DFS POUR LES PRECEDENCES
// - Permet de trouver le nombre d'etapes max
void DFS_etapes(Graphe* graphe, int id_operation, int etape, int* max_etape);
// PERMET DE CREER LES STATIONS DE TRAVAIL EN FONCTION DES PRECEDENCES
void creation_station_travail_precedences(Graphe* graphe, t_station_travail** tab_station_travail, int nb_station_travail);
// FONCTION A APPELER POUR RESPECTER LA CONTRAINTE DES PRECEDENCES
void contrainte_precedences(t_infos* infos, t_operation** tab_operations);



#endif //PROJET_TDG_CONTRAINTE_PRECEDENCES_H
