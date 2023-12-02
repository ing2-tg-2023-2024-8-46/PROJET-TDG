#include "lecture_operations.h"
#include <stdio.h>
#include <stdlib.h>


void temps_cycle(t_station_travail** stations, int nb_stations, t_operation** operations, int nb_operations, int temps_cycle) {
    int i, j;
    float* temps_total = (float*)malloc(nb_stations * sizeof(float));

    //On réitère le processus pour chaque opération, qu'on fait checker par toutes les stations
    for (i = 0; i < nb_operations; i++) {
        for (j = 0; j < nb_stations; j++) {
          
            if (temps_total[j] + operations[i]->temps_operation < temps_cycle) {   //si le temps total des opérations sur la station + la nvlle est inf au temps de cycle
            
                stations[j]->tab_operations_struct[stations[j]->nb_operations] = operations[i]; 
                stations[j]->nb_operations++;
              
                temps_total[j] += operations[i]->temps_operation;  // on update le temps total de la station

                // Passer à la prochaine opération
                break;
            }
        }
    }

    // Afficher les opérations attribuées à chaque station
    for (j = 0; j < nb_stations; j++) {
        printf("Station %d : ", j);
        for (i = 0; i < stations[j]->nb_operations; i++) {
            printf("%d ", stations[j]->tab_operations_struct[i]->id);
        }
        printf("\n");
    }

    free(temps_total);
}
