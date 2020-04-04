#include <limits.h>
#include "mapa.h"
#include <stdio.h>
#include <time.h>

#define TAM 1000000

clock_t startTime;

Mapa* preenche (Mapa* m, int inicio, int fim) {
/* para usar no programa teste com: preenche(meumapa2, 0, TAM) */
  int meio;
  if (inicio>fim) return m;
  meio = (fim+inicio)/2;
  m = m_insere (m, meio, meio*2);
  m = preenche (m, inicio, meio-1);
  m = preenche (m, meio+1, fim);
  return m;
}

void startCount() {
	startTime = clock();
}

void endCount() {
	printf("A operacao anterior durou %ld milisegundos.\n\n", (clock() - startTime));
}

int main() {

	int i;
	Mapa *meuMapa1 = m_cria(), *meuMapa2 = m_cria();

	
	for (i = 0; i < TAM; i++)
		meuMapa1 = m_insere(meuMapa1, i, 2*i);
	

	meuMapa2 = preenche(meuMapa2, 0, TAM);

	if (TAM <= 20) {
		printf("Meu mapa 1: ");
		m_debugMostraMapa(meuMapa1);
		printf("\n\n");
	}

	if (TAM <= 20) {
		printf("Meu mapa 2: ");
		m_debugMostraMapa(meuMapa2);
		printf("\n\n");
	}

	printf("Realizando busca no mapa 1\n\n");

	startCount();
		m_busca(meuMapa1, TAM-1);
	endCount();

	printf("Realizando busca no mapa 2\n\n");

	startCount();
		m_busca(meuMapa2, TAM-1);
	endCount();

	/*printf("Realizando remocao no mapa 1\n\n");

	startCount();
		m_remove(meuMapa1, TAM/2);
	endCount();

	printf("Realizando remocao no mapa 2\n\n");

	startCount();
		m_remove(meuMapa2, TAM/2);
	endCount();

	printf("Realizando apagamento do mapa 1\n\n");

	startCount();
		m_destroi(meuMapa1);
	endCount();

	printf("Realizando apagamento do mapa 2\n\n");

	startCount();
		m_destroi(meuMapa2);
	endCount();*/

	return 0;
}
