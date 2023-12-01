cmake_minimum_required(VERSION 3.26)
project(PROJET_TDG C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJET_TDG
        operations.h
        lecture_operations.c
        main.c
        contrainte_precedences.h
        contrainte_precedences.c)
