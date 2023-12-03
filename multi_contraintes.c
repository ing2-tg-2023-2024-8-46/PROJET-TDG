//
// Created by lasbo on 03/12/2023.
//

#include "stations.h"
#include "operations.h"
#include "multi_contraintes.h"
#include "creation_graph.h"
#include "contrainte_exclusions.h"
#include "contrainte_precedences.h"
#include "contrainte_temps_de_cycle.h"

void creation_station_travail_colore(Graphe* g_precedences, Graphe* g_exclusions, t_infos* infos, t_operation** tab_operations, t_station_travail** tab_station_travail,int max_etape, int max_color) {

    int nb_station_travail = max_etape;
    int stations_en_plus = 0;

    tab_station_travail = creer_stations_travail(nb_station_travail);

    for (int i = 0; i < g_precedences->ordre; ++i) {
        if (g_precedences->tabSommet[i]->is_valid == 0) continue;
        int etape = g_precedences->tabSommet[i]->etape_traitement;
        tab_station_travail[etape]->nb_operations++;
        //ON REAJUSTE LA TAILLE DU TABLEAU
        tab_station_travail[etape]->tab_operations = (int*) realloc(tab_station_travail[etape]->tab_operations, sizeof(int)*tab_station_travail[etape]->nb_operations);
        tab_station_travail[etape]->tab_operations[tab_station_travail[etape]->nb_operations-1] = i;

    }

    afficher_station_travail_coloration(tab_station_travail, tab_operations, nb_station_travail, "PRECEDENCES");


}


float calculer_temps_cycle_station(t_station_travail* station, t_operation** tab_operations) {
    float temps_cycle_total = 0;

    // Parcours de toutes les opérations de la station de travail
    for (int i = 0; i < station->nb_operations; ++i) {
        int operation_index = station->tab_operations[i];
        // Ajout du temps de cycle de chaque opération
        temps_cycle_total += tab_operations[operation_index]->temps_operation;
    }

    return temps_cycle_total;
}



