//
// Created by lasbo on 02/12/2023.
//

#include "contrainte_exclusions.h"
#include "contrainte_precedences.h"
#include "creation_graph.h"






//░██████╗░██████╗░░█████╗░██████╗░██╗░░██╗
//██╔════╝░██╔══██╗██╔══██╗██╔══██╗██║░░██║
//██║░░██╗░██████╔╝███████║██████╔╝███████║
//██║░░╚██╗██╔══██╗██╔══██║██╔═══╝░██╔══██║
//╚██████╔╝██║░░██║██║░░██║██║░░░░░██║░░██║
//░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░░░░╚═╝░░╚═╝


Graphe* graph_exclusions(t_infos* infos, t_operation** tab_operations) {

    // CREATION ET ALLOCATION DU GRAPH
    Graphe* graphe = (Graphe*) malloc(sizeof(Graphe));
    graphe->taille = infos->max_operations+1;
    graphe->ordre = infos->max_operations+1;
    graphe->orientation = 1;
    graphe->tabSommet = (Sommet**) malloc(sizeof(Sommet*) * graphe->ordre);


    // CREATION ET ALLOCATION DES SOMMETS
    for (int i = 0; i < graphe->ordre; ++i) {
        graphe->tabSommet[i] = (Sommet*) malloc(sizeof(Sommet));
        graphe->tabSommet[i]->valeur = i;
        graphe->tabSommet[i]->is_valid = tab_operations[i]->is_valid;
        graphe->tabSommet[i]->arrete = NULL;
        graphe->tabSommet[i]->etape_traitement = 0;
    }

    // CREATION DES ARETES
    for (int i = 0; i < infos->max_operations; ++i) {
        if (tab_operations[i]->is_valid == 0) continue;
        if (tab_operations[i]->exclusions == NULL) continue;
        graphe->tabSommet[i]->degre = tab_operations[i]->nb_exclusions;
        for (int j = 0; j < tab_operations[i]->nb_exclusions; ++j) {
            graphe->tabSommet[i]->is_valid = 1;
            int id_exclusion = tab_operations[i]->exclusions[j];
            CreerArete(graphe->tabSommet, i, id_exclusion, 1);
        }

    }

    return graphe;

}





//░██████╗░█████╗░██████╗░████████╗
//██╔════╝██╔══██╗██╔══██╗╚══██╔══╝
//╚█████╗░██║░░██║██████╔╝░░░██║░░░
//░╚═══██╗██║░░██║██╔══██╗░░░██║░░░
//██████╔╝╚█████╔╝██║░░██║░░░██║░░░
//╚═════╝░░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░


Graphe* trier_decroissant(Graphe* g) {


    // CREATION D'UN TABLEAU DE SOMMETS
    Sommet** tab_sommet = (Sommet**) malloc(sizeof(Sommet*) * g->ordre);
    for (int i = 0; i < g->ordre; ++i) {
        tab_sommet[i] = g->tabSommet[i];
    }

    // TRIAGE
    for (int i = 0; i < g->ordre; ++i) {
        for (int j = 0; j < g->ordre; ++j) {
            if (tab_sommet[i]->degre > tab_sommet[j]->degre) {
                Sommet* temp = tab_sommet[i];
                tab_sommet[i] = tab_sommet[j];
                tab_sommet[j] = temp;
            }
        }
    }

    // NOUVEAU GRAPHE
    Graphe* g_trie = (Graphe*) malloc(sizeof(Graphe));
    g_trie->taille = g->taille;
    g_trie->ordre = g->ordre;
    g_trie->orientation = g->orientation;
    g_trie->tabSommet = tab_sommet;



    return g_trie;


}



//░█████╗░░█████╗░██╗░░░░░░█████╗░██████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗
//██╔══██╗██╔══██╗██║░░░░░██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
//██║░░╚═╝██║░░██║██║░░░░░██║░░██║██████╔╝███████║░░░██║░░░██║██║░░██║██╔██╗██║
//██║░░██╗██║░░██║██║░░░░░██║░░██║██╔══██╗██╔══██║░░░██║░░░██║██║░░██║██║╚████║
//╚█████╔╝╚█████╔╝███████╗╚█████╔╝██║░░██║██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║
//░╚════╝░░╚════╝░╚══════╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝

int estCouleurValide(Graphe* graphe, int sommet, int couleur) {
    Arrete* arrete = graphe->tabSommet[sommet]->arrete;
    while (arrete != NULL) {
        if (graphe->tabSommet[arrete->sommet]->is_valid && graphe->tabSommet[arrete->sommet]->couleur == couleur) {
            return 0;  // COULEUR UTILISEE
        }
        arrete = arrete->arrete_suivante;
    }
    return 1;  // SUCCES
}

int colorerGrapheExhaustif(Graphe* graphe, int sommet) {
    if (sommet == graphe->ordre) return 1;  // TOUT LES SOMMETS SONT COLORES

    for (int couleur = 0; couleur < graphe->ordre; couleur++) {
        if (estCouleurValide(graphe, sommet, couleur)) {
            graphe->tabSommet[sommet]->couleur = couleur;

            // COLORATION DU PROCHAIN SOMMET
            if (colorerGrapheExhaustif(graphe, sommet + 1)) return 1; // REUSSI

            // PAS REUSSI
            graphe->tabSommet[sommet]->couleur = -1;
        }
    }

    return 0;  // PAS REUSSI
}

