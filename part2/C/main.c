#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include "arraylist.h"
#include "analyzer.h"


int main(int argc, char ** argv){
  int i;
  // Tableau dynamique.
  arraylist_t * a = arraylist_create();
  // Analyse du temps pris par les opérations.
  analyzer_t * time_analysis = analyzer_create();
  // Analyse du nombre de copies faites par les opérations.
  analyzer_t * copy_analysis = analyzer_create();
  // Analyse de l'espace mémoire inutilisé.
  analyzer_t * memory_analysis = analyzer_create(); 
  struct timespec before, after;
  // utilisé comme booléen pour savoir si une allocation a été effectuée.
  char memory_allocation; 

  float p = 0.5;

  printf("Valeur de p par defaut 0.5\n");
  
  if(argc > 1){
    p = atof(argv[1]);
    printf("Changement de la valeur de p à %.2f\n",p);
  }

  srand(11709949);

  for(i = 0; i < 1000000 ; i++){
    float p_rand = (float)rand()/(float)RAND_MAX;
    if(p_rand < p)
    {
      // Ajout d'un élément et mesure du temps pris par l'opération.
      timespec_get(&before, TIME_UTC);
      memory_allocation = arraylist_append(a, i);
      timespec_get(&after, TIME_UTC);
    }else{
      // Ajout d'un élément et mesure du temps pris par l'opération.
      if(arraylist_size(a) > 0)
      {
        timespec_get(&before, TIME_UTC);
        memory_allocation = arraylist_pop_back(a);
        timespec_get(&after, TIME_UTC);
      }else{
        after.tv_nsec  = 0;
        before.tv_nsec = 0;
      }

    }
    // Enregistrement du temps pris par l'opération
    analyzer_append(time_analysis, after.tv_nsec - before.tv_nsec);
    // Enregistrement du nombre de copies efféctuées par l'opération.
    // S'il y a eu réallocation de mémoire, il a fallu recopier tout le tableau.
    analyzer_append(copy_analysis, (memory_allocation)? arraylist_size(a):1 );
    // Enregistrement de l'espace mémoire non-utilisé.
    analyzer_append(memory_analysis,arraylist_capacity(a)-arraylist_size(a));
  }


// Affichage de quelques statistiques sur l'expérience.
  fprintf(stderr, "Total cost: %Lf\n", get_total_cost(time_analysis));
  fprintf(stderr, "Average cost: %Lf\n", get_average_cost(time_analysis));
  fprintf(stderr, "Variance: %Lf\n", get_variance(time_analysis));
  fprintf(stderr, "Standard deviation: %Lf\n", get_standard_deviation(time_analysis));

  // Sauvegarde les données de l'expérience.
  save_values(time_analysis, "../plots/dynamic_array_time_c.plot");
  save_values(copy_analysis, "../plots/dynamic_array_copy_c.plot");
  save_values(memory_analysis, "../plots/dynamic_array_memory_c.plot");

  // Nettoyage de la mémoire avant la sortie du programme
  arraylist_destroy(a);
  analyzer_destroy(time_analysis);
  analyzer_destroy(copy_analysis);
  analyzer_destroy(memory_analysis);

  
  return EXIT_SUCCESS;
}



