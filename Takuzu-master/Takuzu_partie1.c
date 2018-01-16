/////////////////////////////////////////////////////////////////
//                                                             //
// AUTEURS : OUHBAD omar , ESSAHLI Abdelbasset                 //
//                                                             //
// DATE    : 20 decembre 2017                                  //
//                                                             //
// RESUME  : Code source correspondant à la première partie du //
// 		projet tutoré de S1 : coder un Takuzu          //
//                                                             //
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

/* 
	Ce fichier contient pour l'instant les en-têtes des fonctions de la partie 1.
	Vous devez coder les définitions. Les fonctions de test de la partie 1 sont également données.
	Comme ces fonctions utilisent la fonction assert, leurs appels sont commentées dans la fonction principale
	(vous ne pouvez les tester avant de les coder !) 

	ATTENTION : le code ne compile pas avant d'avoir défini les types structurés.
*/


//////////////////////////////////////////////////////////////
// Code permettant d'utiliser les couleurs dans le terminal //
//////////////////////////////////////////////////////////////


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



////////////////////////////////////////////
// DÉFINIR LE TYPE STRUCTURÉ cellule ici  //
////////////////////////////////////////////

typedef struct{
	int val;
	int initial;
}cellule;

//////////////////////////////////////////
// DÉFINIR LE TYPE STRUCTURÉ grille ici //
//////////////////////////////////////////

typedef struct{
	cellule *tab;
	int n;
}grille;



/**
 * Fonction allouant dynamiquement une grille dont l'adresse est retournée.
 * @param n : nombre de lignes/colonnes (4, 6, ou 8)
 * @return  : adresse de la grille, NULL en cas d'erreur
 */
grille * creer_grille(int n)
{
	assert((n==4||n==6||n==8)&& "Le nombre de case n'est pas egale a 4 ou 6 ou 8");
	grille *a= malloc(sizeof(grille));
	if(a == NULL)
	{
		printf("La grille n'as pas pu etre cree");
		return NULL; //Pour éviter les problèmes compilation
	}
	(*a).n = n;
	(*a).tab = malloc((n*n)*sizeof(cellule));
	int i;
	for(i=0;i != n*n;i++)
	{
		(*a).tab[i].val= -1;
		(*a).tab[i].initial=0;
	}
	return a;
}

/**
 * Fonction désallouant dynamiquement la grille passée en paramètre.
 * @param g : grille à désallouer
 */
void detruire_grille(grille * g)
{	
	free(g->tab);
	free(g);
}

/**
 * Fonction ajoutée pour calculée la position de 
 * la cellule dans le tableau a partir de ses coordonnées
 * @param g: grille
 * @param i,j: coordonnees
 */
int calcul_indice(grille *g, int i, int j) 
{
	return ((g->n)*i +j);
}

/**
 * Fonction retournant 1 si l'indice est valide par rapport à la grille.
 * @param g      : grille
 * @param indice : entier
 * @return       : 1 si indice est un indice valide pour g, 0 sinon
 */
int est_indice_valide(grille * g, int indice)
{
	return ( indice < g->n && indice >= 0);
}

/**
 * Fonction retournant 1 si (i,j) est une cellule de la grille.
 * @param g : grille
 * @param i : numéro de ligne
 * @param j : numéro de colonne
 * @return  : 1 si (i,j) correspond à une cellule de g, 0 sinon
 */
int est_cellule(grille * g, int i, int j)
{
	return ( est_indice_valide(g,i) && est_indice_valide(g,j) );
}


/**
 * Fonction retournant la valeur de la cellule (i,j) de la grille g.
 *
 * @param g : grille
 * @param i : numéro de ligne
 * @param j : numéro de colonne
 */
int get_val_cellule(grille * g, int i, int j)
{
	assert( est_cellule(g,i,j) && "\nCe n'est pas une cellule de la grille\n");
	//int indice = calcul_indice(g,i,j);
	return g->tab[(g->n *i )+j].val;
}


/**
 * Fonction modifiant la valeur de la cellule (i,j) de la grille g avec 
 * la valeur passée en paramètre.
 * @param g : grille
 * @param i : indice de ligne
 * @param j : indice de colonne
 * @param valeur : valeur à mettre dans le champ val de la cellule (i,j) 
 */
void set_val_cellule(grille * g, int i, int j, int val)
{
	assert( est_cellule(g,i,j) && (val >= -1 && val <= 1) );
	int indice = calcul_indice(g,i,j);
	g->tab[indice].val = val;
}


/**
 * Fonction retournant 1 si la cellule (i,j) est une cellule initiale, 
 * et 0 sinon.
 * @param g : grille
 * @param i : indice de ligne
 * @param j : indice de colonne 
 */
int est_cellule_initiale(grille * g, int i, int j)
{
	assert( est_cellule(g,i,j) );
	int indice = calcul_indice(g,i,j);
	return g->tab[indice].initial;
}


/**
 * Fonction retournant 1 si la cellule (i,j) de la grille g est vide,
 * et 0 sinon.
 * @param g : grille
 * @param i : indice de ligne
 * @param j : indice de colonne 
 */
int est_cellule_vide(grille * g, int i, int j)
{
	int indice = calcul_indice(g,i,j);
	return (g->tab[indice].val == -1);
}

////////////////////////////////
// Fonctions affichage couleur//
////////////////////////////////


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


///////////////////////////////////////////////////
//  Code correspondant aux tests de la partie 1  //
///////////////////////////////////////////////////
 
/**
 * Fonction testant la fonction creer_grille
 */
