//
// Created by lasbo on 03/12/2023.
//

#ifndef PROJET_TDG_MULTI_CONTRAINTES_H
#define PROJET_TDG_MULTI_CONTRAINTES_H


#include "operations.h"
#include "creation_graph.h"
#include <stdio.h>
#include <stdlib.h>

void multi_contraintes(t_infos* infos, t_operation** tab_operations);
t_station_travail** creation_station_travail(Graphe* g_precedences, Graphe* g_exclusions, t_infos* infos, t_operation** tab_operations, t_station_travail** tab_station_travail, int max_etape, int max_color, int* nb_station_travail_main);

#endif //PROJET_TDG_MULTI_CONTRAINTES_H
