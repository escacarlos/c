#include "jeu_serpent_echelles.h"

#include <string.h>

struct Resultat *Resultat_create(unsigned int p_nombreDeTours, const char *p_nom) {
    struct Resultat *res = (struct Resultat *)malloc(sizeof(struct Resultat));
    res->nombreDeTours = p_nombreDeTours;
    
    // Allocate memory for the nom field
    res->nom = (char *) malloc(strlen(p_nom) + 1);
    if (res->nom == NULL) {
        perror("Failed to allocate memory for joueur name");
        free(res);  // Free previously allocated memory
        exit(EXIT_FAILURE);
    }

    strcpy(res->nom, p_nom);

    return res;
}

void Resultat_destroy(struct Resultat *res) {
    free(res->nom);
    free(res);
}

JeuSerpentsEtEchelles *JeuSerpentsEtEchelles_create() {
    
    JeuSerpentsEtEchelles *jeuSE = (JeuSerpentsEtEchelles *)malloc(sizeof(JeuSerpentsEtEchelles));
    if (jeuSE == NULL) {
        perror("Failed to allocate memory for JeuSerpentsEtEchelles");
        exit(EXIT_FAILURE);
    }

    ListeDeCases *p_cases = ListeDeCases_create();
    ListeCirculaire_Couleur *p_choix = ListeCirculaire_Couleur_create();
    File_Joueur *p_Joueur = File_Joueur_create();

    jeuSE->m_cases = p_cases;
    jeuSE->m_choix = p_choix;
    jeuSE->m_joueurs = p_Joueur;

    return jeuSE;
}

void JeuSerpentsEtEchelles_destroy(JeuSerpentsEtEchelles *jeuSE) {
    ListeDeCases_destroy(jeuSE->m_cases);
    ListeCirculaire_Couleur_destroy(jeuSE->m_choix);
    File_Joueur_destroy(jeuSE->m_joueurs);
    free(jeuSE);
}

void JeuSerpentsEtEchelles_afficherResultats(JeuSerpentsEtEchelles *jeuSE, struct Resultat gagnant) {
    
    if (strcmp(gagnant.nom, "") != 0)
        printf("Gagnant : %s\n", gagnant.nom);
    else
        printf("Aucun gagnant\n");
    printf("Nombre de tours realises: %u\n", gagnant.nombreDeTours);
    printf("Position des joueurs: \n");
    int nPlayers = File_Joueur_taille(jeuSE->m_joueurs);
    for (int i = 0; i < nPlayers; i++) {
        Joueur player = File_Joueur_defiler(jeuSE->m_joueurs);
        Joueur_print(stdout, &player);
        printf("%c", ' ');
    }
    puts("");
    printf("Plateau de jeu: \n");
    ListeDeCases_print(stdout, jeuSE->m_cases);
    printf("Liste de choix: \n");
    ListeCirculaire_Couleur_print(stdout, jeuSE->m_choix);
}

void JeuSerpentsEtEchelles_effacer(JeuSerpentsEtEchelles *jeuSE) {
    while (ListeDeCases_taille(jeuSE->m_cases) > 0)
        ListeDeCases_enleverCase(jeuSE->m_cases, 1);
    while (ListeCirculaire_Couleur_taille(jeuSE->m_choix) > 0)
        ListeCirculaire_Couleur_enleverPos(jeuSE->m_choix, 1);
    while (File_Joueur_taille(jeuSE->m_joueurs) > 0) {
        File_Joueur_defiler(jeuSE->m_joueurs);
    }
}

void JeuSerpentsEtEchelles_ajouterCase(JeuSerpentsEtEchelles *jeuSE, Case *p_case) {
    ListeDeCases_ajouterCaseALaFin(jeuSE->m_cases, p_case);
}

void JeuSerpentsEtEchelles_ajouterChoix(JeuSerpentsEtEchelles *jeuSE, Couleur couleur) {
    ListeCirculaire_Couleur_ajouterFin(jeuSE->m_choix, &couleur);
}

void JeuSerpentsEtEchelles_ajouterJoueur(JeuSerpentsEtEchelles *jeuSE, Joueur joueur) {
    File_Joueur_enfiler(jeuSE->m_joueurs, joueur);
}

Iterateur *JeuSerpentsEtEchelles_premiereCase(JeuSerpentsEtEchelles *jeuSE) {
    
    Iterateur *it = Iterateur_create(jeuSE->m_cases);
    return it;  
}

struct Resultat *JeuSerpentsEtEchelles_jouer(JeuSerpentsEtEchelles *jeuSE, unsigned int maximumDeTours) {

    unsigned int tourActuel = 0;
    
    ListeCirculaire_Couleur *choixCourante = ListeCirculaire_Couleur_create();
    ListeCirculaire_Couleur_copy(choixCourante, jeuSE->m_choix);
    while (tourActuel < maximumDeTours - 1) {
        ++tourActuel;
        int nombreJoueur = File_Joueur_taille(jeuSE->m_joueurs);
        for(int i = 0; i < nombreJoueur; ++i) {
            
            Joueur unJoueur = File_Joueur_defiler(jeuSE->m_joueurs);

            Couleur uneCouleur = ListeCirculaire_Couleur_element(choixCourante, 1);
            ListeCirculaire_Couleur_enleverPos(choixCourante, 1);
            ListeCirculaire_Couleur_ajouterFin(choixCourante, &uneCouleur);
            Decoration decorationCourante = AUCUNE;
            if (Iterateur_existeCaseSuivanteCouleur(&unJoueur.position, uneCouleur)) {
                Iterateur_caseSuivante(&unJoueur.position, uneCouleur);
                decorationCourante = Iterateur_caseCourante(&unJoueur.position)->decoration;
            }
            

            if (decorationCourante == SERPENT) {

                uneCouleur = ListeCirculaire_Couleur_element(choixCourante, 1);
                ListeCirculaire_Couleur_enleverPos(choixCourante, 1);
                ListeCirculaire_Couleur_ajouterFin(choixCourante, &uneCouleur);

                if (Iterateur_existeCasePrecedenteCouleur(&unJoueur.position, uneCouleur)) {
                    Iterateur_casePrecedente(&unJoueur.position, uneCouleur);
                }

                
            } else if (decorationCourante == ECHELLE) {
                uneCouleur = ListeCirculaire_Couleur_element(choixCourante, 1);
                ListeCirculaire_Couleur_enleverPos(choixCourante, 1);
                ListeCirculaire_Couleur_ajouterFin(choixCourante, &uneCouleur);

                if (Iterateur_existeCaseSuivanteCouleur(&unJoueur.position, uneCouleur)) {
                    Iterateur_caseSuivante(&unJoueur.position, uneCouleur);
                }
            }

            if (Iterateur_estADerniereCase(&unJoueur.position)) {
                File_Joueur_enfiler(jeuSE->m_joueurs, unJoueur);

                ListeCirculaire_Couleur_destroy(choixCourante);
                
                struct Resultat *res = Resultat_create(tourActuel, unJoueur.nom);
                return res;
            }
            
            File_Joueur_enfiler(jeuSE->m_joueurs, unJoueur);
            
        }
    }

    ListeCirculaire_Couleur_destroy(choixCourante);

    struct Resultat *res = Resultat_create(maximumDeTours, "");
    return res;
}
