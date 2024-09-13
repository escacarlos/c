#include "file_joueur.h"
#include <string.h>

FILE *Joueur_print(FILE *stream, Joueur *joueur) {
    fprintf(stream, "%s : %d", joueur->nom, Iterateur_positionCourante(&joueur->position));
    return stream;
}

FILE *ListeCirculaire_Joueur_print(FILE *stream, const ListeCirculaire_Joueur *liste) {
    if (ListeCirculaire_Joueur_estVide(liste)) {
        fprintf(stream, "Liste Circulaire est vide\n");
    } else {
        Noeud_Joueur *courant = liste->dernier->suivant;
        while (courant != liste->dernier) {
            fprintf(stream, "%s", courant->element.nom);
            fprintf(stream, "; ");
            courant = courant->suivant;
        }
        fprintf(stream, "%s\n", liste->dernier->element.nom);
    }

    return stream;
}

ListeCirculaire_Joueur *ListeCirculaire_Joueur_create() {
    ListeCirculaire_Joueur *liste = (ListeCirculaire_Joueur *)malloc(sizeof(ListeCirculaire_Joueur));
    if (liste == NULL) {
        perror("Failed to allocate memory for ListeCirculaire_Joueur");
        exit(EXIT_FAILURE);
    }
    liste->dernier = NULL;

    return liste;
}

