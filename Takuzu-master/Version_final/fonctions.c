#include "fonctions.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
//Partie 1

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


//Partie 2

/**
* Fonction modifiant une cellule pour la rendre initiale.
* @param g : pointeur sur la grille
* @param i : indice de ligne
* @param j : indice de colonne
*/
void rendre_cellule_initiale(grille *g, int i, int j)
{
  assert( !est_cellule_initiale(g,i,j) && est_cellule(g,i,j));
  g->tab[calcul_indice(g,i,j)].initial = 1;
}

/**
* Fonction retournant une grille avec les informations contenues
* dans le fichier passé en paramètre.
* @param nom_fichier : fichier contenant l'instance du problème
* @return: pointeur sur la grille crée
*/
grille * initialiser_grille( char nom_fichier[])
{
  FILE * f= fopen(nom_fichier,"rt");
  if(f == NULL)
  {
    exit(1);
  }
  int taille, nb_initiale, i, j, val;
  fscanf(f,"%d",&taille);
  fscanf(f,"%d",&nb_initiale);
  grille *a = creer_grille(taille);
  for(nb_initiale; nb_initiale > 0; nb_initiale--) {
    fscanf(f,"%d",&i);
    fscanf(f,"%d",&j);
    fscanf(f,"%d",&val);
    set_val_cellule(a,i,j,val);
    rendre_cellule_initiale(a,i,j);
  }
  fclose(f);
  return a;
}

/**
* Fonction testant si la grille est entièrement remplie.
* @param g : grille à tester
* @return : 1 si la grille est pleine, 0 sinon
*/
int est_grille_pleine(grille *g)
{
  int i,j;
  for(i=0; i<g->n; i++)
  {
    for(j=0; j<g->n; j++)
    {
      if(est_cellule_vide(g,i,j))
      {
        return 0;
      }
    }
  }
  return 1;
}

/**
* Fonction vérifiant qu'il n'existe pas 3 zéro ou 3 un consécutifs dans
* la grille (ligne ou colonne).
* @param g : grille à tester
* @return : 1 si c'est le cas, 0 sinon
*/
int pas_zero_un_consecutifs(grille * g)
{
  int i,j;
  for(i=0;i<(g->n);i++)
  {
    for(j=0;j<(g->n)-2;j++)
    {
      if(get_val_cellule(g,i,j) == get_val_cellule(g,i,j+1) && get_val_cellule(g,i,j) == get_val_cellule(g,i,j+2) )
      return 0;
    }
  }

  for(i=0;i<(g->n)-2;i++)
  {
    for(j=0;j<(g->n);j++)
    {
      if(get_val_cellule(g,i,j) == get_val_cellule(g,i+1,j) && get_val_cellule(g,i,j) == get_val_cellule(g,i+2,j) )
      return 0;
    }
  }
  return 1;
}

/**
* Fonction testant si le nombre de zéros est égal au nombre de uns dans
* chaque ligne/colonne.
* @param g : grille à tester
* @return : 1 si c'est le cas, 0 sinon
*/
int meme_nombre_zero_un(grille *g)
{
  int i, j;
  int nb_zero=0, nb_un=0;
  for(i=0; i<g->n; i++){
    for(j=0; j<g->n; j++){
      if(g->tab[calcul_indice(g,i,j)].val == 0){
        nb_zero ++;
      }
      else{
        nb_un ++;
      }
    }
    if (nb_un != nb_zero ) {
      return 0;
    }

    for(j=0; j<g->n; j++){
      if(g->tab[calcul_indice(g,j,i)].val == 0){
        nb_zero ++;
      }
      else{
        nb_un ++;
      }
    }
    if (nb_un != nb_zero ) {
      return 0;
    }
  }
  return 1;
}

