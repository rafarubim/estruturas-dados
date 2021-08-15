#include <stdio.h>
#include <stdlib.h>
#include "listaprio.h"

struct _listaprio {
  int max; /* tamanho maximo do heap */
  int pos; /* proxima posicao disponivel no vetor */ 
  int* prioridade; /* vetor das prioridades */
}; 

static void listap_monta (ListaP* heap, int n, int *prios) {
    int i, j;
    if (n > heap->max) {printf("Deu treta maligna\n");    exit(1);}

    for (i = 0; i < n; i++)
        heap->prioridade[i] = prios[i];
    heap->pos = n;

    for (i = n-1; i >= 0; i--) {
        j = i;
        while(2*j+1 <= n-1) { //Tem pelo menos 1 filho
            int troquei = 0; // Ainda nao troquei o pai por nenhum filho
            if (2*j+2 <= n-1) { //Tem 2 filhos
                if (heap->prioridade[2*j+1] < heap->prioridade[2*j+2]) {// Filho maior é filho 2
                    if (heap->prioridade[2*j+2] > heap->prioridade[j]) { // Pai é menor que filho
                        int temp = heap->prioridade[2*j+2];
                        heap->prioridade[2*j+2] = heap->prioridade[j]; // Troca
                        heap->prioridade[j] = temp;
                        troquei = 2; // Troquei pelo filho 2
                    }
                } else { //Filho maior é filho 1
                    if (heap->prioridade[2*j+1] > heap->prioridade[j]) {// Pai é menor que filho
                        int temp = heap->prioridade[2*j+1];
                        heap->prioridade[2*j+1] = heap->prioridade[j]; // Troca
                        heap->prioridade[j] = temp;
                        troquei = 1; // Troquei pelo filho 1
                    }
                }
            } else { // Tem 1 filho
                if (heap->prioridade[2*j+1] > heap->prioridade[j]) {// Pai é menor que filho
                    int temp = heap->prioridade[2*j+1];
                    heap->prioridade[2*j+1] = heap->prioridade[j]; // Troca
                    heap->prioridade[j] = temp;
                    troquei = 1; // Troquei pelo filho 1
                }
            }
            if (troquei == 0) // Se não fiz trocas, ir para próximo nó
                break;
            else if (troquei == 1) // Se troquei, devo trocar até a base da árvore
                j = i*2+1;
            else
                j = i*2+2;
        }
    }
}

ListaP* listap_cria(int max, int qtos, int* iniciais){
  ListaP* heap=(ListaP*)malloc(sizeof(struct _listaprio)); heap->max=max;
  heap->pos=0;
  heap->prioridade=(int *)malloc(max*sizeof(int));
  listap_monta(heap, qtos, iniciais);
  return heap;
}

int *cria_listaordenada (ListaP *lp, int* tam) {

    int i, j, tempMax, *novo;

    *tam = lp->pos;
    for (i = 0; i < *tam; i++) {
        int temp = listap_remove(lp);
        for (j = 0; j < i; j++)
            lp->prioridade[lp->pos+j] = lp->prioridade[lp->pos+1+j];
        lp->prioridade[(*tam)-1] = temp;
    }
    novo = lp->prioridade;

    free(lp);

    return lp->prioridade;
}

static void troca(int a, int b, int* v) {
  int f = v[a];
  v[a] = v[b];
  v[b] = f;
}

static void corrige_acima(ListaP* heap, int pos) {
  int pai;
  while (pos > 0){
    pai = (pos-1)/2;
    if (heap->prioridade[pai] < heap->prioridade[pos])
      troca(pos,pai,heap->prioridade);
    else 
      break;
    pos=pai;
  }
}

void listap_insere(ListaP* heap, int prioridade) {
  if ( heap->pos < heap->max ) {
    heap->prioridade[heap->pos]=prioridade; 
    corrige_acima(heap,heap->pos); 
    heap->pos++;
    } 
    else {
      printf("Heap CHEIO!\n"); 
      exit(1);
    }
}

static void corrige_abaixo(ListaP* heap){
  int pai=0;
  while (2*pai+1 < heap->pos){
    int filho_esq=2*pai+1;
    int filho_dir=2*pai+2;
    int filho;
    if (filho_dir >= heap->pos) filho_dir=filho_esq;
    if (heap->prioridade[filho_esq]>heap->prioridade[filho_dir])
        filho=filho_esq;
    else
        filho=filho_dir;
    if (heap->prioridade[pai]<heap->prioridade[filho])
            troca(pai,filho,heap->prioridade);
    else
            break;
    pai=filho;
  }
}

int listap_remove(ListaP* heap) {
  if (heap->pos>0) {
    int topo=heap->prioridade[0];
    heap->prioridade[0]=heap->prioridade[heap->pos-1];
    heap->pos--;
    corrige_abaixo(heap);
    return topo;
  }
  else {
     printf("Heap VAZIO!");
     return -1;
  }
}

void listap_libera (ListaP * h) {
  free(h->prioridade);
  free(h);
}

void debug_listap_show (ListaP *h, char* title){
	int i;
	printf("%s={",title);
	for (i=0; i<(h->pos); i++)
		printf("%d,",h->prioridade[i]);
	printf("}\n");

}


