#include "liste_de_cases.h"
#include <stdio.h>

// Function to initialize a ListeDeCases with some sample cases
void initializeList(ListeDeCases *list) {
  Case case1 = {ROUGE, SERPENT};
  Case case2 = {VERT, ECHELLE};
  Case case3 = {BLEU, AUCUNE};

  ListeDeCases_ajouterCaseALaFin(list, &case1);
  ListeDeCases_ajouterCaseALaFin(list, &case2);
  ListeDeCases_ajouterCaseALaFin(list, &case3);
}

int main() {
  ListeDeCases *myList = ListeDeCases_create();

  initializeList(myList); // Add some cases to the list

  printf("Initial List:\n");
  ListeDeCases_print(stdout, myList);

  // Add a case at position 2
  Case case4 = {JAUNE, SERPENT};
  ListeDeCases_ajouterCase(myList, &case4, 2);

  printf("\nAfter adding a case at position 2:\n");
  ListeDeCases_print(stdout, myList);

  // Remove the case at position 1
  ListeDeCases_enleverCase(myList, 1);

  printf("\nAfter removing the case at position 1:\n");
  ListeDeCases_print(stdout, myList);

  // Using the iterator
  Iterateur *iter = Iterateur_create(myList);
  printf("\nUsing Iterator:\n");
  do {
    case_print(stdout, Iterateur_caseCourante(iter));
    printf("; ");
  } while (Iterateur_existeCaseSuivante(iter) && Iterateur_avancer(iter));

  // Cleanup
  ListeDeCases_destroy(myList);

  return 0;
}