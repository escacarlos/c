#ifndef _FILE_H_
#define _FILE_H_

#include "liste_circulaire.h"

typedef struct File_NAME {
    ListeCirculaire_NAME *liste;
} File_NAME;

File_NAME *File_NAME_create() {
    
    File_NAME *file = (File_NAME *)malloc(sizeof(File_NAME));
    if (file == NULL) {
        perror("Failed to allocate memory for File_NAME");
        exit(EXIT_FAILURE);
    }

    ListeCirculaire_NAME *liste = ListeCirculaire_NAME_create();

    file->liste = liste;

    return file;
}

void File_NAME_destroy(File_NAME *file) {
    ListeCirculaire_NAME_destroy(file->liste);
    file->liste = NULL;
    free(file);
}

void File_NAME_enfiler(File_NAME *file, const TYPE *x) {
    ListeCirculaire_NAME_ajouterFin(file->liste, x);
}

TYPE File_NAME_defiler(File_NAME *file) {
    if (ListeCirculaire_NAME_taille(file->liste) < 1) {
        fprintf(stderr, "File_NAME_defiler: La file est vide\n");
        exit(EXIT_FAILURE);
    }
    TYPE ret = ListeCirculaire_NAME_element(file->liste, 1);
    ListeCirculaire_NAME_enleverPos(file->liste, 1);
    return ret;
}

int File_NAME_taille(const File_NAME *file) {
    return ListeCirculaire_NAME_taille(file->liste);
}

FILE *File_NAME_print(FILE *stream, const File_NAME *file) {
    return ListeCirculaire_NAME_print(stream, file->liste);
}


#endif /*_FILE_H_*/

