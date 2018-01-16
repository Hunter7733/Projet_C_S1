//////////////////////////////////////////////////////////////
// Code permettant d'utiliser les couleurs dans le terminal //
//////////////////////////////////////////////////////////////
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "fonctions.h"

// Couleurs possibles
typedef enum
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
  } COULEUR_TERMINAL;

void clear_terminal();
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...);
void afficher_coordonnees(int n);
void case_couleur(COULEUR_TERMINAL couleur);
void ligne_couleur(COULEUR_TERMINAL c1, COULEUR_TERMINAL c2, int n);
void ligne_cellule_couleur(grille *g, int i, int j, COULEUR_TERMINAL couleur);
void afficher_grille(grille *g);

#endif
