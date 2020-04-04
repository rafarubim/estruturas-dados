#include "grafo.h"

int main() {
		
	Grafo* grafoDoRafa,* grafoSemCiclos;
	
	grafoDoRafa = grafoLe("grafo1.dat");
	
	grafoMostra("Olha que grafo lindo",grafoDoRafa);

	grafoPercorreProfundidade(grafoDoRafa, 0);

	grafoSemCiclos = criaArvoreGeradora(grafoDoRafa, 0);
	
	grafoMostra("\nOlha que grafo lindo sem ciclos", grafoSemCiclos);
	
	grafoPercorreProfundidade(grafoSemCiclos, 0);
	
	grafoDoRafa = grafoLibera(grafoDoRafa);
	grafoSemCiclos = grafoLibera(grafoSemCiclos);
	
	return 0;
}
