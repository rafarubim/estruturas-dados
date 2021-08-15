#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

void quebraAbstracao2(Mapa *m) {
	if (m->esq)
		quebraAbstracao2(m->esq);
	if (m->kp != -1)
		printf ("- %d ", m->kp);
	if (m->meio)
		quebraAbstracao2(m->meio);
	if (m->kg != -1)
		printf ("- %d ", m->kg);
	if (m->dir)
		quebraAbstracao2(m->dir);
}

void quebraAbstracao(Mapa *m) {
	printf("Milagre ");
	quebraAbstracao2(m);
	printf("- Fim do milagre\n");
}

int main(int argc, char** argv) {

    int i;
    int tam;

    if (argc<2) {printf ("uso: %s <qtos_inserir>\n", argv[0]); exit(1);}
    tam = atoi(argv[1]);

    Mapa *mapa1 = cria();
    Mapa *mapa2 = cria();
    Mapa *mapa3 = cria();

    printf ("inserÃ§Ã£o sempre Ã  esquerda:\n");
    for (i=tam-1;i>=0;i--) {
       mapa1 = insere (mapa1, i);
    }
    debug_mostra_mapa(mapa1);
    quebraAbstracao(mapa1);

    printf ("inserÃ§Ã£o sempre Ã  direita:\n");
    for (i=0;i<tam;i++) {
       mapa2 = insere (mapa2, i);
    }
    debug_mostra_mapa(mapa2);
    quebraAbstracao(mapa2);

    printf ("inserÃ§Ã£o variada:\n");
    for (i=0;i<2*tam;i++) {
      mapa3 = (i%2)?insere (mapa3, 2*tam-i):insere(mapa3,i);
    }
    debug_mostra_mapa(mapa3);
    quebraAbstracao(mapa3);
       
    destroi (mapa1);
    destroi (mapa2);
    destroi (mapa3);

    return 0;
}
