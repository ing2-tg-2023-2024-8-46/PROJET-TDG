//
// Created by lasbowowowowow on 01/11/2023.
//  ......


#include "lecture_operations.h"
#include "contrainte_precedences.h"
#include "contrainte_exclusions.h"
#include "contrainte_temps_de_cycle.h"
#include "multi_contraintes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define GOLD "\033[1;33m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RESET_BOLD "\033[21m"
#define RESET_COLOR "\033[39m"


int main() {

    printf("Informations générales : \n");

    t_infos* infos = (t_infos*) malloc(sizeof(t_infos));
    t_operation** tab_operations;
    tab_operations = lecture_operations(infos);


    contrainte_precedences(infos, tab_operations);
    contrainte_exclusions(infos, tab_operations);
    contrainte_temps_de_cycle(infos, tab_operations);
    multi_contraintes(infos, tab_operations);



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