void creation_station_travail(Graphe* g_precedences, Graphe* g_exclusions, t_infos* infos, t_operation** tab_operations, t_station_travail** tab_station_travail, int max_etape, int max_color) {

    int nb_station_travail = max_etape;
    int stations_en_plus = 0;
    int nb_station_travail_total = max_etape;

    tab_station_travail = creer_stations_travail(nb_station_travail);

    for (int i = 0; i < g_precedences->ordre; ++i) {
        if (g_precedences->tabSommet[i]->is_valid == 0) continue;
        int etape = g_precedences->tabSommet[i]->etape_traitement;
        int color = tab_operations[i]->coloration;


        if (tab_station_travail[etape]->nb_operations == 0) {
            tab_station_travail[etape]->coloration = color;
            tab_station_travail[etape]->etape_traitement = etape;
        }


        if (tab_station_travail[etape]->nb_operations != 0) {
            if (tab_station_travail[etape]->coloration != color) {

                // ON VERIFIE SI UNE STATION AVEC LA MEME COULEUR ET LE MEME NUMERO D'ETAPE EXISTE DEJA
                int station_existante = -1;
                for (int j = nb_station_travail_total; j < nb_station_travail + stations_en_plus; ++j) {
                    if (tab_station_travail[j]->coloration == color && tab_station_travail[j]->etape_traitement == etape) {
                        station_existante = j;
                        break;
                    }
                }

                // SI UNE STATION AVEC LA MEME COULEUR ET LE MEME NUMERO D'ETAPE EXISTE DEJA
                if (station_existante != -1) {
                    tab_station_travail[station_existante]->nb_operations++;
                    tab_station_travail[station_existante]->tab_operations = (int*)realloc(tab_station_travail[station_existante]->tab_operations, sizeof(int) * tab_station_travail[station_existante]->nb_operations);
                    tab_station_travail[station_existante]->tab_operations[tab_station_travail[station_existante]->nb_operations - 1] = i;
                }
                // SINON
                else {
                    stations_en_plus++;
                    tab_station_travail = (t_station_travail**)realloc(tab_station_travail, sizeof(t_station_travail*) * (nb_station_travail + stations_en_plus));
                    tab_station_travail[nb_station_travail + stations_en_plus - 1] = (t_station_travail*)malloc(sizeof(t_station_travail));
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations = 0;
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations = NULL;
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->coloration = color;
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->etape_traitement = etape;

                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations++;
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations = (int*)realloc(tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations, sizeof(int) * tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations);
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations[tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations - 1] = i;
                }

                continue;
            }
        }

        tab_station_travail[etape]->nb_operations++;
        tab_station_travail[etape]->tab_operations = (int*)realloc(tab_station_travail[etape]->tab_operations, sizeof(int) * tab_station_travail[etape]->nb_operations);
        tab_station_travail[etape]->tab_operations[tab_station_travail[etape]->nb_operations - 1] = i;
    }

    nb_station_travail += stations_en_plus;
    int nb = 0;


    for (int i = 0; i < nb_station_travail; ++i) {
        // SI LE TEMPS DE CYCLE DE LA STATION DE TRAVAIL EST SUPERIEUR AU TEMPS DE CYCLE MAX
        if (calculer_temps_cycle_station(tab_station_travail[i], tab_operations) > infos->temps_cycle_max) {
            // ON CREE UNE NOUVELLE STATION DE TRAVAIL
            stations_en_plus++;
            tab_station_travail = (t_station_travail**)realloc(tab_station_travail, sizeof(t_station_travail*) * (nb_station_travail + stations_en_plus));
            tab_station_travail[nb_station_travail + stations_en_plus - 1] = (t_station_travail*)malloc(sizeof(t_station_travail));
            tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations = 0;
            tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations = NULL;
            tab_station_travail[nb_station_travail + stations_en_plus - 1]->coloration = tab_station_travail[i]->coloration;
            tab_station_travail[nb_station_travail + stations_en_plus - 1]->etape_traitement = tab_station_travail[i]->etape_traitement;

            // ON RETIRE DES ELEMENTS DU TABLEAU JUSQU'A CE QUE CE SOIT BON
            while (calculer_temps_cycle_station(tab_station_travail[i], tab_operations) > infos->temps_cycle_max) {
                // On transfère une opération de la station i à la nouvelle station créée
                int last_op_index = tab_station_travail[i]->nb_operations - 1;

                // Ajout de l'opération à la nouvelle station
                tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations++;
                tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations =
                        (int*)realloc(tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations,
                                      sizeof(int) * tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations);
                tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations[tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations - 1] =
                        tab_station_travail[i]->tab_operations[last_op_index];

                // On diminue la taille de la station i
                tab_station_travail[i]->nb_operations--;
                tab_station_travail[i]->tab_operations =
                        (int*)realloc(tab_station_travail[i]->tab_operations, sizeof(int) * tab_station_travail[i]->nb_operations);
            }
        }
    }



    afficher_station_travail_coloration(tab_station_travail, tab_operations, nb_station_travail, "PRECEDENCES");
}

void multi_contraintes(t_infos* infos, t_operation** tab_operations) {

    int max_etape = 0;
    int max_color = 0;

    // GRAPH PRECEDENCES
    Graphe* g_precedences = graph_precedences(infos, tab_operations);
    for (int i = 0; i < infos->max_operations; ++i) {
        if (tab_operations[i]->is_valid == 0) continue;
        DFS_etapes(g_precedences, i, 0, &max_etape);
    }
    max_etape++;

    // GRAPH EXCLUSIONS
    Graphe* g_exclusions = graph_exclusions(infos, tab_operations);
    max_color = WelshPowell(g_exclusions);


    t_station_travail** tab_station_travail = NULL;
    creation_station_travail_colore(g_precedences, g_exclusions, infos, tab_operations, tab_station_travail, max_etape, max_color);
    creation_station_travail(g_precedences, g_exclusions, infos, tab_operations, tab_station_travail, max_etape, max_color);

}











