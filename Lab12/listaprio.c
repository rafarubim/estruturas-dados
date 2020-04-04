#include <stdio.h>
#include <stdlib.h>
#include "listaprio.h"

typedef struct {
	int prioridade;
	int dado;
} prioDado;

struct _listaprio {
  int max; /* tamanho maximo do heap */
  int pos; /* proxima posicao disponivel no vetor */ 
  prioDado* prioridade; /* vetor das prioridades */
}; 

static void corrige_abaixo(prioDado* prios, int atual, int tam);

static void listap_monta (ListaP* heap, int n, int *dados, int *prioridades){
  int i;
  if (n>heap->max) {
    printf ("valores demais! \n");
    exit(1);
  }
  for (i=0;i<n;i++) heap->prioridade[i].dado = dados[i];
  for (i=0;i<n;i++) heap->prioridade[i].prioridade = prioridades[i];
  heap->pos = n;
  for (i=(n/2)+1;i>=0;i--) {
    corrige_abaixo(heap->prioridade,i,heap->pos); 
  }
}

ListaP* listap_cria(int max/*, int qtos, int* dadosIniciais, int* prioridadesIniciais*/){
	int qtos = 0;	int* dadosIniciais = NULL;	int* prioridadesIniciais = NULL; /* Comentei parâmetros e inicializei-os com valores padrão para bater com header da professora */
  ListaP* heap=(ListaP*)malloc(sizeof(struct _listaprio)); 
  heap->max=max;
  heap->pos=0;
  heap->prioridade=(prioDado *)malloc(max*sizeof(prioDado)); 
  if (qtos>0) {
    listap_monta (heap, qtos, dadosIniciais, prioridadesIniciais);
  }
  return heap;
}

static void troca(int a, int b, prioDado* v) {
  prioDado f = v[a];
  v[a] = v[b];
  v[b] = f;
}

static void corrige_acima(ListaP* heap, int pos) {
  int pai;
  while (pos > 0){
    pai = (pos-1)/2;
    if (heap->prioridade[pai].prioridade > heap->prioridade[pos].prioridade)
      troca(pos,pai,heap->prioridade);
    else 
      break;
    pos=pai;
  }
}

void listap_insere(ListaP* heap, int prioridade, int dado) {
  if ( heap->pos < heap->max ) {
    heap->prioridade[heap->pos].dado = dado;
    heap->prioridade[heap->pos].prioridade = prioridade; 
    corrige_acima(heap,heap->pos); 
    heap->pos++;
    } 
    else {
      printf("Heap CHEIO!\n"); 
      exit(1);
    }
}

static void corrige_abaixo(prioDado* prios, int atual, int tam){
  int pai=atual;
  int filho_esq, filho_dir, filho;
  while (2*pai+1 < tam){
    filho_esq=2*pai+1;
    filho_dir=2*pai+2;
    if (filho_dir >= tam) filho_dir=filho_esq;
    if (prios[filho_esq].prioridade < prios[filho_dir].prioridade)
        filho=filho_esq;
    else
        filho=filho_dir;
    if (prios[pai].prioridade > prios[filho].prioridade)
            troca(pai,filho,prios);
    else
            break;
    pai=filho;
  }
}

int listap_remove(ListaP* heap) {
  if (heap->pos>0) {
    int topo=heap->prioridade[0].dado;
    heap->prioridade[0]=heap->prioridade[heap->pos-1];
    heap->pos--;
    corrige_abaixo(heap->prioridade, 0, heap->pos);
    return topo;
  }
  else {
     return -1;
  }
}

void listap_libera (ListaP * h) {
  free(h->prioridade);
  free(h);
}

void listap_corrige (ListaP* heap, int novaprio, int dado) { /* Implementação assume possibilidade de haver mais de uma prioridade a ser corrigida */
	int i;
	for (i = 0; i < heap->pos; i++)
		if (heap->prioridade[i].dado == dado) {
			int velhaprio = heap->prioridade[i].prioridade;
			heap->prioridade[i].prioridade = novaprio;
			if (velhaprio > novaprio)
				corrige_acima(heap,i);
			else
				corrige_abaixo(heap->prioridade,i,heap->pos);
		}
}

void debug_listap_show (ListaP *h, char* title){
	int i;
	printf("%s={",title);
	for (i=0; i<(h->pos); i++)
		printf("%d:%d,",h->prioridade[i].dado,h->prioridade[i].prioridade);
	printf("}\n");

}   

