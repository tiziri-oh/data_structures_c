#include<stdio.h>
#include<stdlib.h>
#include "binary_binomial_heap.h"
#include<stdbool.h>
#include<limits.h>

int tas_fils_gauche_noeud(tas* t, int i){
	int k = 2*i + 1;
	return k;
}

int tas_fils_droite_noeud(tas* t, int i){
	int k = 2*i + 2;
	return k;
}

int tas_parent_noeud(tas* t, int i){
	int k = i/2;
	return k;
}
/*
*  Allocation memoire d'un nouveau Tas
*/
tas* tas_creer(int capacity, char is_fixed_size)
{
	tas* t;
	t = (tas*)malloc(sizeof(tas));
	t->size = 0;
	t->capacity = capacity;
	t->is_fixed_size = is_fixed_size;
	t->data = (int*)malloc(capacity*sizeof(int));
	int i;
	for (int i = 0; i < capacity; ++i)
	{
		t->data[i] = -1;
	}
	return t;
}

/*
*  Liberer la memoire et supprimer le Tas
*/
void tas_supprimer(tas* t)
{
	if(t != NULL)
	{
		if(t->data != NULL)
		{
			free(t->data);
		}
		free(t);
	}
}

/*
*  Affiche le contenu du tas
*/
void tas_afficher(tas* t)
{
	int i;
	for (int i = 0; i < t->capacity; ++i)
	{
		printf("Element %d : %d\n", i, t->data[i]);
	}
	if(t->size == t->capacity){
		printf("Le tableau est plein\n");
	}
}

/*
*   Ajouter un nouvel element au tas
*/
char tas_ajouter_cle(tas* t, int valeur)
{
	char memory_allocation = FALSE;
	if(t->is_fixed_size == TRUE){
		if(t->size == t->capacity){
			printf("Tas complet\n");
			return memory_allocation;
		}
	}
	else{
		if(t->size == t->capacity){
			memory_allocation = TRUE;
			t->capacity *= 2;
	  		t->data = (int *) realloc(t->data, sizeof(int) * t->capacity);
		}
	}
	t->data[t->size] = valeur;
	tas_verifier_et_swaper_si_besoin_vers_le_haut(t, t->size);
	t->size++;
	return memory_allocation;
}

/**
    Fonction auxiliaire permettant de permuter recusivement le noeud i et son pere si besoin
*/
void tas_verifier_et_swaper_si_besoin_vers_le_haut(tas* t, int i)
{
	if((t->size == 1) || (i <= 0)) 
	{
		return;
	}
	
	int indice_pere = tas_parent_noeud(t, i);

	if(t->data[i] < t->data[indice_pere])
	{
		tas_permuter_noeuds(t, i, indice_pere);
		tas_verifier_et_swaper_si_besoin_vers_le_haut(t, indice_pere);
	}
}

/*
*   Fonction auxiliaire qui permet de permuter deux elements d'un tas aux positions i et j
*/
void tas_permuter_noeuds(tas* t, int i, int j){
	int tmp = t->data[i];
	t->data[i] = t->data[j];
	t->data[j] = tmp;
}


/*
*   Fonction qui supprime la plus petite clé dans le tas
*/
char tas_extraire_min(tas* t){
	char memory_allocation = FALSE;
	int nbrElems = t->size;
	if(nbrElems==0){
		printf("le tableau est vide\n");
		return FALSE;
	}

	if(t->is_fixed_size == FALSE){
		if(nbrElems <= (t->capacity/4) ){
			t->capacity = t->capacity / 2;
			t->data = (int*) realloc(t->data, sizeof(int) * t->capacity);
			memory_allocation = TRUE;
		}
	}

	tas_permuter_noeuds(t, 0, nbrElems - 1);
	t->data[nbrElems - 1] = -1;
	tas_entasser(t, 0);
	t->size--;
	return memory_allocation;
}

/*
*   Fonction auxiliere : Entassement vers le bas d'un élement à la position i dans un tas
*/
void tas_entasser(tas* t, int i){
	int g = tas_fils_gauche_noeud(t, i);
	int d = tas_fils_droite_noeud(t, i);
	int nbrElems = t->size;
	int indiceDuMin = i;

	if(g < nbrElems){ //si l'indice g est valide (existe)
		if((t->data[g] < t->data[i])){ 
			indiceDuMin = g;
		}	
	}
	if(d < nbrElems){ //si l'indice d est valide (existe)
		if (t->data[d] < t->data[indiceDuMin]){
			indiceDuMin = d;
		}
	}
	if (indiceDuMin != i){
		tas_permuter_noeuds(t, i, indiceDuMin);
		tas_entasser(t, indiceDuMin);
	}
}

// question 2

