#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "grafo.h"
#include "listaprio.h"
#include "ub.h"


typedef struct _viz Viz;
struct _viz {
  int noj;
  int peso;
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


static SQ* push(SQ* stack, int info){
  SQ* novo = (SQ*)malloc(sizeof(SQ));
  assert(novo);
  novo->info = info;
  novo->prox = stack;
  return novo;
}

static SQ* enqueue(SQ* queue, int info){
  SQ* novo = (SQ*)malloc(sizeof(SQ));
  assert(novo);
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

static Viz* criaViz(Viz* head, int noj, int peso) {
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
  assert(g);
  g->nv = nv;
  g->na = na;
  g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
  assert(g->viz);
  for (i = 0; i < nv; i++)
    g->viz[i] = NULL;
  return g;
}


Grafo* grafoLe( char* filename ) {
/* cria grafo nÃ£o orientado - supÃµe que arquivo estÃ¡ correto! */

  FILE *arq = fopen(filename,"rt");
  int nv, na, no1, no2 = 0;
  int peso;
  Grafo* novo;
	
  fscanf(arq, "%d %d", &nv, &na);
  novo = grafoCria(nv, na);
  assert(novo);
  while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
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

void grafoMostra (Grafo * grafo) {
  int i;
  if (grafo) {
    printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
    for (i = 0; i < grafo->nv; i++){
      Viz* viz = grafo->viz[i];
      printf("[%d]->", i);
      while (viz) {
        printf(" {%d, %d}", viz->noj, viz->peso);
        viz = viz->prox;
      }
      printf("\n");
    }
  }
}

void grafoPercorreProfundidade(Grafo *grafo, int no_inicial){
  SQ *q = NULL;
  Viz *v; int no;  
  char *visitado;
  if (grafo == NULL) return;
  visitado = (char*) malloc(sizeof(int)*grafo->nv);
  assert(visitado);
  for (no=0;no<(grafo->nv);no++) visitado[no] = 0;
  no = no_inicial;
  while (no>=0) {
    if (!visitado[no]) {
      printf ("%d-", no);
      visitado[no] = 1;
      v = grafo->viz[no];
      while (v!=NULL) {
        if (!visitado[(v->noj)]) {
          q = push (q, v->noj);
        }
        v = v->prox;
      }
    }
    q=pop(q, &no);
  }
 printf ("\n");
} 


Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial) {
  return NULL;
}

void grafoPercorreLargura(Grafo *grafo, int no_inicial){
  SQ *q = NULL;
  Viz *v; int no;  
  int *enfileirado;
  if (grafo == NULL) return;
  enfileirado = (int*) malloc(sizeof(int)*grafo->nv);
  assert(enfileirado);
  for (no=0;no<(grafo->nv);no++) enfileirado[no] = 0;
  q = enqueue (q, no_inicial);
  enfileirado[no_inicial] = 1;
  q = pop(q, &no);
  while (no>=0) {
    printf ("%d-", no);
    v = grafo->viz[no];
    while (v!=NULL) {
      if (!enfileirado[(v->noj)]) {
        q = enqueue (q, v->noj);
        enfileirado[v->noj] = 1;
      }
      v = v->prox;
    }
    q=pop(q, &no);
  }
 printf ("\n");
} 
  
Grafo* arvoreCustoMinimo (char *filename) {
  int nv, na, no1, no2;
  int peso;
  int arestasSelecionadas;
  Grafo* novo;
  ListaP* lstPArestas;
  UniaoBusca* ubSubFlorestas;
  FILE *arq = fopen(filename,"rt");
	assert(arq);
	
  fscanf(arq, "%d %d", &nv, &na);
  lstPArestas = listap_cria(na);
  assert(lstPArestas);
  
  while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
    listap_insere(lstPArestas,peso,no1,no2);
  }
  fclose(arq);
  
  novo = grafoCria(nv,nv-1);
  
  arestasSelecionadas = 0;
  ubSubFlorestas = ub_cria(nv);
  assert(ubSubFlorestas);
  
  while (arestasSelecionadas < nv-1) {
  	if ((peso = listap_remove(lstPArestas,&no1,&no2)) == -1)
  		{printf("Erro: inconsistencia\n");	exit(1);}
		if (ub_busca(ubSubFlorestas,no1) != ub_busca(ubSubFlorestas,no2)) {
			ub_uniao(ubSubFlorestas,no1,no2);
			novo->viz[no1] = criaViz(novo->viz[no1],no2,peso);
			novo->viz[no2] = criaViz(novo->viz[no2],no1,peso);
			arestasSelecionadas++;
		}
  }
  
  ub_libera(ubSubFlorestas);
  listap_libera(lstPArestas);
  
  return novo;
}

int tem_ciclo (char *filename) {
	int nv, na, no1, no2, peso;
	UniaoBusca* ubComponentesConexas;
	FILE *arq = fopen(filename,"rt");
	assert(arq);
	fscanf(arq, "%d %d", &nv, &na);
	
	if (na >= nv) {/* Considerei que um multigrafo sempre possui ciclos */
		fclose(arq);
		return 1;
	}
	
	ubComponentesConexas = ub_cria(nv);
	assert(ubComponentesConexas);
	
	while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
    if (ub_busca(ubComponentesConexas,no1) == ub_busca(ubComponentesConexas,no2)) { /* No1 e No2 estão no mesmo componente conexo */
    	fclose(arq);
    	ub_libera(ubComponentesConexas);
    	return 1;
    }
    ub_uniao(ubComponentesConexas,no1,no2);
  }
  fclose(arq);
  ub_libera(ubComponentesConexas);
  return 0;
}

