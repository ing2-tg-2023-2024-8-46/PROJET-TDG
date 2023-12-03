//
// Created by lasbo on 03/12/2023.
//

#include "couts_developpement.h"
#include "creation_graph.h"
#include "multi_contraintes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

void simulation_couts_de_developpements(t_infos* infos, t_operation** tab_operations) {

    int max_etape = 0;
    int max_color = 0;

    printf("\n\n");

    float prix_terrain = 0;
    float prix_station_travail = 0;
    float prix_operation = 0;
    float prix_de_vente = 0;
    float couts_exploitation = 0;
    int volume_prod_mensuelle = 0;
    float consommation_electrique_mensuelle = 0;
    float couts_prod_unite = 0;





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


    int nb_station_travail = 0;
    t_station_travail** tab_station_travail = NULL;
    tab_station_travail = creation_station_travail(g_precedences, g_exclusions, infos, tab_operations, tab_station_travail, max_etape, max_color, &nb_station_travail);

    for (int i = 0; i < 10; ++i) {
        printf("\n");
    }

    printf(BOLD"SIMULATION COUTS DE DEVELOPPEMENT\n");
    printf("=================================\n\n"RESET);
    printf("Bienvenu dans votre outil de simulation de couts de developpement.\n");
    printf("Vous allez pouvoir simuler les couts de developpement de votre projet.\n");
    printf("Pour cela, nous allons vous demander de rentrer les informations suivantes:\n\n");
    printf("\nCONSTRUCTION\n");
    printf(BOLD"Prix du terrain (en millions d'euros): ");
    scanf("%f", &prix_terrain);
    printf("\nPrix de construction d'une station de travail (en millions d'euros): ");
    scanf("%f", &prix_station_travail);
    printf("\nPrix d'une operation (en millions d'euros): ");
    scanf("%f", &prix_operation);
    printf("\nVENTE");
    printf("\nPrix de vente d'un produit (en euros): ");
    scanf("%f", &prix_de_vente);
    printf("\nVolume de production mensuel (en milliers d'unites): ");
    scanf("%d", &volume_prod_mensuelle);
    printf("\nCOUTS D'EXPLOITATION");
    printf("\nCout de production pour une unite (en euros): ");
    scanf("%f", &couts_prod_unite);
    printf("\nCouts d'exploitation mensuel (en milliers d'euros): "RESET);
    scanf("%f", &couts_exploitation);
    printf("\nConsommation electrique mensuelle (en kWh): ");
    scanf("%f", &consommation_electrique_mensuelle);

    printf("\n\n");

    printf("RECAPITULATIF DES INFORMATIONS\n");
    printf("==============================\n\n");
    printf("Prix du terrain : %.2fm €\n", prix_terrain);
    printf("Prix de construction d'une station de travail : %.2fm €\n", prix_station_travail);
    printf("Prix d'une operation : %.2fm €\n", prix_operation);
    printf("Prix de vente d'un produit : %.2f €\n", prix_de_vente);
    printf("Volume de production mensuel : %dk unités\n", volume_prod_mensuelle);
    printf("Couts d'exploitation mensuel : %.2fk €\n", couts_exploitation);
    printf("Cout de production d'1 unite : %.2f €\n", couts_prod_unite);
    printf("Consommation electrique mensuelle : %.2f kWh\n", consommation_electrique_mensuelle);
    printf("\n\n");

    printf("Calcul des couts de developpement");
    // PRINT TOUTES LES X SECONDES ENTRE 0.3 ET 0.5

    for (int i = 0; i < 5; ++i) {
        printf(".");
        fflush(stdout);
        usleep((rand() % 500000) + 50000);
    }

    printf("\n\n");

    float cout_terrains = (float) nb_station_travail * prix_terrain;
    float cout_stations_travail = (float) nb_station_travail * prix_station_travail;
    float cout_developpement = 0;



    printf("\n");
    printf(BOLD"---------------------\n");
    printf("COUTS DE CONSTRUCTION\n");
    printf("---------------------\n\n"RESET);
    printf("Cout des terrains : "BOLD"%.2fm €"RESET" [%.2f X %d]\n", cout_terrains, prix_terrain, nb_station_travail);
    printf("Cout de construction "BOLD"des stations : %.2fm € \"RESET\" [%.2f X %d]\n", cout_stations_travail, prix_station_travail, nb_station_travail);
    printf("\n");
    float cout_construction = cout_terrains + cout_stations_travail;
    printf(BOLD"Cout total de construction : %.2fm €\n"RESET, cout_construction);


    printf("\n");
    printf(BOLD"---------------------\n");
    printf("COUTS DE DEVELOPPEMENT\n");
    printf("----------------------\n\n"RESET);

    for (int i = 0; i < nb_station_travail; ++i) {
        if (i<9) printf("STATION 0%d : "BOLD"%.2fm €"RESET" [%.2f X %d]\n", i+1, (float) tab_station_travail[i]->nb_operations * prix_operation, prix_operation, tab_station_travail[i]->nb_operations);
        else printf("STATION %d : "BOLD"%.2fm €"RESET" [%.2f X %d]\n", i+1, (float) tab_station_travail[i]->nb_operations * prix_operation, prix_operation, tab_station_travail[i]->nb_operations);
        cout_developpement += (float) tab_station_travail[i]->nb_operations * prix_operation;
    }
    printf("\n");
    printf(BOLD"Cout total de developpement : %.2fm €\n"RESET, cout_developpement);


    float cout_construction_total = cout_construction + cout_developpement;
    printf(BOLD"TOTAL : %.2fm €\n"RESET, cout_construction_total);



    printf("\n");
    printf(BOLD"---------------------\n");
    printf("BENEFICE\n");
    printf("----------------------\n\n"RESET);

    float chiffre_affaire_en_euros = (float) (12 * 1000 * volume_prod_mensuelle) * prix_de_vente;
    float cout_unitaire =  (float) (12 * 1000 * volume_prod_mensuelle) * couts_prod_unite;
    float chiffre_affaire_en_millions = (chiffre_affaire_en_euros - cout_unitaire) / 1000000;
    printf("Chiffre d'affaire par an : "BOLD"%.2fm € "RESET" [%.2f - %.2f X %d]\n", chiffre_affaire_en_millions, chiffre_affaire_en_euros, couts_prod_unite, volume_prod_mensuelle);


    float couts_exploitation_en_milliers = (12 * couts_exploitation);
    printf("Couts d'exploitation par an : "BOLD"%.2fk €\n"RESET, couts_exploitation_en_milliers);


    float consommation_electrique_par_an = (12 * consommation_electrique_mensuelle);
    printf("Consommation electrique par an : "BOLD"%.2fk kWh\n"RESET, consommation_electrique_par_an);
    float cout_consommation_electrique = consommation_electrique_par_an * 0.15;
    printf("Cout de consommation electrique par an : "BOLD"%.2fk €\n"RESET, cout_consommation_electrique);


    float benefice = chiffre_affaire_en_euros - couts_exploitation_en_milliers - cout_consommation_electrique - cout_unitaire;
    float benefice_en_millions = benefice / 1000000;
    printf("\n");
    printf(BOLD"Benefice par an : %.2fm €\n"RESET, benefice_en_millions);


    printf("\n");
    printf(BOLD"---------------------\n");
    printf("RENTABILITE\n");
    printf("----------------------\n\n"RESET);


    float nb_annees = cout_construction_total / benefice_en_millions;
    printf("Nombre d'annees pour rentabiliser l'investissement : "BOLD"%.2f\n"RESET, nb_annees);
    printf("\n");

    printf(BOLD"=============================\n");
    printf("FIN DE LA SIMULATION\n");
    printf("=============================\n\n"RESET);



}