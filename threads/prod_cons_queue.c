#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define QUEUE_CAPACITY 10

int compteur_prod = 0;
int compteur_cons = 0;
pthread_mutex_t compteur_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {            // la Queue que sera partage
    int items[QUEUE_CAPACITY];
    int premier;
    int dernier;
    int taille;
    int nombre_items_pour_test;     // nombre d'items maximale a produire
    pthread_mutex_t mutex_queue;    // pour proteger l'access a la file
    pthread_cond_t plein;       // pour attendre si file pleine ou signaler file non pas pleine
    pthread_cond_t vide;        // pour attendre si file vide ou signaler file non pas vide
} Queue;

void init_queue(Queue *queue) {
    queue->premier = 0;
    queue->dernier = 0;
    queue->taille = 0;
    queue->nombre_items_pour_test = 0;
    pthread_mutex_init(&queue->mutex_queue, NULL);
    pthread_cond_init(&queue->plein, NULL);
    pthread_cond_init(&queue->vide, NULL);
}

void enfiler(Queue *queue, int item) {  // methode pour enfiler pour les producteurs
    pthread_mutex_lock(&queue->mutex_queue);    // lock de la file

    while (queue->taille == QUEUE_CAPACITY) {
        pthread_cond_wait(&queue->plein, &queue->mutex_queue);  // file pleine, il faut attendre, libere le mutex
    }

    queue->items[queue->dernier] = item;    // enfiler a la fin
    queue->dernier = (queue->dernier + 1) % QUEUE_CAPACITY; // mantient la position du dernier element dans la queue
    queue->taille++;

    printf("enfiler: Nombre d'elements dans la file: %d\n", queue->taille);

    pthread_cond_signal(&queue->vide);  //  signaler que il y a des elements disponibles pour consommer
    pthread_mutex_unlock(&queue->mutex_queue);  // libere la file
}

int defiler(Queue *queue) {     // methode pour defiler pour les consommateurs
    pthread_mutex_lock(&queue->mutex_queue);    // lock de la file

    while (queue->taille == 0) {
        pthread_cond_wait(&queue->vide, &queue->mutex_queue);   // file vide, il faut attendre, libere le mutex
    }

    int item = queue->items[queue->premier];    // defiler le premier element
    queue->premier = (queue->premier + 1) % QUEUE_CAPACITY; // mantient la position du premier element dans la queue
    queue->taille--;

    printf("defiler: Nombre d'elements dans la file: %d\n", queue->taille);

    pthread_cond_signal(&queue->plein); //  signaler que il y a de la place dans la file pour produire
    pthread_mutex_unlock(&queue->mutex_queue);  // libere la file

    return item;
}

void *producteur(void *arg) {
    Queue *queue = (Queue *)arg;
    while (1) {
        pthread_mutex_lock(&compteur_mutex);    // pour proteger le compteur des producteurs
        if (compteur_prod >= queue->nombre_items_pour_test) {   // condition pour arreter de produire
            pthread_mutex_unlock(&compteur_mutex);
            break;
        }
        int item = rand() % 1000;
        compteur_prod++;    // compter les items produits
        pthread_mutex_unlock(&compteur_mutex);

        enfiler(queue, item);
        printf("Producteur a produit le item %d\n", item);
        printf("items produits: %d\n", compteur_prod);
        usleep(rand() % 100000);
    }
    return NULL;
}

void *consommateur(void *arg) {
    Queue *queue = (Queue *)arg;
    while (1) {
        pthread_mutex_lock(&compteur_mutex);    // pour proteger le compteur de consommateurs
        if (compteur_cons >= queue->nombre_items_pour_test) {   // condition pour arreter de lire
            pthread_mutex_unlock(&compteur_mutex);
            break;
        }
        compteur_cons++;    // compter les items consomme
        pthread_mutex_unlock(&compteur_mutex);

        int item = defiler(queue);
        printf("Consomateur a consomme le item: %d\n", item);
        usleep(rand() % 100000);
    }
    return NULL;
}

void test_3prod_3cons_50items(Queue *queue);

void test_5prod_10cons_100items(Queue *queue);

void test_10prod_5cons_100items(Queue *queue);

void test_20prod_20cons_500items(Queue *queue);

int main() {
    srand(time(NULL));

    // allouer des resources pour la file
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Erreur d'allocation de memoire\n");
        return -1;
    }
    init_queue(queue);

    // TESTS: decommenter le test que voulez faire
    test_3prod_3cons_50items(queue);
    // test_5prod_10cons_100items(queue);
    // test_10prod_5cons_100items(queue);
    // test_20prod_20cons_500items(queue);

    // liberer les resources
    pthread_mutex_destroy(&queue->mutex_queue);
    pthread_cond_destroy(&queue->plein);
    pthread_cond_destroy(&queue->vide);
    pthread_mutex_destroy(&compteur_mutex);
    free(queue);

    return 0;
}

void create_join_threads(Queue* queue, int nom_producteurs, int nom_consommateurs) {
    pthread_t producteurs[nom_producteurs];
    pthread_t consommateurs[nom_consommateurs];

    // creation des producteurs
    for (int i = 0; i < nom_producteurs; i++) {
        pthread_create(&producteurs[i], NULL, producteur, queue);
    }
    // creation des consommateurs
    for (int i = 0; i < nom_consommateurs; i++) {
        pthread_create(&consommateurs[i], NULL, consommateur, queue);
    }

    // attendre tous les producteurs et consommateurs (threads)
    for (int i = 0; i < nom_producteurs; i++) {
        pthread_join(producteurs[i], NULL);
    }
    for (int i = 0; i < nom_consommateurs; i++) {
        pthread_join(consommateurs[i], NULL);
    }

    // verifier la condition de arret et la syncronisation
    printf("Total items produits: %d\n", compteur_prod);
    printf("Total items consommes: %d\n", compteur_cons);
}

void test_3prod_3cons_50items(Queue *queue) {

    int nom_producteurs = 3;   // nombre de producteurs
    int nom_consommateurs = 3; // nombre de consommateurs
    queue->nombre_items_pour_test = 50;

    create_join_threads(queue, nom_producteurs, nom_consommateurs);
    
}

void test_5prod_10cons_100items(Queue *queue) {

    int nom_producteurs = 5;   // nombre de producteurs
    int nom_consommateurs = 10; // nombre de consommateurs
    queue->nombre_items_pour_test = 100;

    create_join_threads(queue, nom_producteurs, nom_consommateurs);
}

void test_10prod_5cons_100items(Queue *queue) {

    int nom_producteurs = 10;   // nombre de producteurs
    int nom_consommateurs = 5; // nombre de consommateurs
    queue->nombre_items_pour_test = 100;

    create_join_threads(queue, nom_producteurs, nom_consommateurs);
}

void test_20prod_20cons_500items(Queue *queue) {

    int nom_producteurs = 20;   // nombre de producteurs
    int nom_consommateurs = 20; // nombre de consommateurs
    queue->nombre_items_pour_test = 500;

    create_join_threads(queue, nom_producteurs, nom_consommateurs);
}