/* Decidi não fazer uma busca linear em cada nó na ub ao final pois tomaria muito tempo */
int num_componentes (char *filename) {
	int nv, na, no1, no2, peso, numComp;
	UniaoBusca* ubComponentesConexas;
	FILE *arq = fopen(filename,"rt");
	assert(arq);
	
	fscanf(arq, "%d %d", &nv, &na);
	
	ubComponentesConexas = ub_cria(nv);
	assert(ubComponentesConexas);
	
	/* Inicialmente a partição é o mais fragmentada possível (nós ainda desconexos) */
	numComp = nv; /* Número inicial de componentes conexas */
	
	while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
		if (ub_busca(ubComponentesConexas,no1) != ub_busca(ubComponentesConexas,no2)) { /* No1 e No2 serão juntados no mesmo componente conexo */
			ub_uniao(ubComponentesConexas,no1,no2);
			numComp--; /* Número total de componentes diminui em 1 */
		} /* Caso no1 e no2 já estejam no mesmo componente, nada muda */
  }
  
  fclose(arq);
  ub_libera(ubComponentesConexas);
  return numComp;
}

/* Decidi não fazer uma busca linear em cada nó na ub ao final pois tomaria muito tempo */
int nv_maior_componente (char *filename) {
	int nv, na, no1, no2, peso, maiorComp, i;
	int* qtdElemsComponentes;
	UniaoBusca* ubComponentesConexas;
	FILE *arq = fopen(filename,"rt");
	assert(arq);
	
	fscanf(arq, "%d %d", &nv, &na);
	
	ubComponentesConexas = ub_cria(nv);
	assert(ubComponentesConexas);
	
	/* Se o representante na ub de uma componente conexa é o nó k, então
	qtdElemsComponentes[k] é a quantidade de elementos nessa componente.
	Se o nó j não é representante de nenhuma componente, então
	qtdElemsComponentes[j] contém lixo. */
	qtdElemsComponentes = (int*) malloc(nv*sizeof(int));
	assert(qtdElemsComponentes);
	
	/* Inicialmente a partição é o mais fragmentada possível (nós ainda desconexos) */
	maiorComp = 1; /* Número de elementos da maior componente conexa */
	for (i = 0; i < nv; i++)
		qtdElemsComponentes[i] = 1;
	
	while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
		int representanteComp1 = ub_busca(ubComponentesConexas,no1);
		int representanteComp2 = ub_busca(ubComponentesConexas,no2);
		if (representanteComp1 != representanteComp2) { /* No1 e No2 serão juntados no mesmo componente conexo */
			int novoRepresentante;
			ub_uniao(ubComponentesConexas,no1,no2);
			novoRepresentante = ub_busca(ubComponentesConexas,no1);
			qtdElemsComponentes[novoRepresentante] = qtdElemsComponentes[representanteComp1] + qtdElemsComponentes[representanteComp2];
			if (qtdElemsComponentes[novoRepresentante] > maiorComp)
				maiorComp = qtdElemsComponentes[novoRepresentante];
		} /* Caso no1 e no2 já estejam no mesmo componente, nada muda */
  }
  
  fclose(arq);
  ub_libera(ubComponentesConexas);
  free(qtdElemsComponentes);
  return maiorComp;
}
