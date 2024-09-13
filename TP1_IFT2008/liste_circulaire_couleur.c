#include "liste_circulaire_couleur.h"

FILE *ListeCirculaire_Couleur_print(FILE *stream, const ListeCirculaire_Couleur *liste) {
  if (ListeCirculaire_Couleur_estVide(liste)) {
    fprintf(stream, "Liste Circulaire est vide\n");
  } else {
    Noeud_Couleur *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
      fprintf(stream, "%d", courant->element);
      fprintf(stream, "; ");
      courant = courant->suivant;
    }
    fprintf(stream, "%d\n", liste->dernier->element);
  }

  return stream;
}

ListeCirculaire_Couleur *ListeCirculaire_Couleur_create() {
    
    ListeCirculaire_Couleur *liste = (ListeCirculaire_Couleur *)
        malloc(sizeof(ListeCirculaire_Couleur));
    if (liste == NULL) {
        perror("Failed to allocate memory for ListeCirculaire_Couleur");
        exit(EXIT_FAILURE);
    }
    liste->dernier = NULL;

    return liste;
}

void ListeCirculaire_Couleur_destroy(ListeCirculaire_Couleur *liste) {
    
    if (liste->dernier != NULL) {
        Noeud_Couleur *courant = liste->dernier->suivant;
        Noeud_Couleur *autre = courant;
        while (courant != liste->dernier) {
            courant = courant->suivant;
            free(autre);
            autre = courant;
        }
        free(liste->dernier);
    }
    liste->dernier = NULL;
    free(liste);
}

ListeCirculaire_Couleur *ListeCirculaire_Couleur_copy(ListeCirculaire_Couleur *liste, const ListeCirculaire_Couleur *source) {

    if (source->dernier == NULL) {
        liste->dernier = NULL;
        return liste;
    } else {
        liste->dernier = (Noeud_Couleur *)malloc(sizeof(Noeud_Couleur));
        liste->dernier->element = source->dernier->element;
        if (liste->dernier == NULL) {
            perror("Failed to allocate memory for Noeud_Couleur");
            ListeCirculaire_Couleur_destroy(liste);
            exit(EXIT_FAILURE);
        }

        Noeud_Couleur *nouveau = liste->dernier;
        for (Noeud_Couleur *temp = source->dernier->suivant; temp != source->dernier; temp = temp->suivant) {
            nouveau->suivant = (Noeud_Couleur *)malloc(sizeof(Noeud_Couleur));
            if (nouveau->suivant == NULL) {
                perror("Failed to allocate memory for Noeud_Couleur");
                ListeCirculaire_Couleur_destroy(liste);
                exit(EXIT_FAILURE);
            }

            nouveau->suivant->element = temp->element;
            nouveau = nouveau->suivant;
            nouveau->suivant = liste->dernier;
        }
        nouveau->suivant = liste->dernier;
    }
    return liste;
}

int ListeCirculaire_Couleur_taille(const ListeCirculaire_Couleur *liste) {
    
    int compteur = 0;
    if (liste->dernier == NULL) return 0;
    Noeud_Couleur *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
        compteur++;
        courant = courant->suivant;
    }
    return compteur + 1;
}

bool ListeCirculaire_Couleur_appartient(const ListeCirculaire_Couleur *liste,
    const Couleur *x) {
    
    if (liste->dernier == NULL) return false;

    Noeud_Couleur *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
        if (courant->element == *x) return true;
        courant = courant->suivant;
    }

    if (liste->dernier->element == *x) return true;
    return false;
}

Couleur ListeCirculaire_Couleur_element(const ListeCirculaire_Couleur *liste, int pos) {

    int compteur = 1;
    int taille = ListeCirculaire_Couleur_taille(liste);

    if (pos < 1 || pos > taille + 1) {
        fprintf(stderr, "ListeCirculaire_Couleur_element: Position de l'element est erronee\n");
        exit(EXIT_FAILURE);
    }

    Noeud_Couleur *courant = liste->dernier->suivant;
    while (compteur < pos) {
        courant = courant->suivant;
        compteur++;
    }
    return courant->element;
}

int ListeCirculaire_Couleur_position(const ListeCirculaire_Couleur *liste, 
    const Couleur *x) {
    
    if (liste->dernier == NULL) {
        fprintf(stderr, "ListeCirculaire_Couleur_position: L'element dont on cherche sa position n'est pas present dans la liste (liste vide!)\n");
        return -1;
    }

    int pos = 1;
    Noeud_Couleur *courant = liste->dernier->suivant;

    while (courant != liste->dernier && courant->element != *x) {
        courant = courant->suivant;
        pos++;
    }

    if (liste->dernier->element == *x) return pos;

    if (courant->element != *x) {
        fprintf(stderr, "ListeCirculaire_Couleur_position: L'element dont on cherche sa position n'est pas present dans la liste\n");
        return -1;        
    }

    return pos;
}

