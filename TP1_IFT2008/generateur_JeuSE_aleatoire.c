#include "generateur_JeuSE_aleatoire.h"

Couleur GenerateurAleatoireJeuSerpentEchelle_choisirUneCouleurAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE) {

    return (Couleur) GenerateurNombresAleatoires_pige(randJeuSE->m_generateurNombresAleatoires) % NOMBRE_COULEURS;
}

Decoration GenerateurAleatoireJeuSerpentEchelle_choisirUneDecorationAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE) {

    return (Decoration) GenerateurNombresAleatoires_pige(randJeuSE->m_generateurNombresAleatoires) % NOMBRE_DECORATIONS;
}

// MEMORY ALLOCATED
void GenerateurAleatoireJeuSerpentEchelle_genererCases(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, JeuSerpentsEtEchelles *jeuSE, unsigned int nombreCases) {
    for (unsigned int compteurCases = 0; compteurCases < nombreCases; compteurCases++) {
        Case *nouvelleCase = (Case *)malloc(sizeof(Case));
        nouvelleCase->couleur = ROUGE;
        nouvelleCase->decoration = AUCUNE;
        case_init(nouvelleCase, GenerateurAleatoireJeuSerpentEchelle_choisirUneCouleurAleatoirement(randJeuSE),
                  GenerateurAleatoireJeuSerpentEchelle_choisirUneDecorationAleatoirement(randJeuSE));
        JeuSerpentsEtEchelles_ajouterCase(jeuSE, nouvelleCase);
        free(nouvelleCase);
    }
}

void GenerateurAleatoireJeuSerpentEchelle_choisirUnNomAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, char *nomBuffer, size_t bufferSize) {
    randJeuSE->m_compteurNomJoueurs++;

    // char *nom = (char *) malloc(20); // Assuming 20 is enough
    // if (nom == NULL) {
    //     perror("Failed to allocate memory for player name");
    //     exit(EXIT_FAILURE);
    // }
    if (bufferSize < 15) {  // Ensure the buffer can hold "Joueur X" + null terminator
        fprintf(stderr, "Buffer size is too small\n");
        exit(EXIT_FAILURE);
    }

    snprintf(nomBuffer, bufferSize, "Joueur %u", randJeuSE->m_compteurNomJoueurs);
}

void GenerateurAleatoireJeuSerpentEchelle_genererChoix(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, JeuSerpentsEtEchelles *jeuSE, unsigned int nombreDeChoix) {
    for (unsigned int compteurChoix = 0; compteurChoix < nombreDeChoix; compteurChoix++) {
        JeuSerpentsEtEchelles_ajouterChoix(jeuSE, GenerateurAleatoireJeuSerpentEchelle_choisirUneCouleurAleatoirement(randJeuSE));
    }
}

Joueur GenerateurAleatoireJeuSerpentEchelle_genererUnJoueurAleatoirement(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, Iterateur *it) {
    Joueur unJoueur;
    GenerateurAleatoireJeuSerpentEchelle_choisirUnNomAleatoirement(randJeuSE, unJoueur.nom, sizeof(unJoueur.nom));
    unJoueur.position = *it;
    return unJoueur;
}

// MEMORY ALLOCATED
void GenerateurAleatoireJeuSerpentEchelle_genererJoueurs(GenerateurAleatoireJeuSerpentEchelle *randJeuSE, JeuSerpentsEtEchelles *jeuSE, unsigned int nombreDeJoueurs) {
    for (unsigned int indexJoueur = 0; indexJoueur < nombreDeJoueurs; indexJoueur++) {
        Iterateur *it = JeuSerpentsEtEchelles_premiereCase(jeuSE);
        Joueur unJoueur = GenerateurAleatoireJeuSerpentEchelle_genererUnJoueurAleatoirement(randJeuSE, it);
        JeuSerpentsEtEchelles_ajouterJoueur(jeuSE, unJoueur);
        Iterateur_destroy(it);
    }
}

GenerateurAleatoireJeuSerpentEchelle *GenerateurAleatoireJeuSerpentEchelle_create(unsigned int initNombreAleatoire) {
    GenerateurAleatoireJeuSerpentEchelle *randJeuSE = (GenerateurAleatoireJeuSerpentEchelle *)malloc(sizeof(GenerateurAleatoireJeuSerpentEchelle));
    randJeuSE->m_compteurNomJoueurs = 0;
    

    struct GenerateurNombresAleatoires_args args;
    GenerateurNombresAleatoires_args_init(&args);
    args.init = initNombreAleatoire;

    randJeuSE->m_generateurNombresAleatoires = GenerateurNombresAleatoires_create(&args);

    return randJeuSE;
}

void GenerateurAleatoireJeuSerpentEchelle_generer(GenerateurAleatoireJeuSerpentEchelle *randJeuSE,
                                                  JeuSerpentsEtEchelles *jeuSE,
                                                  unsigned int nombreCases, unsigned int nombreDeChoix,
                                                  unsigned int nombreDeJoueurs) {
    randJeuSE->m_compteurNomJoueurs = 0;
    JeuSerpentsEtEchelles_effacer(jeuSE);

    GenerateurAleatoireJeuSerpentEchelle_genererCases(randJeuSE, jeuSE, nombreCases);

    GenerateurAleatoireJeuSerpentEchelle_genererChoix(randJeuSE, jeuSE, nombreDeChoix);

    GenerateurAleatoireJeuSerpentEchelle_genererJoueurs(randJeuSE, jeuSE, nombreDeJoueurs);

}

void GenerateurAleatoireJeuSerpentEchelle_destroy(GenerateurAleatoireJeuSerpentEchelle *randJeuSE) {
    GenerateurNombresAleatoires_destroy(randJeuSE->m_generateurNombresAleatoires);
    free(randJeuSE);
}

