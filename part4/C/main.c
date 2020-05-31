#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "b_tree/btree.h"
#include "b_tree/btree_tools.h"
#include "avl/avl.h"
#include "analyzer.h"


#define ORDRE_CROISSANT   0
#define ORDRE_DECROISSANT 1
#define ORDRE_ALEATOIRE   2

#define MAX_KEYS 1000000

BTree   *b_tree_root;

avlNode *avl_root;

int values[MAX_KEYS];

void populate_values() {
	int i;
	for (i = 0; i < MAX_KEYS; ++i) {
		values[i] = i;
	}
}

int main(int argc, char ** argv){
  
  int i;
  
  populate_values();

  int order = 64;

  b_tree_root = btree_new(order);
  avl_root    = insert(avl_root, 0);
  // Analyse du temps pris par les opérations.
  analyzer_t * time_analysis_btree = analyzer_create();
  analyzer_t * time_analysis_avl = analyzer_create();

  struct timespec before_btree, before_avl, after_b_tree, after_avl;
  // utilisé comme booléen pour savoir si une allocation a été effectuée.
  char memory_allocation; 

  memory_allocation = 1;

  float random = 0.0;

  int ordre = ORDRE_CROISSANT;
  
  float p = 0.5;
  
  printf("Valeur de p par defaut 0.5\n");

  if(argc > 1){
    ordre = atoi(argv[1]);
    printf("Changement de l'ordre des valeur à inserer : %d\n",ordre);
  }
  
  if(argc > 2){
    p = atof(argv[2]);
    printf("Changement de la valeur de p à %.2f\n",p);
  }
  int cle = 0;
  for(i = 0; i < 1000000 ; i++){
    
    random = rand()/RAND_MAX;
    
    if(random < 0.5)
    {
      if(ordre == ORDRE_DECROISSANT){
        cle = 1000000 - i;
      }else if(ordre == ORDRE_ALEATOIRE){
        cle = rand() % 1000000;
      }else {
        cle = i;
      }
      timespec_get(&before_btree, TIME_UTC);
      btree_insert(b_tree_root, cle, &values[i]);
      timespec_get(&after_b_tree, TIME_UTC);

      timespec_get(&before_avl, TIME_UTC);
      insert(avl_root, cle);
      timespec_get(&after_avl, TIME_UTC);
    }else
    {
    	timespec_get(&before_btree, TIME_UTC);
    	btree_remove(b_tree_root, rand() % i);
    	timespec_get(&after_b_tree, TIME_UTC);
    	
    	timespec_get(&before_avl, TIME_UTC);
    	delete(avl_root, rand() % i);
    	timespec_get(&after_avl, TIME_UTC);    	
    }
    analyzer_append(time_analysis_btree, (after_b_tree.tv_sec * 1000000000 + after_b_tree.tv_nsec) - (before_btree.tv_sec * 1000000000 + before_btree.tv_nsec));
    analyzer_append(time_analysis_avl  , (after_avl.tv_sec * 1000000000 + after_avl.tv_nsec) - (before_avl.tv_sec * 1000000000 + before_avl.tv_nsec) );
  }
  // Affichage de quelques statistiques sur l'expérience sur le B-Arbre.
  fprintf(stderr, "Total cost: %Lf\n", get_total_cost(time_analysis_btree));
  fprintf(stderr, "Average cost: %Lf\n", get_average_cost(time_analysis_btree));
  fprintf(stderr, "Variance: %Lf\n", get_variance(time_analysis_btree));
  fprintf(stderr, "Standard deviation: %Lf\n", get_standard_deviation(time_analysis_btree));

  // Affichage de quelques statistiques sur l'expérience sur l'AVL.
  fprintf(stderr, "Total cost: %Lf\n", get_total_cost(time_analysis_avl));
  fprintf(stderr, "Average cost: %Lf\n", get_average_cost(time_analysis_avl));
  fprintf(stderr, "Variance: %Lf\n", get_variance(time_analysis_avl));
  fprintf(stderr, "Standard deviation: %Lf\n", get_standard_deviation(time_analysis_avl));

  // Sauvegarde les données de l'expérience.
  save_values(time_analysis_btree, "../plots/dynamic_btree_time_c.plot");
  save_values(time_analysis_avl  , "../plots/dynamic_avl_time_c.plot");

  // Nettoyage de la mémoire avant la sortie du programme
  analyzer_destroy(time_analysis_btree);
  analyzer_destroy(time_analysis_avl);
//  btree_delete_h(b_tree_root);
  freeAVL(avl_root);

  return EXIT_SUCCESS;
}