arbre_binomial* arbre_binomial_creer(int cle){
	arbre_binomial* B1 = (arbre_binomial*) malloc(sizeof(arbre_binomial));
	B1->pere = NULL;
	B1->fils = NULL;
	B1->frere = NULL;
	B1->cle = cle;
	B1->degre = 0;
	return B1;
}

void arbre_binomial_afficher(arbre_binomial* b, bool est_racine){
	if(b == NULL)
	{
		return;
	}
	if(b->fils != NULL){
		arbre_binomial_afficher(b->fils, false);
	}
	if(b->frere != NULL){
		if(!est_racine)
			arbre_binomial_afficher(b->frere, false);
	}
	printf("%d , ", b->cle);
}

void afficher_liste_arbre_binomiaux(arbre_binomial* t)
{
	if(t == NULL){
		printf("vide -> ");
		return;
	}
	if(t->frere != NULL){
		afficher_liste_arbre_binomiaux(t->frere);
	}
	printf("arbre { \n");
	printf(" degre   : %d,\n", t->degre);
	printf(" cles    : ");
	arbre_binomial_afficher(t, true);
	printf("\n} \n");
}

void arbre_binomial_supprimer(arbre_binomial* b){
	if(b == NULL)
	{
		return;
	}
	if(b->fils != NULL){
		arbre_binomial_supprimer(b->fils);
	}
	if(b->frere != NULL){
		arbre_binomial_supprimer(b->frere);
	}
	free(b);
}

void supprimer_liste_arbre_binomiaux(arbre_binomial* t)
{
	if(t == NULL)
		return;
	if(t->frere != NULL){
		supprimer_liste_arbre_binomiaux(t->frere);
	}
	arbre_binomial_supprimer(t);
}

tas_binomial* tas_binomial_creer()
{
	tas_binomial* T = (tas_binomial*)malloc(sizeof(tas_binomial));
	T->tete = NULL;
	return T;
}

void tas_binomial_supprimer(tas_binomial* t){
	supprimer_liste_arbre_binomiaux(t->tete);
	free(t);
}

void tas_binomial_afficher(tas_binomial* t)
{
	printf("------------------------------------------\n");
	
	if(t == NULL){
		printf("Pas de Tas binomial: null!\n");
		return;
	}
	if(t->tete == NULL){
		printf("Tas binomial vide!\n");
	}else{
		afficher_liste_arbre_binomiaux(t->tete);
	}

	printf("------------------------------------------\n");
}

tas_binomial* tas_binomial_inserer_cle(tas_binomial* t, int cle){
	struct noeud_tas_binomial* B0 = arbre_binomial_creer(cle);
	t = tas_binomial_inserer(t, B0);
	return t;
}

tas_binomial* tas_binomial_inserer(tas_binomial* t, struct noeud_tas_binomial* x){
	tas_binomial* t1 = tas_binomial_creer();
	x->pere = NULL;
	x->frere = NULL;
	x->fils = NULL;
	x->degre = 0;
	t1->tete = x;
	return tas_binomial_union(t, t1);
}

struct noeud_tas_binomial* tas_binomial_min(tas_binomial* T){
	struct noeud_tas_binomial* y = NULL;
	struct noeud_tas_binomial* x = T->tete;
	int min = INT_MAX;
	while (x != NULL){
		if(x->cle < min){
			min = x->cle;
			y = x;
		}
		x = x->frere;
	}
	return y;
}

void lien_binomial(struct noeud_tas_binomial* y, struct noeud_tas_binomial* z){
	y->pere = z;
	y->frere = z->fils;
	z->fils = y;
	z->degre++;
}

struct noeud_tas_binomial* tas_binomial_fusion(tas_binomial* t1, tas_binomial* t2){
	struct noeud_tas_binomial* tete = NULL;
	struct noeud_tas_binomial* iter1 = t1->tete;
	struct noeud_tas_binomial* iter2 = NULL;
	struct noeud_tas_binomial* avant_iter1 = NULL;
	struct noeud_tas_binomial* avant_iter2 = NULL;
	struct noeud_tas_binomial* tmp ;

	if(t1->tete == NULL){
		if(t2->tete == NULL){
			return NULL;
		}
		return t2->tete;
	}

	while(iter1->frere != NULL){
		iter1 = iter1->frere;
	}
	iter1->frere =  t2->tete;

	iter1 = t1->tete;

