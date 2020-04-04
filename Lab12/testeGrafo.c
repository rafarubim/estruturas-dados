#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
		
	Grafo* grafoDoRafa;
	int* minimos;
	int i, inicial = 5;
	
	grafoDoRafa = grafoLe("grafo1.dat");
	
	grafoMostra("Olha que grafo lindo",grafoDoRafa);

	minimos = menoresCaminhos(grafoDoRafa, inicial);
	
	printf("Distancias do no %d: ", inicial);
	for (i = 0; minimos[i] != -1; i++)
		printf("%d, ", minimos[i]);
	puts("");
	
	free(minimos);
	grafoDoRafa = grafoLibera(grafoDoRafa);
	
	return 0;
}
