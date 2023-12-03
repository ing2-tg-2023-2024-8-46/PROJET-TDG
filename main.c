//
// Created by lasbowowowowow on 01/11/2023.
//  ......


#include "lecture_operations.h"
#include "contrainte_precedences.h"
#include "contrainte_exclusions.h"
#include "contrainte_temps_de_cycle.h"
#include "multi_contraintes.h"
#include "couts_developpement.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>



#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define GOLD "\033[1;33m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RESET_BOLD "\033[21m"
#define RESET_COLOR "\033[39m"
#define ITALIC "\033[3m"
#define LIGHT_GREEN "\033[92m"





int main() {

    int choix = -1;
    srand(time(NULL));

    t_infos* infos = (t_infos*) malloc(sizeof(t_infos));
    t_operation** tab_operations;
    tab_operations = lecture_operations(infos);


    printf("\n"
           BLUE"███████╗░█████╗░███████╗""          ""██╗░░░░░███████╗░█████╗░░█████╗░██████╗░\n"RESET
           BLUE"██╔════╝██╔══██╗██╔════╝""          ""██║░░░░░██╔════╝██╔══██╗██╔══██╗██╔══██╗\n"RESET
           BLUE"█████╗░░██║░░╚═╝█████╗░░""  █████╗  ""██║░░░░░█████╗░░██║░░╚═╝███████║██████╔╝\n"RESET
           BLUE"██╔══╝░░██║░░██╗██╔══╝░░""  ╚════╝  ""██║░░░░░██╔══╝░░██║░░██╗██╔══██║██╔══██╗\n"RESET
           BLUE"███████╗╚█████╔╝███████╗""          ""███████╗███████╗╚█████╔╝██║░░██║██║░░██║\n"RESET
           BLUE"╚══════╝░╚════╝░╚══════╝""          ""╚══════╝╚══════╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝\n"RESET);

    printf(ITALIC"Votre Logiciel de Gestion de Production\n"RESET);
    printf("\n");

    printf("CHARGEMENT : ");
    //ECRIT ALEATOIRE ENTRE 0.1 ET 0.5S POUR SIMULER UN TEMPS DE CHARGEMENT
    for (int i = 0; i < 50; ++i) {
        printf(LIGHT_GREEN"█"RESET);
        fflush(stdout);
        usleep((rand() % 20000) + 20000);
    }
    printf("\n"BOLD GREEN "CHARGEMENT TERMINE\n"RESET);


    printf("\n\n");
    printf("USERNAME : ");
    char user[50] = "ECE-Linux1233";
    //ECRIT ALEATOIRE ENTRE 0.01 ET 0.3S POUR SIMULER UN TEMPS DE CHARGEMENT
    for (int i = 0; i < strlen(user); ++i) {
        printf("%c",user[i]);
        fflush(stdout);
        usleep((rand() % 30000) + 10000);
    }
    printf("\n");
    printf("PASSWORD : ");
    //ECRIT ALEATOIRE ENTRE 0.1 ET 0.3S POUR SIMULER UN TEMPS DE CHARGEMENT
    for (int i = 0; i < 10; ++i) {
        printf("*");
        fflush(stdout);
        usleep((rand() % 30000) + 100000);
    }
    printf("\n"BOLD GREEN "AUTHENTIFICATION REUSSIE\n"RESET);
    printf("Bienvenue "BOLD"%s\n"RESET,user);
    printf("\n\n");
    printf("Bienvenue et merci d'utiliser notre logiciel de gestion de production\n");
    printf("\n\n");

    while (choix != 0) {

        do {

            //SI C'EST LE PREMIER TOUR DE BOUCLE, NE PAS EFFACER L'ECRAN
            if (choix != -1) {
                for (int i = 0; i < 20; ++i) {
                    printf("\n\n");
                }
            }

            printf(BOLD"\n"
                   "███╗░░░███╗███████╗███╗░░██╗██╗░░░██╗  ██████╗░██████╗░██╗███╗░░██╗░█████╗░██╗██████╗░░█████╗░██╗░░░░░\n"
                   "████╗░████║██╔════╝████╗░██║██║░░░██║  ██╔══██╗██╔══██╗██║████╗░██║██╔══██╗██║██╔══██╗██╔══██╗██║░░░░░\n"
                   "██╔████╔██║█████╗░░██╔██╗██║██║░░░██║  ██████╔╝██████╔╝██║██╔██╗██║██║░░╚═╝██║██████╔╝███████║██║░░░░░\n"
                   "██║╚██╔╝██║██╔══╝░░██║╚████║██║░░░██║  ██╔═══╝░██╔══██╗██║██║╚████║██║░░██╗██║██╔═══╝░██╔══██║██║░░░░░\n"
                   "██║░╚═╝░██║███████╗██║░╚███║╚██████╔╝  ██║░░░░░██║░░██║██║██║░╚███║╚█████╔╝██║██║░░░░░██║░░██║███████╗\n"
                   "╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░╚═════╝░  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚════╝░╚═╝╚═╝░░░░░╚═╝░░╚═╝╚══════╝"RESET"\n");

            printf("Veuillez choisir une option :\n");
            printf(BOLD"\t 1 - Afficher les informations des operations\n");
            printf("\t 2 - Afficher les informations de la chaine de montage\n");
            printf("\t 3 - Afficher les contraintes de precedences\n");
            printf("\t 4 - Afficher les contraintes d'exclusions\n");
            printf("\t 5 - Afficher les contraintes de temps de cycle\n");
            printf("\t 6 - Afficher les contraintes multiples\n");
            printf("\t 7 - NOUVEAU ! Simulation de couts de developpement\n");
            printf("\t 8 - Quitter\n"RESET);

            printf("C:\\"BOLD"Projet_TDG\\input : "RESET);

            scanf("%d", &choix);

            // TANT QUE LE CHOIX EST EN DEHORS DE L'INTERVALLE 0 - 4
        } while (choix < 1 || choix > 8);

        switch (choix) {

            case 8:
                printf("Merci d'avoir utilise notre logiciel de gestion de production\n");
                printf("A bientot\n");
                exit(0);
                break;

            case 1:
                printf("\n");
                printf("\n");
                printf("INFOS DES OPERATIONS\n");
                for (int i = 0; i < infos->max_operations + 1; ++i) {
                    if (tab_operations[i]->is_valid == 0) continue;
                    printf(BOLD"Operation "GOLD"%d\n"RESET, tab_operations[i]->id);
                    printf("\t - Temps : %.2f\n", tab_operations[i]->temps_operation);
                    printf("\t - Exclusions : ");
                    for (int j = 0; j < tab_operations[i]->nb_exclusions; ++j) {
                        printf("%d ", tab_operations[i]->exclusions[j]);
                    }
                    printf("\n");
                    printf("\t - Precedences : ");
                    for (int j = 0; j < tab_operations[i]->nb_precedences; ++j) {
                        printf("%d ", tab_operations[i]->precedences[j]);
                    }
                    printf("\n");

                }
                break;

            case 2:
                printf("\n");
                printf("INFOS DE LA CHAINE DE MONTAGE\n");
                printf("\t - Nombre d'operations : %d\n", infos->max_operations);
                printf("\t - Temps de cycle : %.1f\n", infos->temps_cycle_max);
                break;

            case 3:
                contrainte_precedences(infos, tab_operations);
                break;

            case 4:
                contrainte_exclusions(infos, tab_operations);
                break;

            case 5:
                contrainte_temps_de_cycle(infos, tab_operations);
                break;

            case 6:
                contrainte_precedences(infos, tab_operations);
                contrainte_exclusions(infos, tab_operations);
                multi_contraintes(infos, tab_operations);
                fflush(stdin);
                break;

            case 7:
                contrainte_precedences(infos, tab_operations);
                contrainte_exclusions(infos, tab_operations);
                simulation_couts_de_developpements(infos, tab_operations);
                break;

            default:
                printf("Erreur\n");
                break;



        }

        fflush(stdin);
        getchar();

    }





    /*
    printf("\n");
    printf("\n");
    printf("INFOS DES OPERATIONS\n");
    for (int i = 0; i < infos->max_operations+1; ++i) {
        if (tab_operations[i]->is_valid == 0) continue;
        printf(BOLD"Operation "GOLD"%d\n"RESET ,tab_operations[i]->id);
        printf("\t - Temps : %.2f\n",tab_operations[i]->temps_operation);
        printf("\t - Exclusions : ");
        for (int j = 0; j < tab_operations[i]->nb_exclusions; ++j) {
            printf("%d ",tab_operations[i]->exclusions[j]);
        }
        printf("\n");
        printf("\t - Precedences : ");
        for (int j = 0; j < tab_operations[i]->nb_precedences; ++j) {
            printf("%d ",tab_operations[i]->precedences[j]);
        }
        printf("\n");

    }

    printf("\n");
    printf("INFOS DE LA CHAINE DE MONTAGE\n");
    printf("\t - Nombre d'operations : %d\n",infos->max_operations);
    printf("\t - Temps de cycle : %.1f\n",infos->temps_cycle_max);
*/





    return 0;



}