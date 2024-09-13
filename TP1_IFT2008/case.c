#include "case.h"

// Initialize a case with the given color and decoration.
void case_init(Case *uneCase, Couleur couleur, Decoration decoration) {
    uneCase->couleur = couleur;
    uneCase->decoration = decoration;
}

// Destroy a case (not needed in this simple case, but added for symmetry).
// void case_destroy(Case *uneCase) {
//     // If there's dynamic allocation, it would be handled here.
// }

// Convert the decoration to a string representation.
const char *decorationEnLettre(Decoration decoration) {
    switch (decoration) {
        case SERPENT:
            return "S";
        case ECHELLE:
            return "E";
        default:
            return "A";
    }
}

// Convert the color to a string representation.
const char *couleurEnLettre(Couleur couleur) {
    switch (couleur) {
        case ROUGE:
            return "R";
        case VERT:
            return "V";
        case BLEU:
            return "B";
        default:
            return "J";
    }
}

// Print a case to the console.
FILE *case_print(FILE *stream, const Case uneCase) {
    fprintf(stream, "(%u,%s)", uneCase.couleur, decorationEnLettre(uneCase.decoration));
    return stream;
}
