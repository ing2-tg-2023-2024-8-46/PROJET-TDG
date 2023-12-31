//
// Created by lasbo on 20/11/2023.
//

#ifndef PROJET_TDG_OPERATIONS_H
#define PROJET_TDG_OPERATIONS_H

#include <stdio.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define GOLD "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RESET_BOLD "\033[21m"
#define RESET_COLOR "\033[39m"


typedef struct {

    int max_operations;
    float temps_cycle_max;

}t_infos;

typedef struct {

    int id;
    int is_valid;

    int *exclusions;
    int nb_exclusions;

    int *precedences;
    int nb_precedences;

    float temps_operation;
    int coloration;

}t_operation;




#endif //PROJET_TDG_OPERATIONS_H
