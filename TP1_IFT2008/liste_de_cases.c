#include "liste_de_cases.h"
#include <stdio.h>
#include <stdlib.h>

// Helper functions

static bool noeudMauvaiseCouleur(Noeud *noeud, Couleur couleur)
{
    return (noeud != NULL && noeud->m_case.couleur != couleur);
}

static Noeud *noeudSuivant(const Iterateur *iter, Couleur couleur,
                           int *distance)
{

    distance = 0;
    if (iter->m_courant == NULL)
    {
        return NULL;
    }

    Noeud *suivant = iter->m_courant->m_suivant;
    while (noeudMauvaiseCouleur(suivant, couleur))
    {
        suivant = suivant->m_suivant;
        distance++;
    }
    return suivant;
}

static Noeud *noeudPrecedent(const Iterateur *iter, Couleur couleur,
                             int *distance)
{
    distance = 0;
    if (iter->m_courant == NULL)
    {
        return NULL;
    }

    Noeud *precedent = iter->m_courant->m_precedent;
    while (noeudMauvaiseCouleur(precedent, couleur))
    {
        precedent = precedent->m_precedent;
        distance++;
    }
    return precedent;
}

static int noeudPosition(const Iterateur *iter)
{
    Noeud *courant = iter->m_liste->m_debut;
    int position = 1;
    while (courant != NULL && courant != iter->m_courant)
    {
        courant = courant->m_suivant;
        position++;
    }
    return position;
}

static Noeud *noeudAt(const ListeDeCases *liste, int position)
{
    if (position < 1 || position > ListeDeCases_taille(liste))
    {
        fprintf(stderr, "noeudAt: la position est hors borne\n");
        return NULL;
    }

    Noeud *noeud = liste->m_debut;
    for (int p = 1; p < position; ++p)
    {
        noeud = noeud->m_suivant;
    }
    return noeud;
}

// ListeDeCases Functions

ListeDeCases *ListeDeCases_create()
{
    ListeDeCases *liste = (ListeDeCases *)malloc(sizeof(ListeDeCases));
    if (liste == NULL)
    {
        perror("Failed to allocate memory for ListeDeCases");
        exit(EXIT_FAILURE);
    }
    liste->m_debut = NULL;
    liste->m_fin = NULL;
    liste->m_taille = 0;
    return liste;
}

void ListeDeCases_destroy(ListeDeCases *liste)
{
    while (!ListeDeCases_estVide(liste))
    {
        ListeDeCases_enleverCase(liste, 1);
    }
    free(liste);
}

int ListeDeCases_taille(const ListeDeCases *liste) { return liste->m_taille; }

bool ListeDeCases_estVide(const ListeDeCases *liste)
{
    return ListeDeCases_taille(liste) == 0;
}

void ListeDeCases_ajouterCase(ListeDeCases *liste, const Case *uneCase,
                              int position)
{
    if (position < 1 || position > ListeDeCases_taille(liste) + 1)
    {
        fprintf(stderr, "ajouterCase: position invalide\n");
        return;
    }

    Noeud *nouveau = (Noeud *)malloc(sizeof(Noeud));
    if (!nouveau)
    {
        perror("Failed to allocate memory for Noeud");
        exit(EXIT_FAILURE);
    }
    nouveau->m_case = *uneCase;
    nouveau->m_suivant = NULL;
    nouveau->m_precedent = NULL;

    if (position == 1)
    {
        nouveau->m_suivant = liste->m_debut;
        if (liste->m_debut != NULL)
        {
            liste->m_debut->m_precedent = nouveau;
        }
        liste->m_debut = nouveau;
        if (liste->m_fin == NULL)
        {
            liste->m_fin = nouveau;
        }
    }
    else if (position == ListeDeCases_taille(liste) + 1)
    {
        nouveau->m_precedent = liste->m_fin;
        if (liste->m_fin != NULL)
        {
            liste->m_fin->m_suivant = nouveau;
        }
        liste->m_fin = nouveau;
        if (liste->m_debut == NULL)
        {
            liste->m_debut = nouveau;
        }
    }
    else
    {
        Noeud *courant = noeudAt(liste, position);
        nouveau->m_suivant = courant;
        nouveau->m_precedent = courant->m_precedent;
        if (courant->m_precedent != NULL)
        {
            courant->m_precedent->m_suivant = nouveau;
        }
        courant->m_precedent = nouveau;
    }
    liste->m_taille++;
}

