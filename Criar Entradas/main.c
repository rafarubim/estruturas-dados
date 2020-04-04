#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int main() {

	int i;
	FILE *arq = fopen("entradas.txt", "wt");
	if (!arq) {printf("Deu merda\n\n");	exit(1);}

	fprintf(arq, "%d\n", MAX);
	for (i = 0; i < MAX; i++)
		fprintf(arq, "%d\n", i);

	fclose(arq);

	return 0;
}