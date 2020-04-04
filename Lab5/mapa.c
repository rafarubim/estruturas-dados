#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"

struct smapa {
  int chave;
  int conteudo;
  short int bf;
  int lsize;
  struct smapa* esq;
  struct smapa* dir;
};

static Mapa* cria_no(int c, int novodado);
static Mapa* insere2(Mapa *m, int chave, int novodado, int *flag);
static Mapa* verifica_dir(Mapa *m);
static Mapa* verifica_esq(Mapa *m);
static Mapa* rotaciona_dir(Mapa *m);
static Mapa* rotaciona_esq(Mapa *m);

static Mapa* cria_no(int c, int novodado) {
  Mapa *m = (Mapa*)malloc(sizeof(Mapa));
  if (m != NULL) {
    m->esq = m->dir = NULL;
    m->chave = c;
    m->conteudo = novodado;
    m->bf = 0;
    m->lsize = 0;
  }
  return m;
}

Mapa* cria() {
  return NULL;
}

Mapa* insere (Mapa* m, int chave, int novodado) {
  int flag = 0;
  return insere2(m, chave, novodado, &flag);
}

int numNos(Mapa *m) {
	if (m == NULL)
		return 0;
	return 1 + m->lsize + numNos(m->dir);
}

static Mapa* insere2(Mapa *m, int chave, int novodado, int *flag) {
  if (m == NULL) {
    m = cria_no(chave, novodado);
    *flag = 1;
  }
  else if (chave < m->chave) {
    m->lsize += 1;
    m->esq = insere2(m->esq, chave, novodado, flag);
    if (*flag) {
      switch (m->bf) {
      case 1:
        m->bf = 0;
        *flag = 0;
        break;
      case 0:
        m->bf = -1;
        break;
      case -1:
        *flag = 0;
        m = verifica_esq(m);
        break;
      }
    }
  }
  else if (chave > m->chave) {
    m->dir = insere2(m->dir, chave, novodado, flag);
    if(*flag) {
      switch (m->bf) {
      case 1:
        m = verifica_dir(m);
        *flag = 0;
        break;
      case 0:
        m->bf = 1;
        break;
      case -1:
        m->bf = 0;
        *flag = 0;
        break;
      }
    }
  }
  return m;
}

static Mapa* verifica_esq(Mapa *m) {
  if (m->esq->bf == -1) {
    m->bf = m->esq->bf = 0;
    return rotaciona_dir(m);
  }
  else /* if (m->esq->bf == 1) */ {
    Mapa *n = m->esq->dir;
    switch (n->bf) {
    case  -1:
      m->bf = 1;
      m->esq->bf = 0;
      break;
    case 0:
      m->bf = m->esq->bf = 0;
      break;
    case 1:
      m->bf = 0;
      m->esq->bf = -1;
      break;
    }
    n->bf = 0;
    m->esq = rotaciona_esq(m->esq);
    return rotaciona_dir(m);
  }
  return NULL;
}


static Mapa* verifica_dir(Mapa *m) {
  if (m->dir->bf == 1) {
    m->bf = m->dir->bf = 0;
    return rotaciona_esq(m);
  }
  else/* if (m->dir->bf == -1) */ {
    Mapa *n = m->dir->esq;
    switch (n->bf) {
    case  1:
      m->bf = -1;
      m->dir->bf = 0;
      break;
    case 0:
      m->bf = m->dir->bf = 0;
      break;
    case -11:
      m->bf = 0;
      m->dir->bf = 1;
      break;
    }
    n->bf = 0;
    m->dir = rotaciona_dir(m->dir);
    return rotaciona_esq(m);
  }
  return NULL;
}

static Mapa* rotaciona_dir(Mapa *m) {
  Mapa* esq = m->esq;
  m->esq = esq->dir;
  m->lsize = numNos(esq->dir);
  esq->dir = m;
  return esq;
}

static Mapa* rotaciona_esq(Mapa *m) {
  Mapa* dir = m->dir;
  m->dir = dir->esq;
  dir->esq = m;
  dir->lsize = numNos(m);
  return dir;
}

int busca (Mapa *m, int chave) {
  if (m == NULL) {
    return INT_MAX;
  }
  else if (m->chave == chave) {
    return m->conteudo;
  }
  else if (chave < m->chave) {
  return busca(m->esq, chave);
  }
  else if (chave > m->chave) {
    return busca(m->dir, chave);
  }
  else {
    return INT_MAX;
  }
}

void destroi (Mapa *m) {
  if (m != NULL) {
    destroi(m->esq);
    destroi(m->dir);
    free(m);
  }
}

void debug_mostra_mapa_int (Mapa* m) {

  if (m != NULL) {
    printf("%d-%d-%d", m->chave,m->bf,m->lsize);
    printf("(");
    debug_mostra_mapa_int(m->esq);
    printf(",");
    debug_mostra_mapa_int(m->dir);
    printf(")");
  } else
    printf("*");
}

int debug_altura (Mapa *m) {
	if (m == NULL)
		return -1;
	if (m->bf > 0)
		return 1 + debug_altura(m->dir);
	else
		return 1 + debug_altura(m->esq);
}

void debug_mostra_mapa (Mapa* m) {
  debug_mostra_mapa_int (m); printf ("\n");
}

void lista_todos_int (Mapa *m) {
	if (m == NULL)
		return;
	lista_todos_int(m->esq);
	printf("%d,", m->chave);
	lista_todos_int(m->dir);
}

void lista_todos (Mapa *m) {
	printf("{");	lista_todos_int(m);	printf("}\n");
}



