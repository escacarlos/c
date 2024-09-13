#include <stdio.h>
#include <stdlib.h>

#include "jeu_serpent_echelles.h"

int main() {
    // Create the game
    JeuSerpentsEtEchelles *jeu = JeuSerpentsEtEchelles_create();

    // Add cases to the game board
    Case case1 = {ROUGE, AUCUNE};
    Case case2 = {VERT, SERPENT};
    Case case3 = {BLEU, ECHELLE};
    Case case4 = {JAUNE, AUCUNE};
    JeuSerpentsEtEchelles_ajouterCase(jeu, &case1);
    JeuSerpentsEtEchelles_ajouterCase(jeu, &case2);
    JeuSerpentsEtEchelles_ajouterCase(jeu, &case3);
    JeuSerpentsEtEchelles_ajouterCase(jeu, &case4);

    // Add choices to the circular color list
    JeuSerpentsEtEchelles_ajouterChoix(jeu, ROUGE);
    JeuSerpentsEtEchelles_ajouterChoix(jeu, VERT);
    JeuSerpentsEtEchelles_ajouterChoix(jeu, BLEU);
    JeuSerpentsEtEchelles_ajouterChoix(jeu, JAUNE);

    // Create iterators pointing to the first case
    Iterateur it1 = JeuSerpentsEtEchelles_premiereCase(jeu);
    Iterateur it2 = JeuSerpentsEtEchelles_premiereCase(jeu);
    Iterateur it3 = JeuSerpentsEtEchelles_premiereCase(jeu);

    // Create players
    Joueur joueur1;
    Joueur_create(&joueur1, &it1, "Carlos");
    
    Joueur joueur2;
    Joueur_create(&joueur2, &it2, "Alissa");
    
    Joueur joueur3;
    Joueur_create(&joueur3, &it3, "Gael");

    // Add players to the game
    JeuSerpentsEtEchelles_ajouterJoueur(jeu, joueur1);
    JeuSerpentsEtEchelles_ajouterJoueur(jeu, joueur2);
    JeuSerpentsEtEchelles_ajouterJoueur(jeu, joueur3);
    printf("*******GOT HERE*******\n\n");
    
    // Play the game
    unsigned int maximumDeTours = 100;
    struct Resultat resultat = JeuSerpentsEtEchelles_jouer(jeu, maximumDeTours);

    // Display results
    JeuSerpentsEtEchelles_afficherResultats(jeu, resultat);

    // Clean up memory
    JeuSerpentsEtEchelles_effacer(jeu);
    free(jeu);

    return 0;
}
