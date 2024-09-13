#include "../generateur_nombres_aleatoires.h"
#include <gtest/gtest.h>
#include <stdio.h>

TEST(Generateur_nombres_rand, first_test) {

    // Prepare arguments
    struct GenerateurNombresAleatoires_args args;
    GenerateurNombresAleatoires_args_init(&args);

    // Create and initialize the generator
    GenerateurNombresAleatoires *myGen = GenerateurNombresAleatoires_create(&args);

    // Generate and print some random numbers
    printf("Random numbers generated:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\n", GenerateurNombresAleatoires_pige(myGen));
    }
}