bool ListeCirculaire_Couleur_estVide(const ListeCirculaire_Couleur *liste) {

    return liste->dernier == NULL;
}

void ListeCirculaire_Couleur_ajouter(ListeCirculaire_Couleur *liste, const Couleur *x, int pos) {
    Noeud_Couleur *courant;
    Noeud_Couleur *nouveau;
    int compteur = 1;
    int taille = ListeCirculaire_Couleur_taille(liste);

    nouveau = (Noeud_Couleur *)malloc(sizeof(Noeud_Couleur));
    if (nouveau == NULL) {
        perror("Failed to allocate memory for Noeud_Couleur");
        exit(EXIT_FAILURE);
    }

    if (pos < 1 || pos > taille + 1) {
        fprintf(stderr, "ListeCirculaire_Couleur_ajouter: Invalid position\n");
        free(nouveau);  // <-- Added this line to free memory if the position is invalid
        return;
    }

    nouveau->element = *x;
    

    if (liste->dernier == NULL) { 
        // First node in the list
        nouveau->suivant = nouveau;  // <-- This ensures the new node points to itself
        liste->dernier = nouveau;    // <-- Update dernier as it's the only node
    } else {
        if (pos == 1) { 
            // Insertion at the first position
            nouveau->suivant = liste->dernier->suivant;
            liste->dernier->suivant = nouveau;
        } else {
            // Traverse to the position before where we want to insert
            courant = liste->dernier->suivant;

            while (compteur < pos - 1) {
                courant = courant->suivant;
                compteur++;
            }
            nouveau->suivant = courant->suivant;
            courant->suivant = nouveau;

            // Update dernier only if we're adding at the end
            if (pos == taille + 1) {
                liste->dernier = nouveau;
            }
        }
    }
    // Debug prints to see the list after each insertion
    // printf("After adding %d at position %d:\n", *x, pos);
    // ListeCirculaire_Couleur_print(stdout, liste);
    // printf("\n");
}

void ListeCirculaire_Couleur_ajouterFin(ListeCirculaire_Couleur *liste, 
    const Couleur *x) {
    
    ListeCirculaire_Couleur_ajouter(liste, x, ListeCirculaire_Couleur_taille(liste) + 1);
}

void ListeCirculaire_Couleur_enleverEl(ListeCirculaire_Couleur *liste,
    const Couleur *x) {

    if (liste->dernier == NULL) {
        fprintf(stderr, "ListeCirculaire_Couleur_enleverEl: L'element dont on veut enlever n'est pas present dans la liste (liste vide!)\n");
        return;
    }

    Noeud_Couleur *courant = liste->dernier->suivant;
    Noeud_Couleur *pred = liste->dernier;

    do {
        if (courant->element == *x) {
            if (courant == liste->dernier && courant->suivant == liste->dernier) {
                // Only one element in the list
                liste->dernier = NULL;
            } else {
                if (courant == liste->dernier) {
                    liste->dernier = pred;
                }
                pred->suivant = courant->suivant;
            }
            free(courant);
            return; 
        }
        pred = courant;
        courant = courant->suivant;
    } while (courant != liste->dernier->suivant);

    fprintf(stderr, "ListeCirculaire_Couleur_enleverEl: L'element a enlever n'est pas present dans la liste\n");
}

void ListeCirculaire_Couleur_enleverPos(ListeCirculaire_Couleur *liste, int pos) {

    Noeud_Couleur *trouve;

    if (pos < 1 || pos > ListeCirculaire_Couleur_taille(liste)) {
        fprintf(stderr, "ListeCirculaire_Couleur_enleverPos: Position pour l'enlevement est erronee\n");
        return;
    }

    if (pos == 1) {
        trouve = liste->dernier->suivant;
        liste->dernier->suivant = liste->dernier->suivant->suivant;

        if (trouve == liste->dernier) liste->dernier = NULL;
    } else {
        int cpt = 1;
        Noeud_Couleur *courant = liste->dernier->suivant;
        while (cpt < pos - 1) {
            courant = courant->suivant;
            cpt++;
        }
        trouve = courant->suivant;
        courant->suivant = trouve->suivant;

        if (trouve == liste->dernier) liste->dernier = courant;
    }

    trouve->suivant = NULL;
    free(trouve);
}