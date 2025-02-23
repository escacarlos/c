#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_MACHINES 5 
#define N_STOCK 100

pthread_mutex_t mutex;
int stock[N_STOCK];
bool article_traite[N_STOCK]; // Tableau pour suivre l'état des articles traités
int article_index = 0; // Indice de l'article actue

// Initialisation du stock d'articles et de leur statut de traitement
void initialiser_stock() {
    for (int i = 0; i < N_STOCK; i++) {
        stock[i] = i + 1;
        article_traite[i] = false;
    }
}

// Fonction simulant une tâche effectuée par une machine sur un article
void simuler_tache(int machine_id, int article) {
    int resultat = machine_id * 100 + article;
    printf("Machine: %d traite l'article %d, assigne SKU: %d\n",
        machine_id, article, resultat);
    usleep(rand() % 10000);
}

void* machine_worker(void* arg) {
    int machine_id = *(int*)arg;
    int machine_compteur = 0;

    while (true) {
        pthread_mutex_lock(&mutex);

        // Vérifie si tous les articles sont traités
        if (article_index >= N_STOCK) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Affecter l'indice d'article actuel
        int index = article_index;
        article_index++;
        pthread_mutex_unlock(&mutex);

        // Si l'article n'est pas encore traité, la machine le traite
        if (!article_traite[index]) {
            simuler_tache(machine_id + 1, stock[index]);
            article_traite[index] = true; // Marquer l'article comme traité
            machine_compteur++;
        }
    }
    printf("Machine %d a fini son travail avec %d articles traites\n", machine_id, machine_compteur);
    return NULL;
}

int main() {
    pthread_t machines[N_MACHINES];
    int machines_ids[N_MACHINES];

    initialiser_stock();
    pthread_mutex_init(&mutex, 0);

    for (int i = 0; i < N_MACHINES; i++) {
        machines_ids[i] = i;
        pthread_create(&machines[i], 0, machine_worker, &machines_ids[i]);
    }

    for (int i = 0; i < N_MACHINES; i++) {
        pthread_join(machines[i], 0);
    }

    pthread_mutex_destroy(&mutex);

    //test pour checker tous les articles traités
    bool flag = true;
    for (int i = 0; i < N_STOCK; i++) {
        if(!article_traite[i]){
            printf("Erreur: l'article %d n'a pas ete traite.\n",
                stock[i]);
            flag = false;
        }
    }
    if (flag) {
        printf("Tous les articles ont ete trates avec succes.\n");
    }

    return 0;
}
