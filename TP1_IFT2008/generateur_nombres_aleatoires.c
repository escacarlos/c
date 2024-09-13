#include "generateur_nombres_aleatoires.h"

#include <stdlib.h>

GenerateurNombresAleatoires *GenerateurNombresAleatoires_create(struct GenerateurNombresAleatoires_args *fargs) {
    GenerateurNombresAleatoires *myGen = (GenerateurNombresAleatoires *)malloc(sizeof(GenerateurNombresAleatoires));
    myGen->m_etat = fargs->init;
    myGen->m_maxPlusUn = fargs->max + 1;
    return myGen;
}

int GenerateurNombresAleatoires_pige(GenerateurNombresAleatoires *myGen) {
    myGen->m_etat *= ENTROPIE;
    return myGen->m_etat % myGen->m_maxPlusUn;
}

void GenerateurNombresAleatoires_args_init(struct GenerateurNombresAleatoires_args *args) {
    args->init = 1;
    args->max = 2000000000;
}

void GenerateurNombresAleatoires_destroy(GenerateurNombresAleatoires *myGen) {
    free(myGen);
}
