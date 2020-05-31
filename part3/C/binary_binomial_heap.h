#ifndef _TP03_H
#define _TP03_H


#define FALSE 0
#define TRUE  1

#define AFFICHAGE_INS 0
#define AFFICHAGE_EXT 0

#include <stdbool.h>


/*****************************************************/
/*                T A S  B I N A I R E               */
/*****************************************************/

struct tas{
	char is_fixed_size;
	int size;
	int capacity;
	int* data;

};

typedef struct tas tas;

tas* tas_creer(int capacity, char is_fixed_size);
void tas_supprimer(tas* t);
char tas_ajouter_cle(tas* t, int a);
char tas_extraire_min(tas* t);
void tas_verifier_et_swaper_si_besoin_vers_le_haut(tas* t, int i);
void tas_afficher(tas* t);
void tas_entasser(tas* t, int i);
int  tas_fils_gauche_noeud(tas* t, int i);
int  tas_fils_droit_noeud(tas* t, int i);
int  tas_parent_noeud(tas* t, int i);
void tas_permuter_noeuds(tas* t, int i, int j);

/*****************************************************/
/*        T A S / A R B R E  B I N O M I A L         */
/*****************************************************/

struct noeud_tas_binomial{
	struct noeud_tas_binomial* pere;
	struct noeud_tas_binomial* fils;
	struct noeud_tas_binomial* frere;
	int    cle;
	int    degre;
};

struct tas_binomial{
	struct noeud_tas_binomial * tete;
};
typedef struct tas_binomial tas_binomial;
typedef struct noeud_tas_binomial arbre_binomial;


arbre_binomial* arbre_binomial_creer(int cle);
void            arbre_binomial_supprimer(arbre_binomial* b);
void            arbre_binomial_afficher(arbre_binomial* b, bool est_racine);

void 			afficher_liste_arbre_binomiaux(arbre_binomial* b);
void            supprimer_liste_arbre_binomiaux(arbre_binomial* t);

tas_binomial*   tas_binomial_creer();

void            tas_binomial_supprimer(tas_binomial* t);
void            tas_binomial_afficher(tas_binomial* t);
tas_binomial*   tas_binomial_inserer(tas_binomial* t, struct noeud_tas_binomial* x);
tas_binomial*   tas_binomial_inserer_cle(tas_binomial* t, int cle);
void            tas_binomial_diminuer_cle(tas_binomial* t, struct noeud_tas_binomial* x, int k);
tas_binomial*   tas_binomial_union(tas_binomial* T1, tas_binomial* T2);

struct noeud_tas_binomial* tas_binomial_fusion(tas_binomial* t1, tas_binomial* t2);
struct noeud_tas_binomial* tas_binomial_extraire_min(tas_binomial** t);


#endif