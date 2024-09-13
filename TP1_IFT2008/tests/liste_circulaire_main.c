#include <stdio.h>

#include "liste_circulaire_couleur.h"

// #define TYPE int
// #include "liste_circulaire.h"

// void initializeList_int(ListeCirculaire_NAME *list) {
//     int first = 1;
//     int second = 2;
//     int third = 3;
//     int fourth = 4;

//     printf("empty? %d\n", ListeCirculaire_NAME_estVide(list));
//     ListeCirculaire_NAME_ajouterFin(list, &first);
//     printf("taille: %d\n", ListeCirculaire_NAME_taille(list));
//     ListeCirculaire_NAME_ajouterFin(list, &second);
//     printf("taille:%d\n", ListeCirculaire_NAME_taille(list));
//     ListeCirculaire_NAME_ajouterFin(list, &third);
//     printf("taille:%d\n", ListeCirculaire_NAME_taille(list));
//     printf("first: %d, second: %d, third: %d\n", ListeCirculaire_NAME_position(list, &first), 
//     ListeCirculaire_NAME_position(list, &second), ListeCirculaire_NAME_position(list, &third));
//     printf("elem 1: %d, elem 2: %d, elem 3: %d\n", ListeCirculaire_NAME_element(list, 1), 
//     ListeCirculaire_NAME_element(list, 2), ListeCirculaire_NAME_element(list, 3));
//     printf("first is present? %d\n", ListeCirculaire_NAME_appartient(list, &first));
//     printf("fourth is present? %d\n", ListeCirculaire_NAME_appartient(list, &fourth));
// }

// #define TYPE const char *
// #include "liste_circulaire.h"

// void initializeList_string(ListeCirculaire_NAME *list) {
//     const char* first = "Carlos";
//     const char* second = "Alissa";
//     const char* third = "Gael";

//     ListeCirculaire_NAME_ajouter(list, &first, 1);
//     ListeCirculaire_NAME_ajouterFin(list, &third);
//     ListeCirculaire_NAME_ajouter(list, &second, 2);
// }

// typedef struct Person {
//     int ID;
//     int age;
//     const char *name;
// } Person;

// #define TYPE Person
// #include "liste_circulaire.h"

// void initializeList_person(ListeCirculaire_NAME *list) {
//     Person first = {1, 42, "Carlos"};
//     Person second = {2, 39, "Karely"};
//     Person third = {3, 2, "Alissa"};
//     Person fourth = {4, 2, "Gael"};

//     ListeCirculaire_NAME_ajouter(list, &first, 1);
//     ListeCirculaire_NAME_ajouterFin(list, &third);
//     ListeCirculaire_NAME_ajouter(list, &second, 2);
//     ListeCirculaire_NAME_ajouterFin(list, &fourth);
// }

void initializeList_Couleur(ListeCirculaire_Couleur *list) {
    Couleur first = ROUGE;
    Couleur second = VERT;
    Couleur third = JAUNE;

    ListeCirculaire_Couleur_ajouter(list, &first, 1);
    ListeCirculaire_Couleur_ajouterFin(list, &third);
    ListeCirculaire_Couleur_ajouter(list, &second, 2);
}
int main() {

    ListeCirculaire_Couleur *myList = ListeCirculaire_Couleur_create();

    initializeList_Couleur(myList);

    printf("Initial List:\n");
    ListeCirculaire_Couleur_print(stdout, myList);

    printf("Creating Copy List:\n");
    ListeCirculaire_Couleur *myList0 = ListeCirculaire_Couleur_create();
    myList0 = ListeCirculaire_Couleur_copy(myList0, myList);
    
    printf("Second List:\n");
    ListeCirculaire_Couleur_print(stdout, myList0);

    // ListeCirculaire_NAME *myList1 = ListeCirculaire_NAME_create();

    // initializeList_string(myList1);

    // printf("Initial List:\n");
    // ListeCirculaire_NAME_print(stdout, myList1);

    // printf("Creating Copy List:\n");
    // ListeCirculaire_NAME *myList2 = ListeCirculaire_NAME_create();
    // myList2 = ListeCirculaire_NAME_copy(myList2, myList1);
    
    // printf("Second List:\n");
    // ListeCirculaire_NAME_print(stdout, myList1);

    // ListeCirculaire_NAME *myList3 = ListeCirculaire_NAME_create();

    // initializeList_person(myList3);

    // printf("Initial List:\n");
    // ListeCirculaire_NAME_print(stdout, myList3);

    // printf("Creating Copy List:\n");
    // ListeCirculaire_NAME *myList4 = ListeCirculaire_NAME_create();
    // myList4 = ListeCirculaire_NAME_copy(myList4, myList3);
    
    // printf("Second List:\n");
    // ListeCirculaire_NAME_print(stdout, myList4);





    return 0;
}