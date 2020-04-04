#include "mapa.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct smapa {

	int chave;
	int info;
	Mapa* esq;
	Mapa* dir;
	short fb;
};

typedef enum eDirec {ESQUERDA, DIREITA} Direc;

Mapa* m_cria (void) {
	return NULL;
}

Mapa* m_criaNo(int chave, int info) {
	Mapa* novo = (Mapa*)malloc(sizeof(Mapa));
	if (novo == NULL) {printf("Erro: falha de memória\n");	exit(1);}
	novo->chave = chave;
	novo->info = info;
	novo->esq = novo->dir = NULL;
	novo->fb = 0;
	return novo;
}

Mapa* m_balanceia(Mapa* m) {

	if (m->fb > 0) {
		Mapa *dir, *dirEsq;
		int velhoMFb;

		if (m->dir->fb < 0)
			m->dir = m_balanceia(m->dir);

		dir = m->dir;
		dirEsq = m->dir->esq;
		velhoMFb = m->fb;

		m->dir->esq = m;
		m->dir = dirEsq;

		/*Novo fator de balanceamento do novo elemento à esquerda:*/  //(Os casos seguintes são os únicos possíveis)
		if (m->fb == 2 || dir->fb == 0) /*O segundo caso do "ou" considera m->fb == 1 e dir->fb == 1 (Não há o caso dir->fb == -1 pois ele haveria sido balanceado antes recursivamente)*/
			m->fb = 0;
		else // m->fb == 1 && dir->fb == 1
			m->fb = -1;

		/*Novo fator de balanceamento do novo elemento acima:*/
		dir->fb = velhoMFb - 2; // O balanceamento à esquerda diminui o fator em 2

		m = dir;
	} else if (m->fb < 0) {
		Mapa *esq, *esqDir;
		int velhoMFb;

		if (m->esq->fb > 0)
			m->esq = m_balanceia(m->esq);

		esq = m->esq;
		esqDir = m->esq->dir;
		velhoMFb = m->fb;

		m->esq->dir = m;
		m->esq = esqDir;

		/*Novo fator de balanceamento do novo elemento à direita:*/  //(Os casos seguintes são os únicos possíveis)
		if (m->fb == -2 || esq->fb == 0) /*O segundo caso do "ou" considera m->fb == 1 e esq->fb == -1 (Não há o caso esq->fb == 1 pois ele haveria sido balanceado antes recursivamente)*/
			m->fb = 0;
		else // m->fb == 1 && esq->fb == -1
			m->fb = 1;

		/*Novo fator de balanceamento do novo elemento acima:*/
		esq->fb = velhoMFb + 2; // O balanceamento à direita aumenta o fator em 2

		m = esq;
	}
	return m;
}

Mapa* m_insere2 (Mapa* m, int chave, int info, int* flag) {

	if (m == NULL) {
		m = m_criaNo(chave, info);
		*flag = 1;
	} else if (chave < m->chave) {
		m->esq = m_insere2(m->esq, chave, info, flag);
		if (*flag)
			switch(m->fb) {
			case 1:
				m->fb = 0;	*flag = 0;	break;
			case 0:
				m->fb = -1;	break;
			case -1:
				m->fb = -2;	m = m_balanceia(m);	*flag = 0;	break;
			}
	} else if (m->chave < chave) {
		m->dir = m_insere2(m->dir, chave, info, flag);
		if (*flag)
			switch(m->fb) {
			case -1:
				m->fb = 0;	*flag = 0;	break;
			case 0:
				m->fb = 1;	break;
			case 1:
				m->fb = 2;	m = m_balanceia(m);	*flag = 0;	break;
			}
	}
	return m;
}

Mapa* m_insere (Mapa* m, int chave, int info) {

	int flag = 0;
	return m_insere2(m, chave, info, &flag);
}

Mapa* m_buscaNo(Mapa* m, Mapa** noAnterior, Direc* dirAnterior, int chave) { //m é o mapa onde o nó é buscado, noAnterior é um ponteiro para a variável onde deseja-se guardar o nó anterior ao encontrado, dirAnterior diz se o nó encontrado estava à ESQUERDA ou à DIREITA do anterior

	*noAnterior = NULL;
	*dirAnterior = ESQUERDA;

	while(m != NULL) {

		if (chave < m->chave) {
			*noAnterior = m;
			*dirAnterior = ESQUERDA;
			m = m->esq;
		} else if (chave > m->chave) {
			*noAnterior = m; 
			*dirAnterior = DIREITA;
			m = m->dir;
		} else
			break;
	}

	return m;
}

int m_busca (Mapa *m, int chave) {

	Mapa* ant;// Ambas as variáveis são criadas apenas para chamar a funçao buscaNo
	Direc dir;

	m = m_buscaNo(m, &ant, &dir, chave);

	if (m != NULL)
		return m->info;
	else
		return INT_MAX;
}

Mapa* m_remove (Mapa* m, int chave) {

	Mapa *raiz = m, *anterior;
	Direc dir;

	m = m_buscaNo(m, &anterior, &dir, chave); // m é o nó a ser retirado. anterior é o nó anterior e dir diz se M está à ESQUERDA ou DIREITA de seu anterior

	if (m == NULL) {
		printf("Aviso: no a ser retirado nao encontrado. Nenhum no foi removido\n");
		return raiz;
	}

	if (m->esq != NULL && m->dir != NULL) { //Caso em que m possui duas sub-árvores <<<<<<<<<<<<<<<< fazer caso em que m == raiz

		Mapa *temp = m->dir; //temp inicia como não-nulo de certeza

		Mapa *tempAnterior = NULL;

		while(temp->esq != NULL) { //Caminha mais à esquerda possível com temp, até o elemento subsequente
			tempAnterior = temp; 
			temp = temp->esq;
		}

		if (anterior == NULL) { //Caso em que m == raiz
			raiz = temp;
		} else if (dir == ESQUERDA)
			anterior->esq = temp;
		else
			anterior->dir = temp;
		
		temp->esq = m->esq;

		if (tempAnterior != NULL) {
			tempAnterior->esq = temp->dir; //Remenda a sub-árvore antes de "tirar" elemento subsequente. Só acontecerá se o elemento subsequente não for a raíz da sub-árvore. Se for, ele pode continuar apontando para o mesmo elemento à sua direita.
			temp->dir = m->dir;
		}

	} else if (m->esq != NULL) {
		if (anterior == NULL) //Caso em que m == raiz
			raiz = m->esq;
		else if (dir == ESQUERDA)
			anterior->esq = m->esq;
		else
			anterior->dir = m->esq;
	} else {
		if (anterior == NULL) //Caso em que m == raiz
			raiz = m->dir;
		else if (dir == ESQUERDA)
			anterior->esq = m->dir;
		else
			anterior->dir = m->dir;
	}

	free(m); // M PODE REALMENTE SER LIBERADO? POOODEEE

	return raiz;
}

void m_destroi (Mapa *m) {

	if (m == NULL)
		return;

	m_destroi(m->esq);
	m_destroi(m->dir);

	free(m);
}


void m_debugMostraMapa(Mapa* map) {

	if (map == NULL)
		return;

	printf("%d(", map->chave);

	m_debugMostraMapa(map->esq);
	printf(",");
	m_debugMostraMapa(map->dir);

	printf(")");
}