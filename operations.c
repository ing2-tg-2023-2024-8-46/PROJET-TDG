//
// Created by lasbo on 02/12/2023.
//

#include "operations.h"

void afficher_station_travail(t_station_travail** tab_station_travail, int nb_station_travail, char* message) {

    printf(BOLD"\nCONTRAINTE %s\n"RESET, message);
    for (int i = 0; i < nb_station_travail; ++i) {
        printf("Station de travail %d\n", i);
        //printf("\t - Nombre d'operations : %d\n", tab_station_travail[i]->nb_operations);
        printf("\t - Operations : ");
        for (int j = 0; j < tab_station_travail[i]->nb_operations; ++j) {
            printf("%d ", tab_station_travail[i]->tab_operations[j]);
        }
        printf("\n");
    }

}

