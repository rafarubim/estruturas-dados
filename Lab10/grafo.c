#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include "grafo.h"


typedef struct _viz Viz;
struct _viz {
  int noj;
  float peso;
  Viz*  prox;
};

struct _grafo {
  int nv;           /* numero de nos ou vertices */
  int na;           /* numero de arestas */
  Viz** viz;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

static void grafoPercorreProfundidadeRec(Grafo *grafo, int no_inicial, char* visitados);

static void criaArvoreGeradoraRec(Grafo *grafo, int no_inicial, char* visitados, Grafo* novoGrafo);

static Viz* criaViz(Viz* head, int noj, float peso) {
/* insere vizinho no inicio da lista */
  Viz* no = (Viz*) malloc(sizeof(Viz));
  assert(no);
  no->noj = noj;
  no->peso = peso;
  no->prox = head;
  return no;
}

static Grafo* grafoCria(int nv, int na) {

  int i;
  Grafo* g = (Grafo *) malloc(sizeof(Grafo));
  g->nv = nv;
  g->na = na;
  g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
  for (i = 0; i < nv; i++)
    g->viz[i] = NULL;
  return g;
}


Grafo* grafoLe( char* filename ) {
/* cria grafo nÃ£o orientado - supÃµe que arquivo estÃ¡ correto! */

  FILE *arq = fopen(filename,"rt");
  int nv, na, no1, no2 = 0;
  float peso;
  Grafo* novo;
	
  fscanf(arq, "%d %d", &nv, &na);
  novo = grafoCria(nv, na);
  assert(novo);
  while (fscanf(arq, "%d %d %f", &no1, &no2, &peso) == 3) {
    novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
    novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
  }
  fclose(arq);
  return novo;
}

Grafo*   grafoLibera(Grafo* grafo) {
  if (grafo) {
    int i = 0;
    Viz* no,*aux;
    for (i = 0; i < grafo->nv; i++){
      no = grafo->viz[i];
      while (no){
        aux = no->prox;
        free(no);
        no = aux;
      }
    }
    free(grafo->viz);
    free(grafo);
  }
  return NULL;
}

void grafoMostra (char* title, Grafo * grafo) {
  int i;
  if (title)
    printf("%s:\n", title);
  if (grafo) {
    printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
    for (i = 0; i < grafo->nv; i++) {
		  Viz* viz = grafo->viz[i];
		  printf("[%d]->", i);
		  while (viz) {
		    printf("{%d, %g}->", viz->noj, viz->peso);
		    viz = viz->prox;
		  }
		  printf("NULL\n");
    }
  }
}

void grafoPercorreProfundidade(Grafo *grafo, int no_inicial){
	int i;
	char* visitados = (char*) malloc(grafo->nv*sizeof(char));
	assert(visitados);
	for(i=0;i<grafo->nv;i++)
		visitados[i] = 0;
	printf("Percorre: ");
	grafoPercorreProfundidadeRec(grafo, no_inicial, visitados);
	printf("\n");
	free(visitados);
}

static void grafoPercorreProfundidadeRec(Grafo *grafo, int no_inicial, char* visitados) {
	Viz* percorre = grafo->viz[no_inicial];
	visitados[no_inicial] = 1;
	printf("%d, ", no_inicial);
	while(percorre) {
		if (!visitados[percorre->noj])
			grafoPercorreProfundidadeRec(grafo, percorre->noj, visitados);
		percorre = percorre->prox;
	}
}

Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial) {
	int i;
	Grafo* novoGrafo;
	char* visitados = (char*) malloc(grafo->nv*sizeof(char));
	assert(visitados);
	for(i=0;i<grafo->nv;i++)
		visitados[i] = 0;
	novoGrafo = grafoCria(grafo->nv,0);
	criaArvoreGeradoraRec(grafo, no_inicial, visitados, novoGrafo);
	free(visitados);
	return novoGrafo;
}

static void criaArvoreGeradoraRec(Grafo *grafo, int no_inicial, char* visitados, Grafo *novoGrafo) {
	Viz* percorre = grafo->viz[no_inicial];
	visitados[no_inicial] = 1;
	while(percorre) {
		if (!visitados[percorre->noj]) {
			novoGrafo->viz[no_inicial] = criaViz(novoGrafo->viz[no_inicial],percorre->noj,percorre->peso);
			novoGrafo->viz[percorre->noj] = criaViz(novoGrafo->viz[percorre->noj],no_inicial,percorre->peso);
			(novoGrafo->na)++;
			criaArvoreGeradoraRec(grafo, percorre->noj, visitados, novoGrafo);
		}
		percorre = percorre->prox;
	}
}

void   grafoPercorreLargura(Grafo *grafo, int no_inicial){
}
