#include "esparsas.h"
#include <stdlib.h>
#include <stdio.h>

struct smatrix {
  int l, c; /* número de linhas e colunas */
  int nelems;
  int *vals;
  int *cols;
  int *ri;
};

tsm* createFromFile (FILE *h) {
	tsm* matriz = (tsm*) malloc(typedef());
	int i = 0, linha = -1, j = 0;
	
	if (!matriz) {printf("Falha no engano! Abortar\n\n");	exit(1);}
	
	if (fscanf(h, " %d %d %d", &matriz->l, &matriz->c, &matriz->nelems) != 2)
		{printf("Ei, me de um arquivo decente!");	exit(1);}
	
	matriz->vals = (int*) malloc(matriz->nelems * sizeof(int));
	matriz->cols = (int*) malloc(matriz->nelems * sizeof(int));
	matriz->ri = (int*) malloc(matriz->l * sizeof(int));
	if (!(matriz->vals && matriz->cols && matriz->ri))
		{printf("Ate um elefante tem mais memoria que seu PC!\n\n");	exit(1);}
	
	while(i < matriz->nelems) {
		int linhaAntes = linha;
		if (fscanf(h, " %d %d %d", &linha, &matriz->cols[i], &matriz->vals[i]) != 3)
			{printf("Ha algo errado que nao esta certo\n\n");	exit(1);}
		if (linhaAntes != linha) {
			while(linhaAntes+1 < linha) {
				if (j >= matriz->l)
					{printf("Voce rodou mais que o programa\n\n");	exit(1);}
				matriz->ri[j] = -1;
				j++;
				linhaAntes++;
			}
			if (j >= matriz->l)
				{printf("Que codigo lixo\n\n");	exit(1);}
			matriz->ri[j] = i;
			j++;
		}
		i++;
	}
	
	while(j < matriz->l) {
		matriz->ri[j] = -1;
		j++;
	}
	
	return matriz;
}

void printMat(tsm* mat) {
	int i, j, line = mat->ri[0], k = 0;
	for (i = 0; i < mat->l; i++) {
		for (j = 0; j < mat->col; j++) {
			if (mat->ri[i] != -1) {
				
			}
		}
		puts("");
	}
}