void ListeCirculaire_Joueur_destroy(ListeCirculaire_Joueur *liste) {
    if (liste->dernier != NULL) {
        Noeud_Joueur *courant = liste->dernier->suivant;
        Noeud_Joueur *autre = courant;
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

ListeCirculaire_Joueur *
ListeCirculaire_Joueur_copy(ListeCirculaire_Joueur *liste, const ListeCirculaire_Joueur *source) {
    if (source->dernier == NULL) {
        liste->dernier = NULL;
        return liste;
    } else {
        liste->dernier = (Noeud_Joueur *) malloc(sizeof(Noeud_Joueur));
        liste->dernier->element = source->dernier->element;
        if (liste->dernier == NULL) {
            perror("Failed to allocate memory for Noeud_Joueur");
            ListeCirculaire_Joueur_destroy(liste);
            exit(EXIT_FAILURE);
        }

        Noeud_Joueur *nouveau = liste->dernier;
        for (Noeud_Joueur *temp = source->dernier->suivant; temp != source->dernier; temp = temp->suivant) {
            nouveau->suivant = (Noeud_Joueur *) malloc(sizeof(Noeud_Joueur));
            if (nouveau->suivant == NULL) {
                perror("Failed to allocate memory for Noeud_Joueur");
                ListeCirculaire_Joueur_destroy(liste);
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

int ListeCirculaire_Joueur_taille(const ListeCirculaire_Joueur *liste) {
    int compteur = 0;
    if (liste->dernier == NULL) return 0;
    Noeud_Joueur *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
        compteur++;
        courant = courant->suivant;
    }
    return compteur + 1;
}

bool ListeCirculaire_Joueur_appartient(const ListeCirculaire_Joueur *liste,
                                       const Joueur *x) {
    if (liste->dernier == NULL) return false;

    Noeud_Joueur *courant = liste->dernier->suivant;
    while (courant != liste->dernier) {
        if (courant->element.nom == x->nom) return true;
        courant = courant->suivant;
    }

    if (liste->dernier->element.nom == x->nom) return true;
    return false;
}

Joueur ListeCirculaire_Joueur_element(const ListeCirculaire_Joueur *liste, int pos) {
    int compteur = 1;
    int taille = ListeCirculaire_Joueur_taille(liste);

    if (pos < 1 || pos > taille + 1) {
        fprintf(stderr, "ListeCirculaire_Joueur_element: Position de l'element est erronee\n");
        exit(EXIT_FAILURE);
    }

    Noeud_Joueur *courant = liste->dernier->suivant;
    while (compteur < pos) {
        courant = courant->suivant;
        compteur++;
    }

    return courant->element;
}

int ListeCirculaire_Joueur_position(const ListeCirculaire_Joueur *liste,
                                    const Joueur *x) {
    if (liste->dernier == NULL) {
        fprintf(
            stderr,
            "ListeCirculaire_Joueur_position: L'element dont on cherche sa position n'est pas present dans la liste (liste vide!)\n");
        return -1;
    }

    int pos = 1;
    Noeud_Joueur *courant = liste->dernier->suivant;

    while (courant != liste->dernier && courant->element.nom != x->nom) {
        courant = courant->suivant;
        pos++;
    }

    if (liste->dernier->element.nom == x->nom) return pos;

    if (courant->element.nom != x->nom) {
        fprintf(
            stderr,
            "ListeCirculaire_Joueur_position: L'element dont on cherche sa position n'est pas present dans la liste\n");
        return -1;
    }

    return pos;
}

bool ListeCirculaire_Joueur_estVide(const ListeCirculaire_Joueur *liste) {
    return liste->dernier == NULL;
}

void ListeCirculaire_Joueur_ajouter(ListeCirculaire_Joueur *liste, Joueur x, int pos) {
    Noeud_Joueur *courant;
    Noeud_Joueur *nouveau;
    int compteur = 1;
    int taille = ListeCirculaire_Joueur_taille(liste);

    nouveau = (Noeud_Joueur *)malloc(sizeof(Noeud_Joueur));
    if (nouveau == NULL) {
        perror("Failed to allocate memory for Noeud_Joueur");
        exit(EXIT_FAILURE);
    }

    if (pos < 1 || pos > taille + 1) {
        fprintf(stderr, "ListeCirculaire_Joueur_ajouter: Invalid position\n");
        free(nouveau); // <-- Added this line to free memory if the position is invalid
        return;
    }

    nouveau->element = x;


    if (liste->dernier == NULL) {
        // First node in the list
        nouveau->suivant = nouveau; // <-- This ensures the new node points to itself
        liste->dernier = nouveau; // <-- Update dernier as it's the only node
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
    // printf("After adding %s at position %d:\n", x->nom, pos);
    // ListeCirculaire_Joueur_print(stdout, liste);
    // printf("\n");
}

void ListeCirculaire_Joueur_ajouterFin(ListeCirculaire_Joueur *liste, Joueur x) {
    ListeCirculaire_Joueur_ajouter(liste, x, ListeCirculaire_Joueur_taille(liste) + 1);
}

void ListeCirculaire_Joueur_enleverEl(ListeCirculaire_Joueur *liste,
                                      const Joueur *x) {
    if (liste->dernier == NULL) {
        fprintf(
            stderr,
            "ListeCirculaire_Joueur_enleverEl: L'element dont on veut enlever n'est pas present dans la liste (liste vide!)\n");
        return;
    }

    Noeud_Joueur *courant = liste->dernier->suivant;
    Noeud_Joueur *pred = liste->dernier;

    do {
        if (courant->element.nom == x->nom) {
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

    fprintf(stderr, "ListeCirculaire_Joueur_enleverEl: L'element a enlever n'est pas present dans la liste\n");
}

void ListeCirculaire_Joueur_enleverPos(ListeCirculaire_Joueur *liste, int pos) {
    Noeud_Joueur *trouve;

    if (pos < 1 || pos > ListeCirculaire_Joueur_taille(liste)) {
        fprintf(stderr, "ListeCirculaire_Joueur_enleverPos: Position pour l'enlevement est erronee\n");
        return;
    }

    if (pos == 1) {
        trouve = liste->dernier->suivant;
        liste->dernier->suivant = liste->dernier->suivant->suivant;

        if (trouve == liste->dernier) liste->dernier = NULL;
    } else {
        int cpt = 1;
        Noeud_Joueur *courant = liste->dernier->suivant;
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

File_Joueur *File_Joueur_create() {
    File_Joueur *file = (File_Joueur *) malloc(sizeof(File_Joueur));
    if (file == NULL) {
        perror("Failed to allocate memory for File_Joueur");
        exit(EXIT_FAILURE);
    }

    ListeCirculaire_Joueur *liste = ListeCirculaire_Joueur_create();

    file->liste = liste;

    return file;
}

void File_Joueur_destroy(File_Joueur *file) {
    ListeCirculaire_Joueur_destroy(file->liste);
    file->liste = NULL;
    free(file);
}

void File_Joueur_enfiler(File_Joueur *file, Joueur x) {
    ListeCirculaire_Joueur_ajouterFin(file->liste, x);
}

Joueur File_Joueur_defiler(File_Joueur *file) {
    if (ListeCirculaire_Joueur_taille(file->liste) < 1) {
        fprintf(stderr, "File_Joueur_defiler: La file est vide\n");
        exit(EXIT_FAILURE);
    }
    Joueur ret = ListeCirculaire_Joueur_element(file->liste, 1);
    ListeCirculaire_Joueur_enleverPos(file->liste, 1);
    return ret;
}

int File_Joueur_taille(const File_Joueur *file) {
    return ListeCirculaire_Joueur_taille(file->liste);
}

FILE *File_Joueur_print(FILE *stream, const File_Joueur *file) {
    return ListeCirculaire_Joueur_print(stream, file->liste);
}
