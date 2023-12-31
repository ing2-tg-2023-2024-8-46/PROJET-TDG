//
// Created by lasbo on 24/11/2023.
//


#include "contrainte_precedences.h"
#include "creation_graph.h"
#define INF (-1)


//░██████╗░██████╗░░█████╗░██████╗░██╗░░██╗
//██╔════╝░██╔══██╗██╔══██╗██╔══██╗██║░░██║
//██║░░██╗░██████╔╝███████║██████╔╝███████║
//██║░░╚██╗██╔══██╗██╔══██║██╔═══╝░██╔══██║
//╚██████╔╝██║░░██║██║░░██║██║░░░░░██║░░██║
//░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░░░░╚═╝░░╚═╝
//
//██████╗░██████╗░███████╗░█████╗░███████╗██████╗░███████╗███╗░░██╗░█████╗░███████╗░██████╗
//██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝██╔══██╗██╔════╝████╗░██║██╔══██╗██╔════╝██╔════╝
//██████╔╝██████╔╝█████╗░░██║░░╚═╝█████╗░░██║░░██║█████╗░░██╔██╗██║██║░░╚═╝█████╗░░╚█████╗░
//██╔═══╝░██╔══██╗██╔══╝░░██║░░██╗██╔══╝░░██║░░██║██╔══╝░░██║╚████║██║░░██╗██╔══╝░░░╚═══██╗
//██║░░░░░██║░░██║███████╗╚█████╔╝███████╗██████╔╝███████╗██║░╚███║╚█████╔╝███████╗██████╔╝
//╚═╝░░░░░╚═╝░░╚═╝╚══════╝░╚════╝░╚══════╝╚═════╝░╚══════╝╚═╝░░╚══╝░╚════╝░╚══════╝╚═════╝░



Graphe* graph_precedences(t_infos* infos, t_operation** tab_operations) {

    Graphe* graphe = (Graphe*) malloc(sizeof(Graphe));
    graphe->taille = infos->max_operations+1;
    graphe->ordre = infos->max_operations+1;
    graphe->orientation = 1;
    graphe->tabSommet = (Sommet**) malloc(sizeof(Sommet*) * graphe->ordre);



    for (int i = 0; i < graphe->ordre; ++i) {
        graphe->tabSommet[i] = (Sommet*) malloc(sizeof(Sommet));
        graphe->tabSommet[i]->valeur = i;
        graphe->tabSommet[i]->is_valid = tab_operations[i]->is_valid;
        graphe->tabSommet[i]->arrete = NULL;
        graphe->tabSommet[i]->etape_traitement = INF;
    }

    for (int i = 0; i < infos->max_operations; ++i) {
        if (tab_operations[i]->is_valid == 0) continue;
        if (tab_operations[i]->precedences == NULL) continue;
        for (int j = 0; j < tab_operations[i]->nb_precedences; ++j) {
            graphe->tabSommet[i]->is_valid = 1;
            int id_precedent = tab_operations[i]->precedences[j];
            CreerArete(graphe->tabSommet, i, id_precedent, 1);
        }
    }




    return graphe;

}




//██████╗░███████╗░██████╗
//██╔══██╗██╔════╝██╔════╝
//██║░░██║█████╗░░╚█████╗░
//██║░░██║██╔══╝░░░╚═══██╗
//██████╔╝██║░░░░░██████╔╝
//╚═════╝░╚═╝░░░░░╚═════╝░

void DFS_etapes(Graphe* graphe, int id_operation, int etape, int* max_etape) {

    if (graphe->tabSommet[id_operation]->etape_traitement != -1) return;
    graphe->tabSommet[id_operation]->etape_traitement = etape;
    Arrete* arc = graphe->tabSommet[id_operation]->arrete;
    while (arc != NULL) {
        //SI LE SOMMET N'A PAS ETE TRAITE OU SI LE SOMMET EST RELIE A UN SOMMET DEJA TRAITE MAIS AVEC UNE ETAPE PLUS PETITE
        if (graphe->tabSommet[arc->sommet]->etape_traitement <= graphe->tabSommet[id_operation]->etape_traitement) {
            graphe->tabSommet[arc->sommet]->etape_traitement = INF;
            DFS_etapes(graphe, arc->sommet, etape + 1, max_etape);

        }

        arc = arc->arrete_suivante;
    }
    if (etape > *max_etape) *max_etape = etape;

}



//░██████╗████████╗░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
//██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
//╚█████╗░░░░██║░░░███████║░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
//░╚═══██╗░░░██║░░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
//██████╔╝░░░██║░░░██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
//╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░

t_station_travail** creation_station_travail_precedences(Graphe* graphe, t_station_travail** tab_station_travail, int nb_station_travail) {

    tab_station_travail = creer_stations_travail(nb_station_travail);

    // ON PARCOURT LE GRAPHE
    for (int i = 0; i < graphe->ordre; ++i) {
        if (graphe->tabSommet[i]->is_valid == 0) continue;
        int etape = graphe->tabSommet[i]->etape_traitement;
        tab_station_travail[etape]->nb_operations++;
        //ON REAJUSTE LA TAILLE DU TABLEAU
        tab_station_travail[etape]->tab_operations = (int*) realloc(tab_station_travail[etape]->tab_operations, sizeof(int)*tab_station_travail[etape]->nb_operations);
        tab_station_travail[etape]->tab_operations[tab_station_travail[etape]->nb_operations-1] = i;

    }


    afficher_station_travail(tab_station_travail, nb_station_travail, "PRECEDENCES");

    return tab_station_travail;

}



//███╗░░░███╗░█████╗░██╗███╗░░██╗
//████╗░████║██╔══██╗██║████╗░██║
//██╔████╔██║███████║██║██╔██╗██║
//██║╚██╔╝██║██╔══██║██║██║╚████║
//██║░╚═╝░██║██║░░██║██║██║░╚███║
//╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝

void contrainte_precedences(t_infos* infos, t_operation** tab_operations) {

    int max_etape = 0;

    Graphe* g = graph_precedences(infos, tab_operations);
    for (int i = 0; i < infos->max_operations; ++i) {
        if (tab_operations[i]->is_valid == 0) continue;
        DFS_etapes(g, i, 0, &max_etape);
    }

    max_etape++;


    t_station_travail** tab_station_travail = NULL;
    creation_station_travail_precedences(g, tab_station_travail, max_etape);



}


