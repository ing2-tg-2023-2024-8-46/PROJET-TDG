//
// Created by lasbo on 02/12/2023.
//

#include "creation_graph.h"
#include <stdio.h>
#include <stdlib.h>


void afficherGraphe(Graphe* g) {


    printf("Affichage du graphe\n");
    printf("- Taille : %d\n", g->taille);
    printf("- Ordre : %d\n", g->ordre);
    printf("- Orientation : %d\n", g->orientation);
    printf("- Sommets : \n");
    for (int i = 0; i < g->ordre; ++i) {
        if (g->tabSommet[i]->is_valid == 0) continue;
        printf("\n Sommet %d ", g->tabSommet[i]->valeur);
        printf("\n\t - Degre %d ", g->tabSommet[i]->degre);
        printf("\n\t - Etape traitement %d ", g->tabSommet[i]->etape_traitement);
        printf("\n\t - Arcs : ");
        Arrete* arc = g->tabSommet[i]->arrete;
        while (arc != NULL) {
            printf("\n\t -> %d ", arc->sommet);
            arc = arc->arrete_suivante;
        }
        printf("\n");
        printf("\n");
    }

}

void afficherGrapheColoration(Graphe* g) {


    printf("Affichage du graphe\n");
    printf("- Taille : %d\n", g->taille);
    printf("- Ordre : %d\n", g->ordre);
    printf("- Orientation : %d\n", g->orientation);
    printf("- Sommets : \n");
    for (int i = 0; i < g->ordre; ++i) {
        if (g->tabSommet[i]->is_valid == 0) continue;
        printf("\n Sommet %d ", g->tabSommet[i]->valeur);
        if (g->tabSommet[i]->couleur == R) printf(RED" [R] "RESET);
        if (g->tabSommet[i]->couleur == G) printf(GREEN" [G] "RESET);
        if (g->tabSommet[i]->couleur == B) printf(BLUE" [B] "RESET);
        if (g->tabSommet[i]->couleur == Y) printf(GOLD" [Y] "RESET);
        if (g->tabSommet[i]->couleur == C) printf(CYAN" [C] "RESET);
        if (g->tabSommet[i]->couleur == M) printf(MAGENTA" [M] "RESET);
        printf("\n\t - Degre %d ", g->tabSommet[i]->degre);
        printf("\n\t - Etape traitement %d ", g->tabSommet[i]->etape_traitement);
        printf("\n\t - Arcs : ");
        Arrete* arc = g->tabSommet[i]->arrete;
        while (arc != NULL) {
            if (g->tabSommet[arc->sommet]->couleur == R) printf(RED"\n\t -> %d "RESET, arc->sommet);
            if (g->tabSommet[arc->sommet]->couleur == G) printf(GREEN"\n\t -> %d "RESET, arc->sommet);
            if (g->tabSommet[arc->sommet]->couleur == B) printf(BLUE"\n\t -> %d "RESET, arc->sommet);
            if (g->tabSommet[arc->sommet]->couleur == Y) printf(GOLD"\n\t -> %d "RESET, arc->sommet);
            if (g->tabSommet[arc->sommet]->couleur == C) printf(CYAN"\n\t -> %d "RESET, arc->sommet);
            if (g->tabSommet[arc->sommet]->couleur == M) printf(MAGENTA"\n\t -> %d "RESET, arc->sommet);
            arc = arc->arrete_suivante;
        }
        printf("\n");
        printf("\n");
    }

}


void CreerArete(Sommet** sommet, int s1, int s2, int poids) {

    if(sommet[s1]->arrete == NULL)
    {
        Arrete* Newarc=(Arrete*)malloc(sizeof(struct Arrete));
        Newarc->sommet=s2;
        Newarc->poids=poids;
        Newarc->arrete_suivante=NULL;
        sommet[s1]->arrete=Newarc;
    }

    else {
        Arrete *temp = sommet[s1]->arrete;
        while (temp->arrete_suivante != NULL) {
            temp = temp->arrete_suivante;
        }
        Arrete *arc = (Arrete *) malloc(sizeof(struct Arrete));
        arc->sommet = s2;
        arc->poids = poids;
        arc->arrete_suivante = NULL;

        if (temp->sommet > s2) {
            arc->arrete_suivante = temp->arrete_suivante;
            arc->sommet = temp->sommet;
            temp->sommet = s2;
            temp->arrete_suivante = arc;
        }

        temp->arrete_suivante = arc;


    }
}
