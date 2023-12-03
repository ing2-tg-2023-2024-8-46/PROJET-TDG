//
// Created by lasbo on 03/12/2023.
//

#ifndef PROJET_TDG_COUTS_DEVELOPPEMENT_H
#define PROJET_TDG_COUTS_DEVELOPPEMENT_H

#include "stations.h"
#include "operations.h"
#include "creation_graph.h"
#include "contrainte_exclusions.h"
#include "contrainte_precedences.h"
#include "contrainte_temps_de_cycle.h"
#include <stdio.h>
#include <stdlib.h>

void simulation_couts_de_developpements(t_infos* infos, t_operation** tab_operations);

#endif //PROJET_TDG_COUTS_DEVELOPPEMENT_H
