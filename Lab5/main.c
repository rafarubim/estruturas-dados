#include "mapa.h"
#include <stdio.h>

int pot2(int pot) {
	if (pot > 0)
		return 2 * pot2(pot-1);
	else
		return 1;
}

int main() {
	int i;
	Mapa* m = cria();

	for(i = 0; i <= 15; i++)
		m = insere(m, i, i*i);

	debug_mostra_mapa(m);
	printf("Altura: %d\n", debug_altura(m));

	for(i = 4; i <= 19; i++) {
		m = insere(m, pot2(i), i*i);
		//printf("Altura: %d\n", debug_altura(m));
	}
	debug_mostra_mapa(m);
	lista_todos(m);
	
	return 0;
}
