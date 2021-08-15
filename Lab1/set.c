#include <stdlib.h>
#include <stdio.h>
#include "set.h"

#define TAM 32

/* cria um conjunto com n elementos */
Set* setCreate(void){
	Set* set = (Set*)malloc(sizeof(Set));
	if (set != NULL) *set = 0;
	return set;
}

/* destroi (desaloca) o conjunto */
Set* setDestroy(Set* set) {
	if (set) free(set);
	return NULL;
}

/* cria uma copia do conjunto */
Set* setCopy(Set* set){
  Set* newSet = setCreate();
  if (newSet != NULL) *newSet = 0;
  *newSet = *set;
  return newSet;
}

/* cria um complemento do conjunto */
Set* setComplement(Set* set){
  Set* newSet = setCreate();
  if (newSet != NULL) *newSet = ~*set;
  return newSet;
}

/* insere o elemento i no conjunto */
void setInsert(Set *set, int i) {
  if (i >= 0 && i < 32)
    *set = (*set) | (1 << i);
}

/* remove o elemento i do conjunto */
void setRemove(Set *set, int i){
  if (i >= 0 && i < 32)
    *set = (*set) & (~(1 << i));
}


/* testa se o elemento i pertence ao conjunto */
int setIsMember(Set *set, int i){
  if ((i<0) || (i>8*sizeof(Set))) return 0;
  return ((1<<i) & (*set));
}


/* cria a uniao de dois conjuntos */
Set* setUnion( Set *set1,  Set *set2){
  Set* newSet = setCreate();
  if (newSet != NULL) *newSet = (*set1) | (*set2);
  return newSet;
}

/* calcula a intersecao de dois conjuntos, a cardinalidade e' a do menor */
Set* setIntersection( Set *set1,  Set *set2){
  Set* newSet = setCreate();
  if (newSet != NULL) *newSet = (*set1) & (*set2);
  return newSet;
}

/* calcula a diferenca de set1-set2. a cardinalidade e'a de set1. */
Set* setDifference(Set *set1, Set *set2){
  Set* newSet = setCreate();
  if (newSet != NULL) *newSet = (*set1) ^ (*set2);
  return NULL;
}



/* verifica de set2 e' um sub conjunto de set1 */
int setIsSubset( Set *set1,  Set *set2) {
  return (*set2) == ((*set1) & (*set2));
}


/* verifica se dois conjuntos sao iguais */
int setIsEqual( Set *set1,  Set *set2) {
  return *set1 == *set2;
}

/* informa a cardilaidade do conjunto */
int setNumberOfElements(Set* set){
  int i, count = 0;
  for (i = 0; i < 8*sizeof(Set); i++)
    if (setIsMember(set, i))
      count++;
  return count;
}

/* mostra os elementos do conjunto */
void setShow(char* title, Set* set){
	int i, first=1;
	printf("%s={", title);
	for (i = 0; i < 8*sizeof(Set); i++) 
		if (setIsMember(set, i)) { 
			if (first) { 
				printf("%d", i); 
				first = 0; 
			}
			else 
				printf(",%d", i);
                 }
	printf("}\n");
}

