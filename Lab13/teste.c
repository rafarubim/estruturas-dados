#include "grafo.h"
#include <stdio.h>

void grafoTemLoop(const char* nomeGrafo, char* pathGrafo) {
	if (tem_ciclo(pathGrafo))
		printf("Grafo %s tem ciclo!!!\n", nomeGrafo);
	else
		printf("Grafo %s nao tem ciclos!!!\n", nomeGrafo);
}

void grafoQtdComponentes(const char* nomeGrafo, char* pathGrafo) {
	int qtd;
	qtd = num_componentes(pathGrafo);
	printf("Grafo %s tem %d componentes conexas!\n", nomeGrafo, qtd);
}

void grafoMaiorComponente(const char* nomeGrafo, char* pathGrafo) {
	int num;
	num = nv_maior_componente(pathGrafo);
	printf("Grafo %s tem maior componente com %d vertices!\n", nomeGrafo, num);
}

int main() {
	Grafo* g1,* g1CustoMin,* g2,* g2CustoMin;
	char pathG1[] = "grafo1.dat";
	char pathG2[] = "grafo2.dat";
	/* Arquivos que criei após rodar arvoreCustoMinimo: */
	char pathG1pequeno[] = "grafo1pequeno.dat";
	char pathG2pequeno[] = "grafo2pequeno.dat";
	
	g1 = grafoLe(pathG1);
	g1CustoMin = arvoreCustoMinimo(pathG1);
	g2 = grafoLe(pathG2);
	g2CustoMin = arvoreCustoMinimo(pathG2);
	
	puts("G1:");
	grafoMostra(g1);
	grafoTemLoop("G1", pathG1);
	grafoQtdComponentes("G1", pathG1);
	grafoMaiorComponente("G1", pathG1);

	puts("\nG1 PEQUENO:");
	grafoMostra(g1CustoMin);
	grafoTemLoop("G1 PEQUENO", pathG1pequeno);
	grafoQtdComponentes("G1 PEQUENO", pathG1pequeno);
	grafoMaiorComponente("G1 PEQUENO", pathG1pequeno);
	
	puts("\nG2:");
	grafoMostra(g2);
	grafoTemLoop("G2", pathG2);
	grafoQtdComponentes("G2", pathG2);
	grafoMaiorComponente("G2", pathG2);
	
	puts("\nG2 PEQUENO:");
	grafoMostra(g2CustoMin);
	grafoTemLoop("G2 PEQUENO", pathG2pequeno);
	grafoQtdComponentes("G2 PEQUENO", pathG2pequeno);
	grafoMaiorComponente("G2 PEQUENO", pathG2pequeno);
	
	puts("");
	grafoQtdComponentes("GRAFO DESCONEXO DO RAFA", "grafoDesconexo.dat"); /* Grafo que fiz para teste */
	grafoMaiorComponente("GRAFO DESCONEXO DO RAFA", "grafoDesconexo.dat");
	
	return 0;
}