void test_creer_grille(){
	int i,k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		assert(g->n == k && "Problème dans le champ n de la grille");

		//Vérification que les cellules sont vides
		for(i = 0 ; i < k * k ; i++){
			assert(g->tab[i].val == -1 && "Problème : cellule non vide !");
			assert(g->tab[i].initial == 0 && "Problème : cellule initiale !");
		}
		detruire_grille(g);
	}
	printf("Test de la fonction creer_grille passé !\n");
}

/**
 * Fonction testant la fonction est_indice_valide
 */
void test_est_indice_valide(){
	int i,k;
	for(k = 4; k <= 8 ; k+=2){

		grille * g = creer_grille(k);
		for(i = 0 ; i < k ; i++)
			assert(est_indice_valide(g,i) == 1 && "Problème indice valide non reconnu !");
		assert(est_indice_valide(g,-1) == 0 && "Problème indice non valide reconnu !");
		assert(est_indice_valide(g,k)  == 0 && "Problème indice non valide reconnu !");
		detruire_grille(g);
	}
	printf("Test de la fonction est_indice_valide passé !\n");
}

/**
 * Fonction testant la fonction est_cellule
 */
void test_est_cellule(){
	int i,j,k;
	for(k = 4; k <= 8 ; k+=2){

		grille * g = creer_grille(k);
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule(g,i,j) == 1 && "Problème indice valide non reconnu !");
		assert(est_cellule(g,-1,1) == 0 && "Problème indice non valide reconnu !");
		assert(est_cellule(g,k,1)  == 0 && "Problème indice non valide reconnu !");
		assert(est_cellule(g,1,-1) == 0 && "Problème indice non valide reconnu !");
		assert(est_cellule(g,1,k)  == 0 && "Problème indice non valide reconnu !");
		detruire_grille(g);
	}
	printf("Test de la fonction est_cellule passé !\n");
}

/**
 * Fonction testant la fonction get_val_cellule
 */
void test_get_val_cellule(){
	grille * g = creer_grille(6);
	g->tab[0].val = 1;
	g->tab[6].val = 1;
	g->tab[15].val = 0;
	assert(get_val_cellule(g,0,0) == 1 && "Problème de valeur");
	assert(get_val_cellule(g,1,0) == 1 && "Problème de valeur");
	assert(get_val_cellule(g,2,3) == 0 && "Problème de valeur");
	assert(get_val_cellule(g,1,4) == -1 && "Problème de valeur");
	detruire_grille(g);
	printf("Test de la fonction get_val_cellule passé !\n");
}


/**
 * Fonction testant la fonction set_val_cellule
 */
void test_set_val_cellule(){
	int k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		set_val_cellule(g,0,0,1);
		assert(get_val_cellule(g,0,0) == 1 && "Problème de valeur");
		set_val_cellule(g,k-1,k-1,0);
		assert(get_val_cellule(g,k-1,k-1) == 0 && "Problème de valeur");
		set_val_cellule(g,0,k-2,1);
		assert(get_val_cellule(g,0,k-2) == 1 && "Problème de valeur");
		set_val_cellule(g,k-2,1,0);
		assert(get_val_cellule(g,k-2,1) == 0 && "Problème de valeur");
		set_val_cellule(g,k-1,k-1,-1);
		assert(get_val_cellule(g,k-1,k-1) == -1 && "Problème de valeur");
		detruire_grille(g);
	}
	printf("Test de la fonction set_val_cellule passé !\n");
}

/**
 * Fonction testant la fonction est_cellule_initiale
 */
void test_est_cellule_initiale(){
	int i,j,k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].initial = 0;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_initiale(g,i,j) == 0 && "Problème valeur initiale au début");
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].initial = 1;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_initiale(g,i,j) == 1 && "Problème valeur initiale au début");
		detruire_grille(g);
	}	
	printf("Test de la fonction est_cellule_initiale passé !\n");
}

/**
 * Fonction testant la fonction est_cellule_vide
 */
void test_est_cellule_vide(){
	int i,j,k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].val = -1;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_vide(g,i,j) == 1 && "Problème valeur initiale au début");
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].val = 0;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_vide(g,i,j) == 0 && "Problème valeur initiale au début");
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].val = 1;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_vide(g,i,j) == 0 && "Problème valeur initiale au début");
		detruire_grille(g);
	}	
	printf("Test de la fonction est_cellule_vide passé !\n");
}

/**
 * Fonction testant la fonctino afficher_grille
 */
void test_afficher_grille(){
	grille * g = creer_grille(8);
	int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
	int i;
	for(i = 0 ; i < 16 ; i++){
		g->tab[i].val = val_cellule[i];
		g->tab[i].initial = initial_cellule[i];
	}
	afficher_grille(g);
	printf("L'affichage doit être celui de la grille solution dans le pdf\n");
}

/**
 * Fonction testant la fonction calcul_indice
 */
void test_calcul_indice()
{
}

int main(){
	 //Remarque : il ne faut pas mettre de retour à la ligne dans color_printf
	color_printf(GREEN, MAGENTA, "Début du programme"); printf("\n");

	//Décommenter chaque fonction lorsque la fonction à tester a été codée

	test_creer_grille();
	test_est_indice_valide();
	test_est_cellule();
	test_get_val_cellule();
	test_set_val_cellule();
	test_est_cellule_initiale();
	test_est_cellule_vide();
	test_afficher_grille();

	

	color_printf(YELLOW, CYAN, "Fin du programme"); printf("\n");
	return 0;
}

