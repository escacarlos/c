#ifndef _JEUSERPENTECHELLES_H_
#define _JEUSERPENTECHELLES_H_

#include <stdio.h>

#include "liste_circulaire_couleur.h"
#include "file_joueur.h"

#if __cplusplus
extern "C" {
#endif

struct Resultat {
    unsigned int nombreDeTours;
    char *nom;
};

typedef struct JeuSerpentsEtEchelles {
    ListeDeCases *m_cases;
    ListeCirculaire_Couleur *m_choix;
    File_Joueur *m_joueurs;
} JeuSerpentsEtEchelles;

// Joueur *Joueur_create(Iterateur *p_pos, const char *p_nom);

// void Joueur_destroy(Joueur *unJoueur);

struct Resultat *Resultat_create(unsigned int p_nombreDeTours, const char *p_nom);

void Resultat_destroy(struct Resultat *res);

FILE *Joueur_print(FILE *stream, Joueur *joueur);

JeuSerpentsEtEchelles *JeuSerpentsEtEchelles_create();

void JeuSerpentsEtEchelles_destroy(JeuSerpentsEtEchelles *jeuSE);

void JeuSerpentsEtEchelles_afficherResultats(JeuSerpentsEtEchelles *jeuSE, struct Resultat gagnant);

void JeuSerpentsEtEchelles_effacer(JeuSerpentsEtEchelles *jeuSE);

void JeuSerpentsEtEchelles_ajouterCase(JeuSerpentsEtEchelles *jeuSE, Case *p_case);

void JeuSerpentsEtEchelles_ajouterChoix(JeuSerpentsEtEchelles *jeuSE, Couleur couleur);

void JeuSerpentsEtEchelles_ajouterJoueur(JeuSerpentsEtEchelles *jeuSE, Joueur joueur);

Iterateur *JeuSerpentsEtEchelles_premiereCase(JeuSerpentsEtEchelles *jeuSE);

struct Resultat *JeuSerpentsEtEchelles_jouer(JeuSerpentsEtEchelles *jeuSE, unsigned int maximumDeTours);

#if __cplusplus
}
#endif

#endif /*_JEUSERPENTECHELLES_H_*/