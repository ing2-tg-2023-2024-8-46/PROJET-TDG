//
// Created by lasbo on 20/11/2023.
//

#include "lecture_operations.h"
#include <stdio.h>
#include <stdlib.h>


t_operation** lecture_operations(t_infos* infos) {

    t_operation** tab_operations;
    int max_operations = 0;
    int operation;
    int temps_cycle;
    float time;


    //████████╗███████╗███╗░░░███╗██████╗░░██████╗        ░█████╗░██████╗░███████╗██████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗
    //╚══██╔══╝██╔════╝████╗░████║██╔══██╗██╔════╝        ██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
    //░░░██║░░░█████╗░░██╔████╔██║██████╔╝╚█████╗░        ██║░░██║██████╔╝█████╗░░██████╔╝███████║░░░██║░░░██║██║░░██║██╔██╗██║
    //░░░██║░░░██╔══╝░░██║╚██╔╝██║██╔═══╝░░╚═══██╗        ██║░░██║██╔═══╝░██╔══╝░░██╔══██╗██╔══██║░░░██║░░░██║██║░░██║██║╚████║
    //░░░██║░░░███████╗██║░╚═╝░██║██║░░░░░██████╔╝        ╚█████╔╝██║░░░░░███████╗██║░░██║██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║
    //░░░╚═╝░░░╚══════╝╚═╝░░░░░╚═╝╚═╝░░░░░╚═════╝░        ░╚════╝░╚═╝░░░░░╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝

    FILE* file = fopen("../congif_text_files/operations.txt", "r");
    if (file == NULL) {
        printf("[lecture_operations.c] Erreur lors de l'ouverture du fichier operations.txt\n");
        exit(1);
    }


    while (fscanf(file, "%d %f", &operation, &time) == 2) {
        //check plus grand id
        if (operation > max_operations) {
            max_operations = operation;
        }
    }

    fclose(file);
    file = fopen("../congif_text_files/operations.txt", "r");
    if (file == NULL) {
        printf("[lecture_operations.c] Erreur lors de l'ouverture du fichier operations.txt\n");
        exit(1);
    }

    // creation du tableau de structures
    tab_operations = (t_operation **) malloc(sizeof(t_operation *) * max_operations);
    for (int i = 0; i < max_operations + 1; ++i) {
        tab_operations[i] = (t_operation *) malloc(sizeof(t_operation));
        tab_operations[i]->nb_exclusions = 0;
        tab_operations[i]->nb_precedences = 0;
        tab_operations[i]->is_valid = 0;

    }

    while (fscanf(file, "%d %f", &operation, &time) == 2) {
        tab_operations[operation]->id = operation;
        tab_operations[operation]->temps_operation = time;
        tab_operations[operation]->is_valid = 1;
    }

    fclose(file);


    //██████╗░██████╗░███████╗░█████╗░███████╗██████╗░███████╗███╗░░██╗░█████╗░███████╗░██████╗
    //██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝██╔══██╗██╔════╝████╗░██║██╔══██╗██╔════╝██╔════╝
    //██████╔╝██████╔╝█████╗░░██║░░╚═╝█████╗░░██║░░██║█████╗░░██╔██╗██║██║░░╚═╝█████╗░░╚█████╗░
    //██╔═══╝░██╔══██╗██╔══╝░░██║░░██╗██╔══╝░░██║░░██║██╔══╝░░██║╚████║██║░░██╗██╔══╝░░░╚═══██╗
    //██║░░░░░██║░░██║███████╗╚█████╔╝███████╗██████╔╝███████╗██║░╚███║╚█████╔╝███████╗██████╔╝
    //╚═╝░░░░░╚═╝░░╚═╝╚══════╝░╚════╝░╚══════╝╚═════╝░╚══════╝╚═╝░░╚══╝░╚════╝░╚══════╝╚═════╝░

    file = fopen("../congif_text_files/precedences.txt", "r");
    if (file == NULL) {
        printf("[lecture_operations.c] Erreur lors de l'ouverture du fichier precedences.txt\n");
        exit(1);
    }

    int precedence1, precedence2;

    while (fscanf(file, "%d %d", &precedence1, &precedence2) == 2) {
        if (tab_operations[precedence1]->nb_precedences == 0) {
            tab_operations[precedence1]->precedences = (int *) malloc(sizeof(int));
        } else {

            tab_operations[precedence1]->precedences = (int *) realloc(
                    tab_operations[precedence1]->precedences,
                    sizeof(int) * (tab_operations[precedence1]->nb_precedences + 1)
            );
        }

        tab_operations[precedence1]->precedences[tab_operations[precedence1]->nb_precedences] = precedence2;
        tab_operations[precedence1]->nb_precedences++;


    }

    fclose(file);



    //███████╗██╗░░██╗░█████╗░██╗░░░░░██╗░░░██╗░██████╗██╗░█████╗░███╗░░██╗░██████╗
    //██╔════╝╚██╗██╔╝██╔══██╗██║░░░░░██║░░░██║██╔════╝██║██╔══██╗████╗░██║██╔════╝
    //█████╗░░░╚███╔╝░██║░░╚═╝██║░░░░░██║░░░██║╚█████╗░██║██║░░██║██╔██╗██║╚█████╗░
    //██╔══╝░░░██╔██╗░██║░░██╗██║░░░░░██║░░░██║░╚═══██╗██║██║░░██║██║╚████║░╚═══██╗
    //███████╗██╔╝╚██╗╚█████╔╝███████╗╚██████╔╝██████╔╝██║╚█████╔╝██║░╚███║██████╔╝
    //╚══════╝╚═╝░░╚═╝░╚════╝░╚══════╝░╚═════╝░╚═════╝░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░

    file = fopen("../congif_text_files/exclusions.txt", "r");
    if (file == NULL) {
        printf("[lecture_operations.c] Erreur lors de l'ouverture du fichier exclusions.txt\n");
        exit(1);
    }

    int exclusion1, exclusion2;

    while (fscanf(file, "%d %d", &exclusion1, &exclusion2) == 2) {
        // Exclusions pour la première opération
        if (tab_operations[exclusion1]->nb_exclusions == 0) {
            tab_operations[exclusion1]->exclusions = (int *) malloc(sizeof(int));
        } else {
            tab_operations[exclusion1]->exclusions = (int *) realloc(
                    tab_operations[exclusion1]->exclusions,
                    sizeof(int) * (tab_operations[exclusion1]->nb_exclusions + 1)
            );
        }
        tab_operations[exclusion1]->exclusions[tab_operations[exclusion1]->nb_exclusions] = exclusion2;
        tab_operations[exclusion1]->nb_exclusions++;

        // Exclusions pour la deuxième opération
        if (tab_operations[exclusion2]->nb_exclusions == 0) {
            tab_operations[exclusion2]->exclusions = (int *) malloc(sizeof(int));
        } else {
            tab_operations[exclusion2]->exclusions = (int *) realloc(
                    tab_operations[exclusion2]->exclusions,
                    sizeof(int) * (tab_operations[exclusion2]->nb_exclusions + 1)
            );
        }
        tab_operations[exclusion2]->exclusions[tab_operations[exclusion2]->nb_exclusions] = exclusion1;
        tab_operations[exclusion2]->nb_exclusions++;
    }

    fclose(file);



    //████████╗███████╗███╗░░░███╗██████╗░░██████╗        ░█████╗░██╗░░░██╗░█████╗░██╗░░░░░███████╗
    //╚══██╔══╝██╔════╝████╗░████║██╔══██╗██╔════╝        ██╔══██╗╚██╗░██╔╝██╔══██╗██║░░░░░██╔════╝
    //░░░██║░░░█████╗░░██╔████╔██║██████╔╝╚█████╗░        ██║░░╚═╝░╚████╔╝░██║░░╚═╝██║░░░░░█████╗░░
    //░░░██║░░░██╔══╝░░██║╚██╔╝██║██╔═══╝░░╚═══██╗        ██║░░██╗░░╚██╔╝░░██║░░██╗██║░░░░░██╔══╝░░
    //░░░██║░░░███████╗██║░╚═╝░██║██║░░░░░██████╔╝        ╚█████╔╝░░░██║░░░╚█████╔╝███████╗███████╗
    //░░░╚═╝░░░╚══════╝╚═╝░░░░░╚═╝╚═╝░░░░░╚═════╝░        ░╚════╝░░░░╚═╝░░░░╚════╝░╚══════╝╚══════╝

    file = fopen("../congif_text_files/temps_cycle.txt", "r");
    if (file == NULL) {
        printf("[lecture_operations.c] Erreur lors de l'ouverture du fichier temps_cycle.txt\n");
        exit(1);
    }
    fscanf(file, "%d", &infos->temps_cycle);
    fclose(file);



    infos->max_operations = max_operations;
    return tab_operations;


}