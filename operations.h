//
// Created by lasbo on 20/11/2023.
//

#ifndef PROJET_TDG_OPERATIONS_H
#define PROJET_TDG_OPERATIONS_H

typedef struct {

    int max_operations;
    int temps_cycle;

}t_infos;

typedef struct {

    int id;
    int is_valid;

    int *exclusions;
    int nb_exclusions;

    int *precedences;
    int nb_precedences;

    float temps_operation;

}t_operation;

#endif //PROJET_TDG_OPERATIONS_H
