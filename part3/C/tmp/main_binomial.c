#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "binary_binomial_heap.h"
#include "analyzer.h"

#define ORDRE_CROISSANT   0
#define ORDRE_DECROISSANT 1
#define ORDRE_ALEATOIRE   2


int main(int argc, char ** argv){
  int i;
  // Création du Tas Binomial
  tas_binomial* t3 = tas_binomial_creer();
  // Analyse du temps pris par les opérations du tas binomial.
  analyzer_t * time_analysis_binomial = analyzer_create();
  // Variables de mesure pour chaque structure de données
  struct timespec before_binomial_h, after_binomial_h;
  // utilisé comme booléen pour savoir si une allocation a été effectuée.
  char memory_allocation = FALSE;
  //initialisation de srand pour avoir une experience unique
  srand(11709949);

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

  int valeur = 0;
  for(i = 0; i < 1000000 ; i++){
    
    random = rand()/RAND_MAX;
    
    if(random < 0.5)
    {
      if(ordre == ORDRE_DECROISSANT){
        valeur = 1000000 - i;
      }else if(ordre == ORDRE_ALEATOIRE){
        valeur = rand() % 1000000;
      }else {
        valeur = i;
      }
      // Ajout d'un élément et mesure du temps pris par l'opération.
      timespec_get(&before_binomial_h, TIME_UTC);
      tas_binomial_inserer_cle(t3, i);
      timespec_get(&after_binomial_h, TIME_UTC);
    }
    else
    {
      // Suppression d'un élément et mesure du temps pris par l'opération.      
      if(t3->tete != NULL){
        timespec_get(&before_binomial_h, TIME_UTC);
			  tas_binomial_extraire_min(&t3);
        timespec_get(&after_binomial_h, TIME_UTC);
      }else{
        before_binomial_h.tv_nsec  = 0;
        after_binomial_h.tv_nsec  = 1;
      }
    }
    // Enregistrement du temps pris par l'opération avec le Tas binomial
    analyzer_append(time_analysis_binomial, after_binomial_h.tv_nsec - before_binomial_h.tv_nsec);
  }


  // Affichage de quelques statistiques sur l'expérience.
  fprintf(stderr, "Total cost binomial         : %Lf\n", get_total_cost(time_analysis_binomial));
  fprintf(stderr, "Average cost binomial       : %Lf\n", get_average_cost(time_analysis_binomial));
  fprintf(stderr, "Variance binomial           : %Lf\n", get_variance(time_analysis_binomial));
  fprintf(stderr, "Standard deviation binomial : %Lf\n", get_standard_deviation(time_analysis_binomial));

  // Sauvegarde les données de l'expérience.
  save_values(time_analysis_binomial     , "../plots/dynamic_binomial_heap_time_c.plot");
  // Nettoyage de la mémoire avant la sortie du programme
  tas_binomial_supprimer(t3);
  analyzer_destroy(time_analysis_binomial);
  
  return EXIT_SUCCESS;
}



