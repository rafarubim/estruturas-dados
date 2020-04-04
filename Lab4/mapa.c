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
	if (novo == NULL) {printf("Erro: falha de mem�ria\n");	exit(1);}
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

		/*Novo fator de balanceamento do novo elemento � esquerda:*/  //(Os casos seguintes s�o os �nicos poss�veis)
		if (m->fb == 2 || dir->fb == 0) /*O segundo caso do "ou" considera m->fb == 1 e dir->fb == 1 (N�o h� o caso dir->fb == -1 pois ele haveria sido balanceado antes recursivamente)*/
			m->fb = 0;
		else // m->fb == 1 && dir->fb == 1
			m->fb = -1;

		/*Novo fator de balanceamento do novo elemento acima:*/
		dir->fb = velhoMFb - 2; // O balanceamento � esquerda diminui o fator em 2

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

		/*Novo fator de balanceamento do novo elemento � direita:*/  //(Os casos seguintes s�o os �nicos poss�veis)
		if (m->fb == -2 || esq->fb == 0) /*O segundo caso do "ou" considera m->fb == 1 e esq->fb == -1 (N�o h� o caso esq->fb == 1 pois ele haveria sido balanceado antes recursivamente)*/
			m->fb = 0;
		else // m->fb == 1 && esq->fb == -1
			m->fb = 1;

		/*Novo fator de balanceamento do novo elemento acima:*/
		esq->fb = velhoMFb + 2; // O balanceamento � direita aumenta o fator em 2

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

Mapa* m_buscaNo(Mapa* m, Mapa** noAnterior, Direc* dirAnterior, int chave) { //m � o mapa onde o n� � buscado, noAnterior � um ponteiro para a vari�vel onde deseja-se guardar o n� anterior ao encontrado, dirAnterior diz se o n� encontrado estava � ESQUERDA ou � DIREITA do anterior

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

	Mapa* ant;// Ambas as vari�veis s�o criadas apenas para chamar a fun�ao buscaNo
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

	m = m_buscaNo(m, &anterior, &dir, chave); // m � o n� a ser retirado. anterior � o n� anterior e dir diz se M est� � ESQUERDA ou DIREITA de seu anterior

	if (m == NULL) {
		printf("Aviso: no a ser retirado nao encontrado. Nenhum no foi removido\n");
		return raiz;
	}

	if (m->esq != NULL && m->dir != NULL) { //Caso em que m possui duas sub-�rvores <<<<<<<<<<<<<<<< fazer caso em que m == raiz

		Mapa *temp = m->dir; //temp inicia como n�o-nulo de certeza

		Mapa *tempAnterior = NULL;

		while(temp->esq != NULL) { //Caminha mais � esquerda poss�vel com temp, at� o elemento subsequente
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
			tempAnterior->esq = temp->dir; //Remenda a sub-�rvore antes de "tirar" elemento subsequente. S� acontecer� se o elemento subsequente n�o for a ra�z da sub-�rvore. Se for, ele pode continuar apontando para o mesmo elemento � sua direita.
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