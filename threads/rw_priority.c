#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Déclaration de la ressource partagée et du verrou de lecture/écriture
pthread_rwlock_t rwlock;
int counter_reader = 0;
int counter_writer = 0;
const char *filename = "shared_file.txt";

// Fonction de lecture
void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {

        pthread_rwlock_rdlock(&rwlock);  // Verrou de lecture
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Erreur lors de l'ouverture du fichier en lecture");
            pthread_rwlock_unlock(&rwlock);
            continue;
        }

        // Affiche le message en vert et en gras
        printf("\033[1;32mLecteur %d: ------------------------lecture du fichier----------------------------\033[0m\n", id);

        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        counter_reader++;
        printf("FIN LECTURE, lecteur %d\n", id);
        printf("Total acces pour les lecteurs: %d\n", counter_reader);

        fclose(file);
        pthread_rwlock_unlock(&rwlock);  // Déverrouille la lecture
        sleep(1);
    }
}

// Fonction d'écriture
void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {

        pthread_rwlock_wrlock(&rwlock);  // Verrou d'écriture
        FILE *file = fopen(filename, "a");
        if (file == NULL) {
            perror("Erreur lors de l'ouverture du fichier en ecriture");
            pthread_rwlock_unlock(&rwlock);
            continue;
        }

        printf("======================DEBUT ECRITURE, ecrivain %d\n", id);
        fprintf(file, "Ecrivain %d ecrit dans le fichier.\n", id);
        counter_writer++;
        printf("======================FIN ECRITURE, ecrivain %d\n", id);
        printf("Total acces pour les ecrivains: %d\n", counter_writer);
        fflush(file);

        fclose(file);
        pthread_rwlock_unlock(&rwlock);  // Déverrouille l'écriture

        sleep(2);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int ids[NUM_READERS + NUM_WRITERS];

    FILE *file = fopen(filename, "w");
    fclose(file);

    pthread_rwlock_init(&rwlock, NULL);  // Initialisation du verrou

    // Création des threads lecteurs
    for (int i = 0; i < NUM_READERS; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    // Création des threads écrivains
    for (int i = 0; i < NUM_WRITERS; i++) {
        ids[NUM_READERS + i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[NUM_READERS + i]);
    }

    // Attendre la fin des threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);  // Détruire le verrou
    return 0;
}
