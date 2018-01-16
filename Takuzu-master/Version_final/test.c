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

////////////////////////
// Test de la partie 2//
////////////////////////

void test_rendre_cellule_initiale()
{
  grille *g = creer_grille(4);

  rendre_cellule_initiale(g,0,1);
  rendre_cellule_initiale(g,3,3);

  assert(est_cellule_initiale(g,0,1));
  assert(est_cellule_initiale(g,3,3));
  assert(!est_cellule_initiale(g,1,3));

  printf("Test rendre_cellule_initiale passée\n");
}

void test_initialise_grille()
{
  char fichier[]= "projet_fichier_donner/Grilles/G4/grille1.txt";
  grille *g = initialiser_grille(fichier);
  afficher_grille(g);
  printf("L'affichage doit correspondre au contenu du fichier G4/grilles1.txt");
}

void test_est_grille_pleine()
{
  int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};

  grille *g = creer_grille(4);
  assert(!est_grille_pleine(g));
  int i,j;
  for(i=0; i<g->n; i++)
  {
    for(j=0; j<g->n; j++)
    {
      set_val_cellule(g,i,j,val_cellule[calcul_indice(g,i,j)]);
    }
  }
  assert(est_grille_pleine(g));
  printf("Test est_grille_pleine passee\n");
}

void test_pas_un_zero_consecutifs()
{
  int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
  int val_cellule_faux[16] = {0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0};

  grille *faux= creer_grille(4);
  grille *vrai= creer_grille(4);

  int i,j;
  for(i=0; i<vrai->n; i++)
  {
    for(j=0; j<vrai->n; j++)
    {
      set_val_cellule(vrai,i,j,val_cellule[calcul_indice(vrai,i,j)]);
      set_val_cellule(faux,i,j,val_cellule_faux[calcul_indice(faux,i,j)]);

    }
  }
  assert(pas_zero_un_consecutifs(vrai));
  assert(!pas_zero_un_consecutifs(faux));

  printf("Test pas_zero_un_consecutifs passée\n");
}

void test_meme_nombre_zero_un()
{
  int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
  int val_cellule_faux[16] = {0,1,1,0,1,0,0,1,0,0,1,0/*faute ici*/,1,1,0,0};

  grille *faux= creer_grille(4);
  grille *vrai= creer_grille(4);

  int i,j;
  for(i=0; i<vrai->n; i++)
  {
    for(j=0; j<vrai->n; j++)
    {
      set_val_cellule(vrai,i,j,val_cellule[calcul_indice(vrai,i,j)]);
      set_val_cellule(faux,i,j,val_cellule_faux[calcul_indice(faux,i,j)]);

    }
  }
  assert(meme_nombre_zero_un(vrai));
  assert(!meme_nombre_zero_un(faux));

  printf("Test meme_nombre_zero_un passée\n");
}

void test_ligne_colonnes_distincts()
{
  int val_cellule[16] =      {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
  int val_cellule_faux[16] = {1,0,0,1,1,0,0,1,0,0,1,1,1,1,0,0};

  grille *vrai=creer_grille(4);
  grille *faux=creer_grille(4);
  int i,j;
  for(i=0; i<vrai->n; i++)
  {
    for(j=0; j<vrai->n; j++)
    {
      set_val_cellule(vrai,i,j,val_cellule[calcul_indice(vrai,i,j)]);
      set_val_cellule(faux,i,j,val_cellule_faux[calcul_indice(faux,i,j)]);

    }
  }

  assert(lignes_colonnes_distinctes(vrai));
  assert(!lignes_colonnes_distinctes(faux));

  printf("Test lignes_colonnes_distinctes passée\n");
}

void test_est_partie_gagnee()
{
  int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};

  grille *g = creer_grille(4);
  int i,j;
  for(i=0; i<g->n; i++)
  {
    for(j=0; j<g->n; j++)
    {
      set_val_cellule(g,i,j,val_cellule[calcul_indice(g,i,j)]);
      if(initial_cellule[calcul_indice(g,i,j)])
      {
        rendre_cellule_initiale(g,i,j);
      }
    }
  }
  assert(est_partie_gagnee(g));
  printf("Test est_partie_gagnee passee\n");
}
