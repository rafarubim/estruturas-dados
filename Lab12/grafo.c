#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include "grafo.h"
#include "listaprio.h"

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

/* aux para fila e pilha */
typedef struct _sq SQ;
struct _sq {
  int info;
  SQ* prox;
};

static void criaArvoreGeradoraRec(Grafo *grafo, int no_inicial, char* visitados, Grafo *novoGrafo);
static void grafoPercorreProfundidadeRec(Grafo *grafo, int no_inicial, char* visitados);

static SQ* push(SQ* stack, int info){
/* empilha um item */
  SQ* novo = (SQ*)malloc(sizeof(SQ));
  assert(novo);
  novo->info = info;
  novo->prox = stack;
  return novo;
}

static SQ* enqueue(SQ* queue, int info){
/* enfileira um item */
  SQ* novo = (SQ*)malloc(sizeof(SQ));
  SQ* aux = queue;
  assert(novo);
  novo->info = info;
  novo->prox = NULL;
  if (!queue){
    return novo;
  }
  while (aux->prox){
    aux = aux->prox;
  }
  aux->prox = novo;
  return queue;
}

static SQ* pop(SQ* stack,int* popped_info){
/* retira um item da fila/pilha */
  SQ* libera;
  if (!stack){
    *popped_info = -1;
    return NULL;
  }
  *popped_info = stack->info;
  libera = stack;
  stack = stack->prox;
  free(libera);
  return stack;
}

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
    for (i = 0; i < grafo->nv; i++){
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
	printf("Percorre Profundidade: ");
	grafoPercorreProfundidadeRec(grafo, no_inicial, visitados);
	printf("\n");
	free(visitados);
}

void grafoPercorreProfundidadeRec(Grafo *grafo, int no_inicial, char* visitados) {
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

void criaArvoreGeradoraRec(Grafo *grafo, int no_inicial, char* visitados, Grafo *novoGrafo) {
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

void grafoPercorreLargura(Grafo *grafo, int no_inicial){
	int i;	
	SQ* fila = NULL;
	char* enfileirados = (char*) malloc(grafo->nv*sizeof(char));
	for (i = 0; i < grafo->nv; i++)
		enfileirados[i] = 0;
	fila = enqueue(fila, no_inicial);
	enfileirados[no_inicial] = 1;
	printf("Percorre Largura: ");
	while (fila != NULL) {
		int no_aberto;
		Viz* percorre;
		fila = pop(fila, &no_aberto);
		printf("%d, ", no_aberto);
		percorre = grafo->viz[no_aberto];
		while (percorre != NULL) {
			if (!enfileirados[percorre->noj]) {
				fila = enqueue(fila, percorre->noj);
				enfileirados[percorre->noj] = 1;
			}
			percorre = percorre->prox;
		}
	}
	printf("\n");
}

int* menoresCaminhos (Grafo *grafo, int no_inicial) {
	int i, noAberto;
	Viz* percorre;
	ListaP* NosAAbrir = listap_cria(grafo->nv/*,0,NULL,NULL*/); /* Comentei parâmetros e inicializei-os com valores padrão para bater com header da professora */
	int* vecCaminhos = (int*) malloc((grafo->nv+1)*sizeof(int)); /* Tamanho é número de vértices+1 pois um -1 no final indicará fim do vetor */
	for (i = 0; i < grafo->nv+1; i++)
		vecCaminhos[i] = -1;	/* Sinaliza distância mínima ainda incalculada (infinita) */ /* -1 no final para indicar fim do vetor */
	listap_insere(NosAAbrir,0,no_inicial);
	vecCaminhos[no_inicial] = 0;
	while((noAberto = listap_remove(NosAAbrir)) != -1) { /* Abre nó (logo já se sabe sua distância mínima) */
		int distanciaNoAberto = vecCaminhos[noAberto]; /* distanciaNoAberto já é distância mínima até ele */
		percorre = grafo->viz[noAberto];
		while (percorre != NULL) {
			int distanciaNoJ = ((int) percorre->peso) + distanciaNoAberto; /* ditância total para cada vizinho */
			if (vecCaminhos[percorre->noj] == -1) { /* Se distância incalculada */
				vecCaminhos[percorre->noj] = distanciaNoJ; /* Insere possibilidade de distância mínima */
				listap_insere(NosAAbrir,distanciaNoJ,percorre->noj); /* Insere nó entre nós a abrir */
			} else if (distanciaNoJ < vecCaminhos[percorre->noj]) { /* Se possibilidade já foi inserida, mas encontrou-se melhor */
				vecCaminhos[percorre->noj] = distanciaNoJ; /* Substitui distância melhor */
				listap_corrige(NosAAbrir,distanciaNoJ,percorre->noj); /* Nó já está entre os que se deve abrir. Atualizar prioridade. */
			} /* Se possibilidade melhor já estava inserida, ou nó já foi aberto ou já foi marcado para ser */
			percorre = percorre->prox;
		}
	} /* Ao final, todo nó já foi aberto. Logo, todas as distâncias mínimas foram calculadas */
	listap_libera(NosAAbrir);
	return vecCaminhos;
}