/*
void creation_station_travail(Graphe* g_precedences, Graphe* g_exclusions, t_infos* infos, t_operation** tab_operations, t_station_travail** tab_station_travail, int max_etape, int max_color) {

    int nb_station_travail = max_etape;
    int stations_en_plus = 0;
    int nb_station_travail_total = max_etape;

    tab_station_travail = creer_stations_travail(nb_station_travail);

    for (int i = 0; i < g_precedences->ordre; ++i) {
        if (g_precedences->tabSommet[i]->is_valid == 0) continue;
        int etape = g_precedences->tabSommet[i]->etape_traitement;
        int color = tab_operations[i]->coloration;

        if (tab_station_travail[etape]->nb_operations == 0) {
            tab_station_travail[etape]->coloration = color;
        }

        if (tab_station_travail[etape]->nb_operations != 0) {
            if (tab_station_travail[etape]->coloration != color) {

                // Vérifie si une station avec la même couleur existe déjà
                int station_existante = -1;
                for (int j = nb_station_travail_total + etape; j < nb_station_travail + stations_en_plus; ++j) {
                    if (tab_station_travail[j]->coloration == color) {
                        station_existante = j;
                        break;
                    }
                }

                // Si une station existe, ajoute l'opération à cette station
                if (station_existante != -1) {
                    tab_station_travail[station_existante]->nb_operations++;
                    tab_station_travail[station_existante]->tab_operations = (int*)realloc(tab_station_travail[station_existante]->tab_operations, sizeof(int) * tab_station_travail[station_existante]->nb_operations);
                    tab_station_travail[station_existante]->tab_operations[tab_station_travail[station_existante]->nb_operations - 1] = i;
                }
                else {
                    // Sinon, crée une nouvelle station de travail
                    stations_en_plus++;
                    tab_station_travail = (t_station_travail**)realloc(tab_station_travail, sizeof(t_station_travail*) * (nb_station_travail + stations_en_plus));
                    tab_station_travail[nb_station_travail + stations_en_plus - 1] = (t_station_travail*)malloc(sizeof(t_station_travail));
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations = 0;
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations = NULL;
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->coloration = color;

                    // Ajuste la taille du tableau
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations++;
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations = (int*)realloc(tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations, sizeof(int) * tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations);
                    tab_station_travail[nb_station_travail + stations_en_plus - 1]->tab_operations[tab_station_travail[nb_station_travail + stations_en_plus - 1]->nb_operations - 1] = i;
                }

                continue;
            }
        }

        tab_station_travail[etape]->nb_operations++;
        tab_station_travail[etape]->tab_operations = (int*)realloc(tab_station_travail[etape]->tab_operations, sizeof(int) * tab_station_travail[etape]->nb_operations);
        tab_station_travail[etape]->tab_operations[tab_station_travail[etape]->nb_operations - 1] = i;
    }

    afficher_station_travail_coloration(tab_station_travail, tab_operations, nb_station_travail + stations_en_plus, "PRECEDENCES");
}*/


/*
 *     int nb_station_travail = max_etape;
    int stations_en_plus = 0;
    int nb_station_travail_total = max_etape;

    tab_station_travail = creer_stations_travail(nb_station_travail);

    for (int i = 0; i < g_precedences->ordre; ++i) {
        if (g_precedences->tabSommet[i]->is_valid == 0) continue;
        int etape = g_precedences->tabSommet[i]->etape_traitement;
        tab_station_travail[etape]->nb_operations++;
        //ON REAJUSTE LA TAILLE DU TABLEAU
        tab_station_travail[etape]->tab_operations = (int*) realloc(tab_station_travail[etape]->tab_operations, sizeof(int)*tab_station_travail[etape]->nb_operations);
        tab_station_travail[etape]->tab_operations[tab_station_travail[etape]->nb_operations-1] = i;

    }



    // ON TRIE LES TABLEAUX D'OPERATIONS DES STATIONS DE TRAVAIL PAR COULEUR
    for (int i = 0; i < nb_station_travail; ++i) {
        // ON TRIE LE TABLEAU D'OPERATIONS DE LA STATION DE TRAVAIL
        for (int j = 0; j < tab_station_travail[i]->nb_operations; ++j) {
            for (int k = j+1; k < tab_station_travail[i]->nb_operations; ++k) {
                if (tab_operations[tab_station_travail[i]->tab_operations[j]]->coloration > tab_operations[tab_station_travail[i]->tab_operations[k]]->coloration) {
                    int temp = tab_station_travail[i]->tab_operations[j];
                    tab_station_travail[i]->tab_operations[j] = tab_station_travail[i]->tab_operations[k];
                    tab_station_travail[i]->tab_operations[k] = temp;
                }
            }
        }

    }

    // COULEUR DE LA STATION DE TRAVAIL = COULEUR DE LA PREMIERE OPERATION
    for (int i = 0; i < nb_station_travail; ++i) {
        tab_station_travail[i]->coloration = tab_operations[tab_station_travail[i]->tab_operations[0]]->coloration;
    }

 */