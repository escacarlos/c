#include "generateur_JeuSE_aleatoire.h"

int main() {
    printf("Jeu 1:\n");
    JeuSerpentsEtEchelles *jeu = JeuSerpentsEtEchelles_create();
    GenerateurAleatoireJeuSerpentEchelle *generateurJeu = GenerateurAleatoireJeuSerpentEchelle_create(1);
    GenerateurAleatoireJeuSerpentEchelle_generer(generateurJeu, jeu, 5, 9, 2);
    struct Resultat *res = JeuSerpentsEtEchelles_jouer(jeu, 100);
    JeuSerpentsEtEchelles_afficherResultats(jeu, *res);
    Resultat_destroy(res);

    printf("\nJeu 2:\n");
    GenerateurAleatoireJeuSerpentEchelle_generer(generateurJeu, jeu, 5, 9, 2);
    struct Resultat *res2 = JeuSerpentsEtEchelles_jouer(jeu, 100);
    JeuSerpentsEtEchelles_afficherResultats(jeu, *res2);
    Resultat_destroy(res2);
    GenerateurAleatoireJeuSerpentEchelle_destroy(generateurJeu);

    printf("\nJeu 3:\n");
    GenerateurAleatoireJeuSerpentEchelle *generateurJeu2 = GenerateurAleatoireJeuSerpentEchelle_create(9569686);
    GenerateurAleatoireJeuSerpentEchelle_generer(generateurJeu2, jeu, 243, 53, 4);
    struct Resultat *res3 = JeuSerpentsEtEchelles_jouer(jeu, 20000);
    JeuSerpentsEtEchelles_afficherResultats(jeu, *res3);
    Resultat_destroy(res3);

    printf("\nJeu 4:\n");
    GenerateurAleatoireJeuSerpentEchelle_generer(generateurJeu2, jeu, 243, 53, 4);
    struct Resultat *res4 = JeuSerpentsEtEchelles_jouer(jeu, 20000);
    JeuSerpentsEtEchelles_afficherResultats(jeu, *res4);
    Resultat_destroy(res4);
    GenerateurAleatoireJeuSerpentEchelle_destroy(generateurJeu2);
    
    JeuSerpentsEtEchelles_destroy(jeu);

    return 0;
}