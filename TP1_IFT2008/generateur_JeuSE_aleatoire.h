#ifndef _RANDGENJEUSERPECHEL_H_
#define _RANDGENJEUSERPECHEL_H_

#include "generateur_nombres_aleatoires.h"
#include "jeu_serpent_echelles.h"

#include <string.h>

#if __cplusplus
extern "C" {
#endif

typedef struct GenerateurAleatoireJeuSerpentEchelle {
    unsigned int m_compteurNomJoueurs;
    GenerateurNombresAleatoires *m_generateurNombresAleatoires;
} GenerateurAleatoireJeuSerpentEchelle;

Couleur GenerateurAleatoireJeuSerpentEchelle_choisirUneCouleurAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE);

Decoration GenerateurAleatoireJeuSerpentEchelle_choisirUneDecorationAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE);

void GenerateurAleatoireJeuSerpentEchelle_genererCases(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, JeuSerpentsEtEchelles *jeuSE, unsigned int nombreCases);

void GenerateurAleatoireJeuSerpentEchelle_choisirUnNomAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, char *nomBuffer, size_t bufferSize);

void GenerateurAleatoireJeuSerpentEchelle_genererChoix(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, JeuSerpentsEtEchelles *jeuSE, unsigned int nombreDeChoix);

Joueur GenerateurAleatoireJeuSerpentEchelle_genererUnJoueurAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, Iterateur *it);

void GenerateurAleatoireJeuSerpentEchelle_genererJoueurs(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, JeuSerpentsEtEchelles *jeuSE, unsigned int nombreDeJoueurs);

GenerateurAleatoireJeuSerpentEchelle *GenerateurAleatoireJeuSerpentEchelle_create(unsigned int initNombreAleatoire);

void GenerateurAleatoireJeuSerpentEchelle_generer(GenerateurAleatoireJeuSerpentEchelle *randJeuSE,
                                                  JeuSerpentsEtEchelles *jeuSE,
                                                  unsigned int nombreCases, unsigned int nombreDeChoix,
                                                  unsigned int nombreDeJoueurs);

void GenerateurAleatoireJeuSerpentEchelle_destroy(GenerateurAleatoireJeuSerpentEchelle *randJeuSE);

#if __cplusplus
}
#endif

#endif /*_RANDGENJEUSERPECHEL_H_*/
