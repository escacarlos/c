#ifndef CASE_H_
#define CASE_H_

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif

// Define the possible colors for a case.
typedef enum { ROUGE, VERT, BLEU, JAUNE } Couleur;

// Number of colors.
#define NOMBRE_COULEURS 4

// Define the possible decorations for a case.
typedef enum { AUCUNE, SERPENT, ECHELLE } Decoration;

// Number of decorations.
#define NOMBRE_DECORATIONS 3

// Define the Case structure.
typedef struct {
    Couleur couleur;
    Decoration decoration;
} Case;

// Function prototypes.
void case_init(Case *uneCase, Couleur couleur, Decoration decoration);

// void case_destroy(Case *uneCase);

const char *decorationEnLettre(Decoration decoration);

const char *couleurEnLettre(Couleur couleur);

FILE *case_print(FILE *stream, const Case uneCase);

#if __cplusplus
}
#endif

#endif /* CASE_H_ */
