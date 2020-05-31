#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include "binary_binomial_heap.h"
#include "analyzer.h"
int main(int argc, char ** argv){
  printf("*********** Programme de test arbre binomial *****************\n");
  tas_binomial* TasBinomial = tas_binomial_creer();
  int max = 7;
  printf("Nombre d'éléments à inserer : %d\n\n", max);
  for (int i = 1; i <= max; i++){
    printf("*********** Insertion de la valeur %d dans le tas *****************\n", i);
    TasBinomial = tas_binomial_inserer_cle(TasBinomial, i);
    tas_binomial_afficher(TasBinomial);
  }
  printf("*********** Extraire min *****************\n");
  tas_binomial_extraire_min(&TasBinomial);
  printf("*********** Resultat *****************\n");
  tas_binomial_afficher(TasBinomial);
  return EXIT_SUCCESS;
}



