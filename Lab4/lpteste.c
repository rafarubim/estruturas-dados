/*#include <stdio.h>
#include "listaprio.h"

int main(void) {
  int i,n=8;
  int info, v[]={25, 48, 37, 12, 57, 86, 33, 92};
  ListaP* lp = listap_cria(30, 0, NULL);
  for (i=0;i<n;i++) {
    listap_insere(lp,v[i]);
    printf("insere %d, ", v[i]);
    debug_listap_show(lp, "lp=");
  }
  do{
    info = listap_remove(lp);
    printf("remove %d ", info);
    debug_listap_show(lp, "lp=");
  } while(info>0);

  listap_libera(lp);
  return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaprio.h"

int* meuheapsort (int nums[], int tam) {
  ListaP *lp = listap_cria (tam, tam, nums);
  int *novosnums = cria_listaordenada (lp, &tam);
  return novosnums;
}

int compara (const void* a, const void* b) {
    int *ia = (int*)a;
    int *ib = (int*)b;
    if (*ia<*ib)
        return 1;
    else if (*ib<*ia)
        return -1;
    else return 0;
}
 
int main(void) {
  int i, n = 8, qtd = 0;
  clock_t time;
  int info, v[]={25, 48, 37, 12, 57, 86, 33, 92};
  int *lstOrd, *lstOrd2;
  int tam, tam2;
  FILE *entradas;
  ListaP *lp, *lp2;
  int *numeros, *numeros2;
 // ListaP* lp = listap_cria(30, 8, v);

  entradas = fopen("entradas//entrada-1000000-cresce", "rt");
  if (!entradas) {printf("Erro em leitura do arquivo \"entrada-1000-cresce\".\n\n");    exit(1);}
  if (fscanf(entradas, " %d", &qtd) != 1) {printf("Erro! Arquivo em formato inespecificado!\n\n");    exit(1);}

  numeros = (int*)malloc(qtd*sizeof(int));
  if (!numeros) {printf("Memoria insuficiente.\n\n");    exit(1);}

  for (i = 0; i < qtd; i++)
      if (fscanf(entradas, " %d", &numeros[i]) != 1) {printf("Erro! Numero incorreto de numeros no arquivo\n\n");    exit(1);}

  fclose(entradas);

  time = clock();

  lp = listap_cria(qtd, qtd, numeros);

  time = clock() - time;
  printf("Tempo criacao com vetor: %ld milisegundos\n", time);

  time = clock();

  lp2 = listap_cria(qtd, 0, NULL);

  for (i = 0; i < qtd; i++)
      listap_insere(lp2, numeros[i]);

  time = clock() - time;

  printf("Criacao com insercao: %ld milisegundos\n", time);

  //debug_listap_show(lp, "lp");
  //debug_listap_show(lp2, "lp2");

  numeros2 = (int*)malloc(qtd*sizeof(int));
  if (!numeros2) {printf("Memoria insuficiente.\n\n");    exit(1);}

  for (i = 0; i < qtd; i++)
    numeros2[i] = numeros[i];

  time = clock();

  lstOrd = meuheapsort(numeros, qtd);

  time = clock() - time;

  printf("Minha criacao lista ordenada: %ld milisegundos\n", time);

  /*printf("lstOrd = {");
  for (i = 0; i < tam; i++)
      printf("%d,", lstOrd[i]);
  printf("}\n");*/

  time = clock();

  qsort (numeros2, qtd, sizeof(int), compara);

  time = clock() - time;

  printf("Lista ordenada por qsort: %ld milisegundos\n", time);

  /*printf("numeros = {");
  for (i = 0; i < tam; i++)
      printf("%d,", numeros[i]);
  printf("}\n");*/


  //debug_listap_show(lp, "lp=");

  //lstOrd = cria_listaordenada (lp, &tam);

  /*printf("lstOrd = {");
  for (i = 0; i < tam; i++)
      printf("%d,", lstOrd[i]);
  printf("}\n");*/

  /*for (i=0;i<n;i++) {
    listap_insere(lp,v[i]);
    printf("insere %d, ", v[i]);
    debug_listap_show(lp, "lp=");
  }

  debug_listap_show(lp, "lp=");

  do{
    info = listap_remove(lp);
    printf("remove %d ", info);
    debug_listap_show(lp, "lp=");
  } while(info>0);*/

  listap_libera(lp);
  listap_libera(lp2);
  return 0;
}

