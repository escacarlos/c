#ifndef _FILEJOUEUR_H_
#define _FILEJOUEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "liste_de_cases.h"
#if __cplusplus
extern "C" {
#endif

typedef struct Joueur {
    Iterateur position;
    char nom[15];
} Joueur;

typedef struct Noeud_Joueur {
    Joueur element;
    struct Noeud_Joueur *suivant;
} Noeud_Joueur;

typedef struct ListeCirculaire_Joueur {
    Noeud_Joueur *dernier;
} ListeCirculaire_Joueur;

void Joueur_destroy(Joueur *joueur);

FILE *Joueur_print(FILE *stream, Joueur *joueur);

FILE *ListeCirculaire_Joueur_print(FILE *stream, const ListeCirculaire_Joueur *liste);

ListeCirculaire_Joueur *ListeCirculaire_Joueur_create();

void ListeCirculaire_Joueur_destroy(ListeCirculaire_Joueur *liste);

ListeCirculaire_Joueur *ListeCirculaire_Joueur_copy(ListeCirculaire_Joueur *liste, const ListeCirculaire_Joueur *source);

int ListeCirculaire_Joueur_taille(const ListeCirculaire_Joueur *liste);

bool ListeCirculaire_Joueur_appartient(const ListeCirculaire_Joueur *liste, const Joueur *x);

Joueur ListeCirculaire_Joueur_element(const ListeCirculaire_Joueur *liste, int pos);

int ListeCirculaire_Joueur_position(const ListeCirculaire_Joueur *liste, const Joueur *x);

bool ListeCirculaire_Joueur_estVide(const ListeCirculaire_Joueur *liste);

void ListeCirculaire_Joueur_ajouter(ListeCirculaire_Joueur *liste, Joueur x, int pos);

void ListeCirculaire_Joueur_ajouterFin(ListeCirculaire_Joueur *liste, Joueur x);

void ListeCirculaire_Joueur_enleverEl(ListeCirculaire_Joueur *liste, const Joueur *x);

void ListeCirculaire_Joueur_enleverPos(ListeCirculaire_Joueur *liste, int pos);

FILE *ListeCirculaire_Joueur_print(FILE *stream, const ListeCirculaire_Joueur *liste);

typedef struct File_Joueur {
    ListeCirculaire_Joueur *liste;
} File_Joueur;

File_Joueur *File_Joueur_create();

void File_Joueur_destroy(File_Joueur *file);

void File_Joueur_enfiler(File_Joueur *file, Joueur x);

Joueur File_Joueur_defiler(File_Joueur *file);

int File_Joueur_taille(const File_Joueur *file);

FILE *File_Joueur_print(FILE *stream, const File_Joueur *file);

#if __cplusplus
}
#endif

#endif /*_FILEJOUEUR_H_*/