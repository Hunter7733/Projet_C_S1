#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>

#include "fonctions.h"
#include "affichage.h"
#include "test.h"

///////////////////
// Fonction main //
///////////////////
int main(){

    srand(time(NULL));

	 //Remarque : il ne faut pas mettre de retour à la ligne dans color_printf
	color_printf(GREEN, MAGENTA, "Début du programme"); printf("\n");

	//Décommenter chaque fonction lorsque la fonction à tester a été codée

	//test_creer_grille();
	//test_est_indice_valide();
	//test_est_cellule();
	//test_get_val_cellule();
	//test_set_val_cellule();
	//test_est_cellule_initiale();
	//test_est_cellule_vide();
	//test_afficher_grille();

  //test_partie_2

  //test_rendre_cellule_initiale();
  //test_est_grille_pleine();
  //test_pas_un_zero_consecutifs();
  //test_meme_nombre_zero_un();
  //test_est_partie_gagnee();
  //test_ligne_colonnes_distincts();
  //test_initialise_grille();

  //test_partie_3

  test_est_mouvement_valide();

  /////////////////////////////////////////
  // Partie permettant de jouer au Takuzu//
  /////////////////////////////////////////

  char s[]= "Grilles/G0/grille0.txt";
  choisir_grille(s);
  jouer(s);
  printf("Vous avez reussi a finir la grille!!\n" );







	color_printf(YELLOW, CYAN, "Fin du programme"); printf("\n");
	return 0;
}
