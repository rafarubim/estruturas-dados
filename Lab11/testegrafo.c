#include "grafo.h"
#include <stdio.h>

int main(int argc, char** argv) {
	
	Grafo* grafoDoRafa;
	
	if (argc != 2) { printf("Uso do programa: %s -path\n\n", argv[0]);	return 1; }
	
	grafoDoRafa = grafoLe(argv[1]);
	
	grafoMostra("Olha que grafo incrivel",grafoDoRafa);
	
	while(1) {
		int no_inicial;
		printf("\nRapido, me de um no inicial (-1 termina): ");
		scanf(" %d", &no_inicial);
		if (no_inicial == -1)
			break;
		grafoPercorreLargura(grafoDoRafa, no_inicial);
	};
	
	grafoDoRafa = grafoLibera(grafoDoRafa);
	
	return 0;
}