/**
* Fonction testant qu'il n'existe pas deux lignes identiques ou deux
* colonnes identiques.
* @param g : grille à tester
* @return: 1 si c'est le cas, 0 sinon
*/
int lignes_colonnes_distinctes(grille *g)
{
  int i,j,k;
  for (k=0; k<g->n; k++){
    for(i=k; i<g->n; i++){
      for(j=0; (j<g->n-1)&&(g->tab[calcul_indice(g,i+1,j)].val == g->tab[calcul_indice(g,i,j)].val ); j++)
      {}
      if(j == g->n-1)
      {
        return 0;
      }
    }

    for(i=k; i<g->n; i++){
      for(j=0; (j<g->n)&&(g->tab[calcul_indice(g,j,i+1)].val == g->tab[calcul_indice(g,i,j)].val ); j++)
      {}
      if(j == g->n-1)
      {
        return 0;
      }
    }
  }
  return 1;
}

/**
* Fonction déterminant si la partie est gagnée.
* @param g : grille à tester
* @return: 1 si la partie est gagnée, 0 sinon
*/
int est_partie_gagnee(grille *g)
{
  if(est_grille_pleine(g)&&pas_zero_un_consecutifs(g)&&meme_nombre_zero_un(g)&&lignes_colonnes_distinctes(g)){
    return 1;
  }
  return 0;
}

//Partie 3


/**
* Fonction déterminant si un mouvement est valide. Si c'est le cas,
* elle met à jour les indices de ligne et colonne et la valeur en
* fonction de la saisie.
* @param  g: pointeur sur la grille
* @param  mouv: chaîne de caractères contenant le mouvement
* @param  ligne: indice de ligne à modifier en fonction de mouv
* @param  colonne: indice de colonne à modifier en fonction de mouv
* @param  val: valeur à modifier en fonction de mouv
* @return: 1 si le mouvement est valide, et 0 sinon
*/

int est_mouvement_valide(grille *g,char mouv[], int *ligne, int *colonne, int *val)
{
  int i,j;
  i= (int)(mouv[0] -'A');
  j= (int)(mouv[1] -'A');

  if( !est_cellule(g,i,j)||est_cellule_initiale(g,i,j))
  {
    return 0;
  }


  if(mouv[2] == '\0' && !est_cellule_vide(g,i,j))
  {
    *val= -1;
  }

  if(mouv[2] != '\0')
  {
    (*val)= mouv[2] -'0';
  }

  *ligne= i;
  *colonne= j;

  return 1;

}

/**
* Fonction effectuant un tour de jeu :
* - saisie jusqu'à ce que l'utilisateur saisisse un mouvement valide,
* - modification de la grille en fonction de la saisie.
* @param  g : pointeur sur la grille
*/
void tour_de_jeu(grille *g)
{
  char mouv[4];
  int i,j,valeur;
  do{
    printf("\nVeuiller saisir un mouvement valide : ");
    scanf("%s", mouv);
  }while(!est_mouvement_valide(g,mouv,&i,&j,&valeur));

  set_val_cellule(g,i,j,valeur);
}

/**
* Fonction permettant de jouer au Takuzu.
* @param ch : Chaîne de caractères contenant le nom du fichier
* correspondant à l'instance du Takuzu
*/
void jouer(char ch[])
{
  grille *g= initialiser_grille(ch);
  while(!est_partie_gagnee(g))
  {
    afficher_grille(g);
    tour_de_jeu(g);
    printf("%d %d %d %d\n",est_grille_pleine(g),pas_zero_un_consecutifs(g),meme_nombre_zero_un(g),lignes_colonnes_distinctes(g)); //a enlever

  }
  afficher_grille(g);
}

/**
* Fonction permettant de choisir aléatoirement une grille dont la taille
* est saisie par l'utilisateur.
* @param s : chaîne de caractères contenant le nom de la grille
* choisie aléatoirement
*/
void choisir_grille(char s[])
{
  int taille;
  do{
    printf("\nChoississez une taille de grille (4,6,8): ");
    scanf("%d",&taille);
  }while(taille != 4 && taille != 6 && taille != 8);
  s[9]= taille +'0';
  s[17]= ((rand()%5)+1) +'0';
  printf("%s\n",s );
}
