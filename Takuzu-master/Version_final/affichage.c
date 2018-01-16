#include <stdio.h>
#include "affichage.h"
#include "fonctions.h"

////////////////////////////////
// Fonctions affichage couleur//
////////////////////////////////

void clear_terminal()
{
  printf("\033[2J");
  printf("\033[0;0H");
}
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...)
{
  int res;
  va_list args;
  printf("\x1B[1;%02d;%02dm", fg + 30, bg + 40);
  va_start(args, format);
  res = vprintf(format, args);
  va_end(args);
  printf("\x1B[00m");
  return res;
}

/**
 * Fonction qui affiche la premiere ligne de coordonnees
 * @param n: nombre de colonnes
 */
void afficher_coordonnees(int n)
{
	int i;
	printf("   ");
	for(i=0;i<n;i++)
	{
		printf("   %c   ",'A'+i);
	}
	printf("\n");
}

/**
 * Fonction qui trace une ligne d'une case avec la couleur donnee
 * @param couleur: La couleur de la case
 */
void case_couleur(COULEUR_TERMINAL couleur)
{
	int i;
	for(i=0;i<5;i++)
	{
		color_printf(WHITE,couleur," ");
	}
	color_printf(WHITE,couleur," ");
	color_printf(WHITE,couleur," ");
}

/**
 * Fonction qui trace une ligne en couleur de la grille
 * @param c1: couleur des cases impairs
 * @param c2: couleur des cases pairs
 * @param n: nombre des colonnes
 */

void ligne_couleur(COULEUR_TERMINAL c1, COULEUR_TERMINAL c2, int n)
{
	int i;
	printf("   ");
	for (i = 0; i < n/2; i++)
	{
		case_couleur(c1);
		case_couleur(c2);
	}
}

/**
 * Fonction qui trace la case avec une valeur
 * @param g: grille
 * @param i: coordonnees, la ligne
 * @param j: coordonnees, la colonne
 * @param couleur: couleur de la case
 */
void ligne_cellule_couleur(grille *g, int i, int j, COULEUR_TERMINAL couleur)
{
	if(est_cellule_vide(g,i,j))
	{
		color_printf(WHITE,couleur,"       ");
	}
	else if(est_cellule_initiale(g,i,j))
	{
		color_printf(YELLOW,couleur,"   %d   ", get_val_cellule(g,i,j));
	}
	else
	{
		color_printf(WHITE,couleur,"   %d   ", get_val_cellule(g,i,j));
	}
}

/**
 * Fonction affichant la grille sur le terminal.
 * @param g : pointeur sur la grille que l'on souhaite afficher
 */
void afficher_grille(grille *g)
{
	clear_terminal();
	afficher_coordonnees(g->n);

	int i,j;
	COULEUR_TERMINAL couleur1, couleur2;

	for (i = 0; i < g->n; i++)
	{
		if (i %2 == 0)
		{
			couleur1= CYAN;
			couleur2= MAGENTA;
		}
		else
		{
			couleur1= MAGENTA;
			couleur2= CYAN;
		}
		ligne_couleur(couleur1, couleur2,g->n);
		printf("\n");
		printf(" %c ",'A'+i );
		if(g->n == 6 || g->n == 8)
		for (j = 0; j <= (g->n/2)+2; j+=2)
		{
			ligne_cellule_couleur(g,i,j,couleur1);
			ligne_cellule_couleur(g,i,j+1,couleur2);
		}
		else
		for (j = 0; j <= (g->n/2); j+=2)
		{
			ligne_cellule_couleur(g,i,j,couleur1);
			ligne_cellule_couleur(g,i,j+1,couleur2);
		}
		printf("\n");
		ligne_couleur(couleur1, couleur2,g->n);
		printf("\n");

	}
	printf("\n");

}
