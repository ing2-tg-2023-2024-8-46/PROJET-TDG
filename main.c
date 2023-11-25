//
// Created by lasbowowowowow on 01/11/2023.
//


#include "lecture_operations.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("Hello, World!\n");

    t_infos* infos = (t_infos*) malloc(sizeof(t_infos));
    t_operation** tab_operations;

    tab_operations = lecture_operations(infos);

    for (int i = 0; i < infos->max_operations+1; ++i) {
        if (tab_operations[i]->is_valid == 0) continue;
        printf("Operation : %d\n",tab_operations[i]->id);
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

    printf("INFOS DE LA CHAINE DE MONTAGE\n");
    printf("\t - Nombre d'operations : %d\n",infos->max_operations);
    printf("\t - Temps de cycle : %d\n",infos->temps_cycle);

    return 0;



}