void ListeDeCases_ajouterCaseALaFin(ListeDeCases *liste, const Case *uneCase)
{
    ListeDeCases_ajouterCase(liste, uneCase, ListeDeCases_taille(liste) + 1);
}

void ListeDeCases_enleverCase(ListeDeCases *liste, int position)
{
    if (ListeDeCases_estVide(liste))
    {
        fprintf(stderr, "enleverCase: ListeDeCases est vide\n");
        return;
    }
    if (position < 1 || position > ListeDeCases_taille(liste))
    {
        fprintf(stderr, "enleverCase: la position est hors borne\n");
        return;
    }
    Noeud *courant = noeudAt(liste, position);

    if (courant == liste->m_debut)
    {
        liste->m_debut = courant->m_suivant;
        if (liste->m_debut != NULL)
        {
            liste->m_debut->m_precedent = NULL;
        }
    }
    else
    {
        courant->m_precedent->m_suivant = courant->m_suivant;
    }

    if (courant == liste->m_fin)
    {
        liste->m_fin = courant->m_precedent;
        if (liste->m_fin != NULL)
        {
            liste->m_fin->m_suivant = NULL;
        }
    }
    else
    {
        courant->m_suivant->m_precedent = courant->m_precedent;
    }
    free(courant);
    liste->m_taille--;
}

const Case *ListeDeCases_caseA(const ListeDeCases *liste, int position)
{
    Noeud *noeud = noeudAt(liste, position);
    return &noeud->m_case;
}

// Iterateur Functions

Iterateur *Iterateur_create(const ListeDeCases *liste)
{
    Iterateur *iter = (Iterateur *)malloc(sizeof(Iterateur));
    if (iter == NULL)
    {
        perror("Failed to allocate memory for Iterateur");
        exit(EXIT_FAILURE);
    }
    iter->m_liste = liste;
    iter->m_courant = liste->m_debut;
    return iter;
}

void Iterateur_destroy(Iterateur *iter) { free(iter); }

const Case *Iterateur_caseCourante(const Iterateur *iter)
{
    return &iter->m_courant->m_case;
}

bool Iterateur_existeCaseSuivante(const Iterateur *iter)
{
    return (iter->m_courant != NULL && iter->m_courant->m_suivant != NULL);
}

void Iterateur_caseSuivante(Iterateur *iter, Couleur couleur)
{
    int distance = 0;
    iter->m_courant = noeudSuivant(iter, couleur, &distance);
    if (iter->m_courant == NULL)
    {
        fprintf(
            stderr,
            "L'iterateur ne peut pas aller à une case suivante de couleur %d.\n",
            couleur);
    }
}

bool Iterateur_existeCaseSuivanteCouleur(const Iterateur *iter,
                                         Couleur couleur)
{
    int distance = 0;
    return noeudSuivant(iter, couleur, &distance) != NULL;
}

void Iterateur_casePrecedente(Iterateur *iter, Couleur couleur)
{
    int distance = 0;
    iter->m_courant = noeudPrecedent(iter, couleur, &distance);
    if (iter->m_courant == NULL)
    {
        fprintf(
            stderr,
            "L'iterateur ne peut pas aller à une case précédente de couleur %d.\n",
            couleur);
    }
}

bool Iterateur_existeCasePrecedenteCouleur(const Iterateur *iter,
                                           Couleur couleur)
{
    int distance = 0;
    return noeudPrecedent(iter, couleur, &distance) != NULL;
}

int Iterateur_positionCourante(const Iterateur *iter)
{
    return noeudPosition(iter);
}

bool Iterateur_estADerniereCase(const Iterateur *iter)
{
    return iter->m_courant == iter->m_liste->m_fin;
}

bool Iterateur_avancer(Iterateur *iter)
{
    if (iter->m_courant != NULL)
    {
        iter->m_courant = iter->m_courant->m_suivant;
        return true;
    }
    return false;
}

FILE *ListeDeCases_print(FILE *stream, const ListeDeCases *liste)
{
    if (ListeDeCases_estVide(liste))
    {
        fprintf(stream, "Liste de cases vide\n");
    }
    else
    {
        Noeud *courant = liste->m_debut;
        while (courant != liste->m_fin)
        {
            case_print(stream, courant->m_case);
            fprintf(stream, "; ");
            courant = courant->m_suivant;
        }
        case_print(stream, liste->m_fin->m_case);
    }
    puts("");

    return stream;
}