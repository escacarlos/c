

// typedef struct Person {
//     int ID;
//     int age;
//     const char *name;
// } Person;

// #define TYPE Person
// #include "file.h"

// void initializeFile_person(File_NAME *file) {
//     Person first = {1, 42, "Carlos"};
//     Person second = {2, 39, "Karely"};
//     Person third = {3, 2, "Alissa"};
//     Person fourth = {4, 2, "Gael"};

//     File_NAME_enfiler(file, &first);
//     File_NAME_enfiler(file, &third);
//     File_NAME_enfiler(file, &second);
//     File_NAME_enfiler(file, &fourth);
// }

#include <stdio.h>
#include <gtest/gtest.h>
#include "../file_joueur.h"

TEST(File_Joueur, general_test) {
    
    // Case case1;
    // case_init(&case1, ROUGE, SERPENT);
    // Case case2;
    // case_init(&case2, VERT, ECHELLE);
    // Case case3;
    // case_init(&case3, BLEU, AUCUNE);
    // puts("Cases created");
    // ListeDeCases *myList0 = ListeDeCases_create();

    // ListeDeCases_ajouterCaseALaFin(myList0, &case1);
    // ListeDeCases_ajouterCaseALaFin(myList0, &case2);
    // ListeDeCases_ajouterCaseALaFin(myList0, &case3);
    
    // ListeDeCases *myList1 = ListeDeCases_create();

    // ListeDeCases_ajouterCaseALaFin(myList1, &case1);
    // ListeDeCases_ajouterCaseALaFin(myList1, &case2);
    // ListeDeCases_ajouterCaseALaFin(myList1, &case3);
    
    // ListeDeCases *myList2 = ListeDeCases_create();

    // ListeDeCases_ajouterCaseALaFin(myList2, &case1);
    // ListeDeCases_ajouterCaseALaFin(myList2, &case2);
    // ListeDeCases_ajouterCaseALaFin(myList2, &case3);
    
    // ListeDeCases *myList3 = ListeDeCases_create();

    // ListeDeCases_ajouterCaseALaFin(myList3, &case1);
    // ListeDeCases_ajouterCaseALaFin(myList3, &case2);
    // ListeDeCases_ajouterCaseALaFin(myList3, &case3);
    // puts("Listes created");
    // Iterateur *it0 = Iterateur_create(myList0);
    // Iterateur *it1 = Iterateur_create(myList1);
    // Iterateur *it2 = Iterateur_create(myList2);
    // Iterateur *it3 = Iterateur_create(myList3);
    // puts("Iterators created");
    // Joueur *first = Joueur_create(it0, "Carlos");
    // if (first == NULL) {
    //     perror("Joueur created is fucked!");
    // }
    // Joueur *second = Joueur_create(it1, "Karely");
    // Joueur *third = Joueur_create(it2, "Alissa");
    // Joueur *fourth = Joueur_create(it3, "Gael");
    // puts("Joueurs created");
    // File_Joueur *myFile = File_Joueur_create();
    // puts("File created");
    // File_Joueur_enfiler(myFile, first);
    // puts("first in");
    // File_Joueur_enfiler(myFile, third);
    // File_Joueur_enfiler(myFile, second);
    // File_Joueur_enfiler(myFile, fourth);
    // printf("%d\n", File_Joueur_taille(myFile));
    // printf("%d\n", Iterateur_positionCourante(&first->position));
    // printf("%d\n", Iterateur_positionCourante(&third->position));
    // printf("%d\n", Iterateur_positionCourante(&second->position));
    // printf("%d\n", Iterateur_positionCourante(&fourth->position));
    // Joueur_print(stdout, second);
    // Joueur *five = Joueur_create(it0, "");
    // Joueur_print(stdout, five);
    // puts("fine here");
    // *five = File_Joueur_defiler(myFile);
    // Joueur *six = Joueur_create(it1, "");
    // *six = File_Joueur_defiler(myFile);
    // Joueur_print(stdout, six);
    // puts("fine here");
    // printf("Initial File:\n");
    // printf("%d\n", Iterateur_positionCourante(&five->position));
    // printf("%d\n", Iterateur_positionCourante(&six->position));
    // Joueur_print(stdout, five);
    // Joueur_print(stdout, six);
    // File_Joueur_print(stdout, myFile);
}
