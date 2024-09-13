#ifndef _LISTECIRCULAIRECOULEUR_H_
#define _LISTECIRCULAIRECOULEUR_H_

#include "liste_de_cases.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if __cplusplus
extern "C" {
#endif

typedef struct Noeud_Couleur {
    Couleur element;
    struct Noeud_Couleur *suivant;
} Noeud_Couleur;

typedef struct ListeCirculaire_Couleur {
    Noeud_Couleur *dernier;
} ListeCirculaire_Couleur;

FILE *ListeCirculaire_Couleur_print(FILE *stream, const ListeCirculaire_Couleur *liste);

ListeCirculaire_Couleur *ListeCirculaire_Couleur_create();

void ListeCirculaire_Couleur_destroy(ListeCirculaire_Couleur *liste);

ListeCirculaire_Couleur *ListeCirculaire_Couleur_copy(ListeCirculaire_Couleur *liste, const ListeCirculaire_Couleur *source);

int ListeCirculaire_Couleur_taille(const ListeCirculaire_Couleur *liste);

bool ListeCirculaire_Couleur_appartient(const ListeCirculaire_Couleur *liste, const Couleur *x);

Couleur ListeCirculaire_Couleur_element(const ListeCirculaire_Couleur *liste, int pos);

int ListeCirculaire_Couleur_position(const ListeCirculaire_Couleur *liste, const Couleur *x);

bool ListeCirculaire_Couleur_estVide(const ListeCirculaire_Couleur *liste);

void ListeCirculaire_Couleur_ajouter(ListeCirculaire_Couleur *liste, const Couleur *x, int pos);

void ListeCirculaire_Couleur_ajouterFin(ListeCirculaire_Couleur *liste, const Couleur *x);

void ListeCirculaire_Couleur_enleverEl(ListeCirculaire_Couleur *liste, const Couleur *x);

void ListeCirculaire_Couleur_enleverPos(ListeCirculaire_Couleur *liste, int pos);

FILE *ListeCirculaire_Couleur_print(FILE *stream, const ListeCirculaire_Couleur *liste);

#if __cplusplus
}
#endif

#endif /*_LISTECIRCULAIRECOULEUR_H_*/