#ifndef LISTEDECASES_H_
#define LISTEDECASES_H_

#include "case.h"
#include <stdbool.h>

#if __cplusplus
extern "C" {
#endif

typedef struct Noeud {
  Case m_case;
  struct Noeud *m_suivant;
  struct Noeud *m_precedent;
} Noeud;

typedef struct ListeDeCases {
  Noeud *m_debut;
  Noeud *m_fin;
  int m_taille;
} ListeDeCases;

// Function prototypes for ListeDeCases
ListeDeCases *ListeDeCases_create();
void ListeDeCases_destroy(ListeDeCases *liste);
int ListeDeCases_taille(const ListeDeCases *liste);
bool ListeDeCases_estVide(const ListeDeCases *liste);
void ListeDeCases_ajouterCase(ListeDeCases *liste, const Case *uneCase,
                              int position);
void ListeDeCases_ajouterCaseALaFin(ListeDeCases *liste, const Case *uneCase);
void ListeDeCases_enleverCase(ListeDeCases *liste, int position);
const Case *ListeDeCases_caseA(const ListeDeCases *liste, int position);

// Iterateur related prototypes
typedef struct Iterateur {
  const ListeDeCases *m_liste;
  Noeud *m_courant;
} Iterateur;

Iterateur *Iterateur_create(const ListeDeCases *liste);
void Iterateur_destroy(Iterateur *iter);
const Case *Iterateur_caseCourante(const Iterateur *iter);
bool Iterateur_existeCaseSuivante(const Iterateur *iter);
void Iterateur_caseSuivante(Iterateur *iter, Couleur couleur);
bool Iterateur_existeCaseSuivanteCouleur(const Iterateur *iter,
                                         Couleur couleur);
void Iterateur_casePrecedente(Iterateur *iter, Couleur couleur);
bool Iterateur_existeCasePrecedenteCouleur(const Iterateur *iter,
                                           Couleur couleur);
int Iterateur_positionCourante(const Iterateur *iter);
bool Iterateur_estADerniereCase(const Iterateur *iter);
bool Iterateur_avancer(Iterateur *iter);
FILE *ListeDeCases_print(FILE *stream, const ListeDeCases *liste);

#if __cplusplus
}
#endif

#endif /* LISTEDECASES_H_ */