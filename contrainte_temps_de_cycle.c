//
// Created by lasbo on 02/12/2023.
//

#include "contrainte_temps_de_cycle.h"


//░██████╗████████╗░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
//██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
//╚█████╗░░░░██║░░░███████║░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
//░╚═══██╗░░░██║░░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
//██████╔╝░░░██║░░░██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
//╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░

void creation_station_travail_temps_cycle(t_infos* infos, t_operation** tab_operations, t_station_travail** tab_station_travail) {

    int nb_station_travail = 0;
    tab_station_travail = creer_stations_travail(1);

    // TANT QUE TEMPS CYCLE + TEMPS OPERATION ACTUELLE < TEMPS CYCLE MAX
    // ON AJOUTE UNE OPERATION A LA STATION DE TRAVAIL
    // SI ON DEPASSE LE TEMPS CYCLE MAX, ON CREE UNE NOUVELLE STATION DE TRAVAIl

    for (int i = 0; i < infos->max_operations+1; ++i) {
        if (tab_operations[i]->is_valid == 0) continue;

        // VERIFIE SI ON DEPASSE LE TEMPS CYCLE MAX
        if (tab_operations[i]->temps_operation + tab_station_travail[nb_station_travail]->temps_cycle > infos->temps_cycle_max) {
            // CREATION D'UNE NOUVELLE STATION DE TRAVAIL
            nb_station_travail++;
            tab_station_travail = (t_station_travail**) realloc(tab_station_travail, sizeof(t_station_travail*)*(nb_station_travail+1));
            tab_station_travail[nb_station_travail] = (t_station_travail*) malloc(sizeof(t_station_travail));
            tab_station_travail[nb_station_travail]->nb_operations = 0;
            tab_station_travail[nb_station_travail]->tab_operations = NULL;
            tab_station_travail[nb_station_travail]->temps_cycle = 0;
        }

        // ON AJOUTE L'OPERATION A LA STATION DE TRAVAIL
        tab_station_travail[nb_station_travail]->nb_operations++;
        tab_station_travail[nb_station_travail]->tab_operations = (int*) realloc(tab_station_travail[nb_station_travail]->tab_operations, 
            sizeof(int)*tab_station_travail[nb_station_travail]->nb_operations);
        tab_station_travail[nb_station_travail]->tab_operations[tab_station_travail[nb_station_travail]->nb_operations-1] = i;
        tab_station_travail[nb_station_travail]->temps_cycle += tab_operations[i]->temps_operation;
    }

    //POUR AVOIR LE NOMBRE DE STATIONS DE TRAVAIL REEL
    nb_station_travail++;

    afficher_station_travail(tab_station_travail, nb_station_travail, "TEMPS DE CYCLE");



}

//███╗░░░███╗░█████╗░██╗███╗░░██╗
//████╗░████║██╔══██╗██║████╗░██║
//██╔████╔██║███████║██║██╔██╗██║
//██║╚██╔╝██║██╔══██║██║██║╚████║
//██║░╚═╝░██║██║░░██║██║██║░╚███║
//╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝

void contrainte_temps_de_cycle(t_infos* infos, t_operation** tab_operations) {


    t_station_travail** tab_station_travail = NULL;
    creation_station_travail_temps_cycle(infos, tab_operations, tab_station_travail);



}