	while(iter1 != NULL){
		iter2 = iter1->frere;
		avant_iter2 = iter1;
		while(iter2 != NULL){
			if(iter1->degre > iter2->degre){
				if(avant_iter1 != NULL){
					avant_iter1->frere = iter2;
				}
				avant_iter2->frere = iter1;
				tmp = iter1->frere;
				iter1->frere = iter2->frere;
				iter2->frere = tmp;
				tmp = iter1;
				iter1 = iter2;
				iter2 = tmp;
			}
			//incermenter l'iterateur 2
			avant_iter2 = iter2;
			iter2 = iter2->frere;
		}
		//mise a jour de la tete a la premiere iteration
		if(tete == NULL){
			tete = iter1;
		}
		//incermenter l'iterateur 1
		avant_iter1 = iter1;
		iter1 = iter1->frere;
	}

	return tete;
}

tas_binomial* tas_binomial_union(tas_binomial* T1, tas_binomial* T2){

	tas_binomial* T = tas_binomial_creer();
	
	#if AFFICHAGE_INS
		printf("Tas 1\n");
		tas_binomial_afficher(T1);
		printf("Tas 2\n");
		tas_binomial_afficher(T2);
	#endif
	
	T->tete = tas_binomial_fusion(T1, T2);
	free(T1);
	free(T2);
	if(T->tete == NULL){
		return T;
	}

	struct noeud_tas_binomial* avant_x = NULL;
	struct noeud_tas_binomial* x = T->tete;
	struct noeud_tas_binomial* apres_x = x->frere;
	
	#if AFFICHAGE_INS
		printf("Après fusion\n");
		tas_binomial_afficher(T);
	#endif

	while(apres_x != NULL){
		if((x->degre != apres_x->degre)){
			avant_x = x;
			x = apres_x;
		}else{
			if(x->cle <= apres_x->cle){
				x->frere = apres_x->frere;
				lien_binomial(apres_x, x);
			}else{
				if(avant_x == NULL){
					T->tete = apres_x;
				}else{
					avant_x->frere = apres_x;
				}
				lien_binomial(x, apres_x);
				x = apres_x;
			}
		}
		apres_x = x->frere;	
	}

	#if AFFICHAGE_INS
		printf("Après Union\n");
		tas_binomial_afficher(T);
	#endif

	return T;
}


struct noeud_tas_binomial* 	tas_binomial_supprimer_min(tas_binomial* T){
	struct noeud_tas_binomial *x_min = NULL;
	struct noeud_tas_binomial *avant_xmin = NULL;
	struct noeud_tas_binomial *x = T->tete;
	struct noeud_tas_binomial *avant_x = NULL;
	int min = INT_MAX;
	while (x != NULL){
		if(x->cle < min){
			min = x->cle;
			avant_xmin = avant_x;
			x_min = x;
		}
		avant_x = x;
		x = x->frere;
	}
	if(avant_xmin != NULL)
		avant_xmin->frere = x_min->frere;
	else
		T->tete = NULL;
	//verifier si on a besoin mettre xmin_frere a null ??
	x_min->frere = NULL;
	return x_min;
}


struct noeud_tas_binomial* tas_binomial_extraire_min(tas_binomial** t){
	//trouver le min ET LE supprimer
	struct noeud_tas_binomial* x_min = tas_binomial_supprimer_min(*t);
	tas_binomial* t1 = tas_binomial_creer();
	//inverser l ordre chainee des enfants de x, et faire pointer tete[t1] sur la tete de la liste resultante
	struct noeud_tas_binomial* iter = x_min->fils;
	struct noeud_tas_binomial* avant_iter = NULL;
	struct noeud_tas_binomial* tmp;
	while(iter != NULL){
		tmp = iter->frere;
		iter->frere = avant_iter;
		//incrementer iterateur;
		avant_iter = iter;
		iter = tmp;
	}
	t1->tete = avant_iter;
	#if AFFICHAGE_EXT
		printf("\nT1 : tas extrait avec inversion ordre des fils\n");
		tas_binomial_afficher(t1);
		printf("\nT2 : tas principal sans l'element extrait\n");
		tas_binomial_afficher(*t);
	#endif
	*t = tas_binomial_union(*t, t1);
	#if AFFICHAGE_EXT
		printf("\nT  : Resultat de extraire min apres union\n");
		tas_binomial_afficher(*t);
	#endif
	return x_min;
}

void tas_binomial_diminuer_cle(tas_binomial* t, struct noeud_tas_binomial* x, int k){
	struct noeud_tas_binomial* x_min = tas_binomial_min(t);
	if(x_min->cle < k){
		printf("la ouvelle clef est plus grand que la clef courante");
		return;
	}
	x_min->cle = k;
	struct noeud_tas_binomial* y = x;
	struct noeud_tas_binomial* z = x->pere;
	int tmp;
	while((z != NULL) && (y->cle < z->cle)){
		tmp = y->cle;
		y->cle = z->cle;
		z->cle = tmp;
		y = z;
		z = z->pere;
	}

}