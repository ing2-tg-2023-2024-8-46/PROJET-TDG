cmake_minimum_required(VERSION 3.26)
project(PROJET_TDG C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJET_TDG
        operations.h
        lecture_operations.c
        main.c
        contrainte_precedences.h
        contrainte_precedences.c
        temps_de_cycle.c
        creation_graph.h
        creation_graph.c
        contrainte_exclusions.h
        contrainte_exclusions.c
        contrainte_temps_de_cycle.h
        contrainte_temps_de_cycle.c
        operations.c
        multi_contraintes.h
        multi_contraintes.c
        stations.c
        stations.h
        couts_developpement.c
        couts_developpement.h)
