//
// Created by lasbo on 02/12/2023.
//

#ifndef PROJET_TDG_CONTRAINTE_EXCLUSIONS_H
#define PROJET_TDG_CONTRAINTE_EXCLUSIONS_H

#include "stations.h"
#include "operations.h"
#include "creation_graph.h"
#include <stdio.h>
#include <stdlib.h>


// PERMET DE CREER UN GRAPHE A PARTIR DES EXCLUSIONS
Graphe* graph_exclusions(t_infos* infos, t_operation** tab_operations);
// PERMET DE TRIER LES SOMMETS DU GRAPHE EN FONCTION DE LEUR DEGRE
Graphe* trier_decroissant(Graphe* g);

// FONCTION A APPELER POUR RESPECTER LA CONTRAINTE DES EXCLUSIONS
void contrainte_exclusions(t_infos* infos, t_operation** tab_operations);
// PERMET DE CREER LES STATIONS DE TRAVAIL EN FONCTION DES EXCLUSIONS
void creation_station_travail_exclusions(Graphe* graphe, t_station_travail** tab_station_travail,t_operation** tab_operations, int nb_station_travail);
// ALGO DE WELSH POWELL
int WelshPowell(Graphe* g);


#endif //PROJET_TDG_CONTRAINTE_EXCLUSIONS_H
