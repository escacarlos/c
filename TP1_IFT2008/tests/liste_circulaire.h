#ifndef _LISTECIRCULAIRE_H_
#define _LISTECIRCULAIRE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Noeud_NAME {
    TYPE element;
    struct Noeud_NAME *suivant;
} Noeud_NAME;

typedef struct ListeCirculaire_NAME {
    Noeud_NAME *dernier;
} ListeCirculaire_NAME;

FILE *ListeCirculaire_NAME_print(FILE *stream, const ListeCirculaire_NAME *liste);

ListeCirculaire_NAME *ListeCirculaire_NAME_create() {
    
    ListeCirculaire_NAME *liste = (ListeCirculaire_NAME *)
        malloc(sizeof(ListeCirculaire_NAME));
    if (liste == NULL) {
        perror("Failed to allocate memory for ListeCirculaire_NAME");
        exit(EXIT_FAILURE);
    }
    liste->dernier = NULL;

    return liste;
}

void ListeCirculaire_NAME_destroy(ListeCirculaire_NAME *liste) {
    
    if (liste->dernier != NULL) {
        Noeud_NAME *courant = liste->dernier->suivant;
        Noeud_NAME *autre = courant;
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

ListeCirculaire_NAME *ListeCirculaire_NAME_copy(ListeCirculaire_NAME *liste, const ListeCirculaire_NAME *source) {

    if (source->dernier == NULL) {
        liste->dernier = NULL;
        return liste;
    } else {
        liste->dernier = (Noeud_NAME *)malloc(sizeof(Noeud_NAME));
        liste->dernier->element = source->dernier->element;
        if (liste->dernier == NULL) {
            perror("Failed to allocate memory for Noeud_NAME");
            ListeCirculaire_NAME_destroy(liste);
            exit(EXIT_FAILURE);
        }

        Noeud_NAME *nouveau = liste->dernier;
        for (Noeud_NAME *temp = source->dernier->suivant; temp != source->dernier; temp = temp->suivant) {
            nouveau->suivant = (Noeud_NAME *)malloc(sizeof(Noeud_NAME));
            if (nouveau->suivant == NULL) {
                perror("Failed to allocate memory for Noeud_NAME");
                ListeCirculaire_NAME_destroy(liste);
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

int ListeCirculaire_NAME_taille(const ListeCirculaire_NAME *liste) {
    
    int compteur = 0;
    if (liste->dernier == NULL) return 0;
    Noeud_NAME *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
        compteur++;
        courant = courant->suivant;
    }
    return compteur + 1;
}

bool ListeCirculaire_NAME_appartient(const ListeCirculaire_NAME *liste,
    const TYPE *x) {
    
    if (liste->dernier == NULL) return false;

    Noeud_NAME *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
        if (courant->element.ID == x->ID) return true;
        courant = courant->suivant;
    }

    if (liste->dernier->element.ID == x->ID) return true;
    return false;
}

TYPE ListeCirculaire_NAME_element(const ListeCirculaire_NAME *liste, int pos) {

    int compteur = 1;
    int taille = ListeCirculaire_NAME_taille(liste);

    if (pos < 1 || pos > taille + 1) {
        fprintf(stderr, "ListeCirculaire_NAME_element: Position de l'element est erronee\n");
        exit(EXIT_FAILURE);
    }

    Noeud_NAME *courant = liste->dernier->suivant;
    while (compteur < pos) {
        courant = courant->suivant;
        compteur++;
    }
    return courant->element;
}

int ListeCirculaire_NAME_position(const ListeCirculaire_NAME *liste, 
    const TYPE *x) {
    
    if (liste->dernier == NULL) {
        fprintf(stderr, "ListeCirculaire_NAME_position: L'element dont on cherche sa position n'est pas present dans la liste (liste vide!)\n");
        return -1;
    }

    int pos = 1;
    Noeud_NAME *courant = liste->dernier->suivant;

    while (courant != liste->dernier && courant->element.ID != x->ID) {
        courant = courant->suivant;
        pos++;
    }

    if (liste->dernier->element.ID == x->ID) return pos;

    if (courant->element.ID != x->ID) {
        fprintf(stderr, "ListeCirculaire_NAME_position: L'element dont on cherche sa position n'est pas present dans la liste\n");
        return -1;        
    }

    return pos;
}

bool ListeCirculaire_NAME_estVide(const ListeCirculaire_NAME *liste) {

    return liste->dernier == NULL;
}

void ListeCirculaire_NAME_ajouter(ListeCirculaire_NAME *liste, const TYPE *x, int pos) {
    Noeud_NAME *courant;
    Noeud_NAME *nouveau;
    int compteur = 1;
    int taille = ListeCirculaire_NAME_taille(liste);

    nouveau = (Noeud_NAME *)malloc(sizeof(Noeud_NAME));
    if (nouveau == NULL) {
        perror("Failed to allocate memory for Noeud_NAME");
        exit(EXIT_FAILURE);
    }

    if (pos < 1 || pos > taille + 1) {
        fprintf(stderr, "ListeCirculaire_NAME_ajouter: Invalid position\n");
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
    printf("After adding %s at position %d:\n", x->name, pos);
    ListeCirculaire_NAME_print(stdout, liste);
    printf("\n");
}

void ListeCirculaire_NAME_ajouterFin(ListeCirculaire_NAME *liste, 
    const TYPE *x) {
    
    ListeCirculaire_NAME_ajouter(liste, x, ListeCirculaire_NAME_taille(liste) + 1);
}

void ListeCirculaire_NAME_enleverEl(ListeCirculaire_NAME *liste,
    const TYPE *x) {

    if (liste->dernier == NULL) {
        fprintf(stderr, "ListeCirculaire_NAME_enleverEl: L'element dont on veut enlever n'est pas present dans la liste (liste vide!)\n");
        return;
    }

    Noeud_NAME *courant = liste->dernier->suivant;
    Noeud_NAME *pred = liste->dernier;

    do {
        if (courant->element.ID == x->ID) {
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

    fprintf(stderr, "ListeCirculaire_NAME_enleverEl: L'element a enlever n'est pas present dans la liste\n");
}

void ListeCirculaire_NAME_enleverPos(ListeCirculaire_NAME *liste, int pos) {

    Noeud_NAME *trouve;

    if (pos < 1 || pos > ListeCirculaire_NAME_taille(liste)) {
        fprintf(stderr, "ListeCirculaire_NAME_enleverPos: Position pour l'enlevement est erronee\n");
        return;
    }

    if (pos == 1) {
        trouve = liste->dernier->suivant;
        liste->dernier->suivant = liste->dernier->suivant->suivant;

        if (trouve == liste->dernier) liste->dernier = NULL;
    } else {
        int cpt = 1;
        Noeud_NAME *courant = liste->dernier->suivant;
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

FILE *ListeCirculaire_NAME_print(FILE *stream, const ListeCirculaire_NAME *liste) {
  if (ListeCirculaire_NAME_estVide(liste)) {
    fprintf(stream, "Liste Circulaire est vide\n");
  } else {
    Noeud_NAME *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
      fprintf(stream, "%s", courant->element.name);
      fprintf(stream, "; ");
      courant = courant->suivant;
    }
    fprintf(stream, "%s\n", liste->dernier->element.name);
  }

  return stream;
}

#endif /*_LISTECIRCULAIRE_H_*/