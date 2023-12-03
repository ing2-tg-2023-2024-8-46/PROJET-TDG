//
// Created by lasbo on 03/12/2023.
//

#ifndef PROJET_TDG_STATIONS_H
#define PROJET_TDG_STATIONS_H

#include "operations.h"

#include <stdio.h>
#include <stdlib.h>

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

#define R 0
#define G 1
#define B 2
#define Y 3
#define C 4
#define M 5



typedef struct stravail {

    float temps_cycle;

    int coloration;
    int etape_traitement;

    int nb_operations;
    int* tab_operations;

    t_operation** tab_operations_struct;

}t_station_travail;


void afficher_station_travail(t_station_travail** tab_station_travail, int nb_station_travail, char* message);
void afficher_station_travail_coloration(t_station_travail** tab_station_travail,t_operation** tab_operations , int nb_station_travail, char* message);
t_station_travail** creer_stations_travail(int nb_station_travail);

#endif //PROJET_TDG_STATIONS_H
