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
  // Création du Tas Binaire avec taille dynamique
  tas* t2          = tas_creer(16, FALSE);
  // Analyse du temps pris par les opérations du tas binaire
  analyzer_t * time_analysis_binary_dyn   = analyzer_create();
  // Analyse du nombre de copies faites par les opérations.
  analyzer_t * copy_analysis_binary_dyn   = analyzer_create();
  // Analyse de l'espace mémoire inutilisé.
  analyzer_t * memory_analysis_binary_dyn = analyzer_create(); 
  // Variables de mesure pour chaque structure de données
  struct timespec before_binary_d, after_binary_d;
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
      timespec_get(&before_binary_d, TIME_UTC);
      memory_allocation = tas_ajouter_cle(t2, valeur);
      timespec_get(&after_binary_d, TIME_UTC);
    }
    else
    {
      // Suppression d'un élément et mesure du temps pris par l'opération.
      if(t2->size != 0){
          timespec_get(&before_binary_d, TIME_UTC);
          memory_allocation = tas_extraire_min(t2);
          timespec_get(&after_binary_d, TIME_UTC);
      }else{
        before_binary_d.tv_nsec  = 0;
        after_binary_d.tv_nsec  = 1;
      }
    }
    // Enregistrement du temps pris par l'opération avec le Tas binaire a taille dynamique
    analyzer_append(time_analysis_binary_dyn   , after_binary_d.tv_nsec   - before_binary_d.tv_nsec);
    // Enregistrement du nombre de copies effectuées avec le Tas binaire a taille dynamique
    analyzer_append(copy_analysis_binary_dyn, (memory_allocation)? i:1);
    // Enregistrement de l'espace mémoire non-utilisé avec le Tas binaire a taille dynamique
    analyzer_append(memory_analysis_binary_dyn,t2->capacity-t2->size);

    memory_allocation = FALSE;
  }

  // Affichage de quelques statistiques sur l'expérience.
  fprintf(stderr, "Total cost binary dynamique         : %Lf\n", get_total_cost(time_analysis_binary_dyn));
  fprintf(stderr, "Average cost binary dynamique       : %Lf\n", get_average_cost(time_analysis_binary_dyn));
  fprintf(stderr, "Variance binary dynamique           : %Lf\n", get_variance(time_analysis_binary_dyn));
  fprintf(stderr, "Standard deviation binary dynamique : %Lf\n", get_standard_deviation(time_analysis_binary_dyn));

  // Sauvegarde les données de l'expérience.
  save_values(time_analysis_binary_dyn   , "../plots/dynamic_binary_heap_time_c.plot");
  save_values(copy_analysis_binary_dyn   , "../plots/dynamic_binary_heap_copy_c.plot");
  save_values(memory_analysis_binary_dyn , "../plots/dynamic_binary_heap_memory_c.plot");

  // Nettoyage de la mémoire avant la sortie du programme
  tas_supprimer(t2);
  analyzer_destroy(time_analysis_binary_dyn);
  
  return EXIT_SUCCESS;
}



