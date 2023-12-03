//
// Created by lasbo on 03/12/2023.
//

#include "stations.h"

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

void afficher_station_travail_coloration(t_station_travail** tab_station_travail,t_operation** tab_operations , int nb_station_travail, char* message) {

    printf(BOLD"\nCONTRAINTE %s\n"RESET, message);
    for (int i = 0; i < nb_station_travail; ++i) {
        printf("Station de travail %d\n", i);
        printf("\t - Temps cycle : %.2f\n", tab_station_travail[i]->temps_cycle);
        //printf("\t - Nombre d'operations : %d\n", tab_station_travail[i]->nb_operations);
        printf("\t - Operations : ");
        for (int j = 0; j < tab_station_travail[i]->nb_operations; ++j) {
            if(tab_operations[tab_station_travail[i]->tab_operations[j]]->coloration == R) printf(RED"%d "RESET, tab_station_travail[i]->tab_operations[j]);
            if(tab_operations[tab_station_travail[i]->tab_operations[j]]->coloration == G) printf(GREEN"%d "RESET, tab_station_travail[i]->tab_operations[j]);
            if(tab_operations[tab_station_travail[i]->tab_operations[j]]->coloration == B) printf(BLUE"%d "RESET, tab_station_travail[i]->tab_operations[j]);
            if(tab_operations[tab_station_travail[i]->tab_operations[j]]->coloration == Y) printf(GOLD"%d "RESET, tab_station_travail[i]->tab_operations[j]);
            if(tab_operations[tab_station_travail[i]->tab_operations[j]]->coloration == C) printf(CYAN"%d "RESET, tab_station_travail[i]->tab_operations[j]);
            if(tab_operations[tab_station_travail[i]->tab_operations[j]]->coloration == M) printf(MAGENTA"%d "RESET, tab_station_travail[i]->tab_operations[j]);
        }
        printf("\n");
    }

}


t_station_travail** creer_stations_travail(int nb_station_travail) {

    t_station_travail** tab_station_travail = (t_station_travail**) malloc(sizeof(t_station_travail*)*nb_station_travail);
    if (tab_station_travail == NULL) {
        printf("[creer_stations_travail] Erreur d'allocation memoire\n");
        exit(1);
    }

    if (nb_station_travail == 0) {
        printf("[creer_stations_travail] Erreur : nb_station_travail = 0\n");
        exit(1);
    }

    for (int i = 0; i < nb_station_travail; ++i) {
        tab_station_travail[i] = (t_station_travail*) malloc(sizeof(t_station_travail));
        tab_station_travail[i]->nb_operations = 0;
        tab_station_travail[i]->tab_operations = NULL;
        tab_station_travail[i]->temps_cycle = 0;
    }

    return tab_station_travail;

}