int coloration_glouton(Graphe* graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        graphe->tabSommet[i]->couleur = -1;
    }

    // DEBUT COLORATION
    int result = colorerGrapheExhaustif(graphe, 0);

    if (result) { // SI 1, COLORATION REUSSIE
        int maxCouleur = 0;
        for (int i = 0; i < graphe->ordre; i++) {
            if (graphe->tabSommet[i]->is_valid && graphe->tabSommet[i]->couleur > maxCouleur) {
                maxCouleur = graphe->tabSommet[i]->couleur;
            }
        }
        return maxCouleur + 1;
    } else return -1; // SINON, COLORATION IMPOSSIBLE
}



int WelshPowell(Graphe* g) {
    Graphe* g_trie = trier_decroissant(g);
    int colormax = 0;

    // ATTRIBUTION D'UNE COULEUR AU PREMIER SOMMET VALIDE
    for (int i = 0; i < g_trie->ordre; ++i) {
        if (g_trie->tabSommet[i]->is_valid == 0) continue;
        g_trie->tabSommet[i]->couleur = 0;
        break;
    }

    // PARCOURS DES SOMMETS POUR WELSH POWELL
    for (int i = 0; i < g_trie->ordre; ++i) {
        // INITIALISATION DE LA COULEUR
        int couleur = 0;

        // SI LE SOMMET N'EST PAS VALIDE
        if (g_trie->tabSommet[i]->is_valid == 0) continue;

        // PARCOURS DES SOMMETS PRECEDENTS
        Arrete* currentArrete = g_trie->tabSommet[i]->arrete;
        while (currentArrete != NULL) {
            int couleurVoisin = g->tabSommet[currentArrete->sommet]->couleur;
            if (couleurVoisin == couleur) {
                couleur++;  // Incrémente la couleur uniquement si nécessaire
                currentArrete = g_trie->tabSommet[i]->arrete;  // Redémarre la vérification avec la nouvelle couleur
            } else {
                currentArrete = currentArrete->arrete_suivante;
            }
        }

        // AFFECTATION DE LA COULEUR AU SOMMET
        g_trie->tabSommet[i]->couleur = couleur;
        if (couleur > colormax) colormax = couleur;
    }

    // RETOURNE LE NOMBRE DE COULEURS UTILISEES
    return colormax + 1;
}



//░██████╗████████╗░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
//██╔════╝╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
//╚█████╗░░░░██║░░░███████║░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
//░╚═══██╗░░░██║░░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
//██████╔╝░░░██║░░░██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
//╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░


t_station_travail** creation_station_travail_exclusions(Graphe* graphe, t_station_travail** tab_station_travail,t_operation** tab_operations, int nb_station_travail) {

    tab_station_travail = creer_stations_travail(nb_station_travail);

    // ON PARCOURT LE GRAPHE
    for (int i = 0; i < graphe->ordre; ++i) {
        if (graphe->tabSommet[i]->is_valid == 0) continue;
        int couleur = graphe->tabSommet[i]->couleur;
        tab_station_travail[couleur]->nb_operations++;
        //ON REAJUSTE LA TAILLE DU TABLEAU
        tab_station_travail[couleur]->tab_operations = (int*) realloc(tab_station_travail[couleur]->tab_operations, sizeof(int)*tab_station_travail[couleur]->nb_operations);
        tab_station_travail[couleur]->tab_operations[tab_station_travail[couleur]->nb_operations-1] = i;

    }

    // TRANSFERER LES COULEURS DU GRAPHE AU TABLEAU D'OPERATIONS
    for (int i = 0; i < graphe->ordre; ++i) {
        if (graphe->tabSommet[i]->is_valid == 0) continue;
        int couleur = graphe->tabSommet[i]->couleur;
        tab_operations[i]->coloration = couleur;
    }

    afficher_station_travail_coloration(tab_station_travail, tab_operations, nb_station_travail, "EXCLUSIONS");


    return tab_station_travail;


}



//███╗░░░███╗░█████╗░██╗███╗░░██╗
//████╗░████║██╔══██╗██║████╗░██║
//██╔████╔██║███████║██║██╔██╗██║
//██║╚██╔╝██║██╔══██║██║██║╚████║
//██║░╚═╝░██║██║░░██║██║██║░╚███║
//╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝


void contrainte_exclusions(t_infos* infos, t_operation** tab_operations) {

    int max_color = 0;

    Graphe* g = graph_exclusions(infos, tab_operations);
    max_color = WelshPowell(g);
    //max_color = coloration_glouton(g);



    //afficherGrapheColoration(g);
    printf("Nombre de couleurs : %d\n", max_color);


    t_station_travail** tab_station_travail = NULL;
    creation_station_travail_exclusions(g, tab_station_travail, tab_operations, max_color);


}