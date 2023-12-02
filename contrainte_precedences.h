//
// Created by lasbo on 24/11/2023.
//


#ifndef PROJET_TDG_CONTRAINTE_PRECEDENCES_H
#define PROJET_TDG_CONTRAINTE_PRECEDENCES_H

#include "operations.h"
#include "creation_graph.h"
#include <stdio.h>
#include <stdlib.h>

Graphe* graph_precedences(t_infos* infos, t_operation** tab_operations);

void etape_traitement(Graphe* graphe, int id_operation, int etape, int* max_etape);
void creation_station_travail(Graphe* graphe, t_station_travail** tab_station_travail, int nb_station_travail);
void contrainte_precedences(t_infos* infos, t_operation** tab_operations);



#endif //PROJET_TDG_CONTRAINTE_PRECEDENCES_H
