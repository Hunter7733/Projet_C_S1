#ifndef FONCTIONS_H
#define	FONCTIONS_H

typedef struct{
	int val;
	int initial;
}cellule;

typedef struct{
	cellule *tab;
	int n;
}grille;

grille * creer_grille(int n);
void detruire_grille(grille * g);
int calcul_indice(grille *g, int i, int j);
int est_indice_valide(grille * g, int indice);
int est_cellule(grille * g, int i, int j);
int get_val_cellule(grille * g, int i, int j);
void set_val_cellule(grille * g, int i, int j, int val);
int est_cellule_initiale(grille * g, int i, int j);
int est_cellule_vide(grille * g, int i, int j);
void rendre_cellule_initiale(grille *g, int i, int j);
grille * initialiser_grille( char nom_fichier[]);
int est_grille_pleine(grille *g);
int pas_zero_un_consecutifs(grille * g);
int meme_nombre_zero_un(grille *g);
int lignes_colonnes_distinctes(grille *g);
int est_partie_gagnee(grille *g);
int est_mouvement_valide(grille *g,char mouv[], int *ligne, int *colonne, int *val);
void tour_de_jeu(grille *g);
void jouer(char ch[]);
void choisir_grille(char s[]);

#endif
