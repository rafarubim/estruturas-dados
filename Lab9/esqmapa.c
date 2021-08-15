
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "mapa.h"

struct smapa
{
	int  kp, kg;   /* chaves: kp<kg, se kg existir. Se kg=-1, significa que ele não existe. */
	Mapa  *pai;
	Mapa  *esq;
	Mapa  *meio;
	Mapa  *dir;
};

Mapa* cria (void) {
  return NULL;
}

Mapa* novoNo (int chave) {
  Mapa *m = (Mapa*) malloc(sizeof(struct smapa));
  if (m==NULL) { printf ("erro no malloc! \n"); exit(1);}
  m->kp = chave; 
  m->kg = -1;
  m->esq = m->meio = m->dir = NULL;
  return m;
}

Mapa* overflowQuebra (Mapa *m, int *valorainserir, Mapa* novofilho) {
/* quebra o nó m em dois, cada um com uma chave                    */
/* entrada:                                                        */
/* m é nó com 2 chaves                                             */
/* *valorainserir é a nova chave                                   */
/* novofilho é subárvore que deve entrar à esquerda da nova chave  */
/* saída:                                                          */
/* retorno é o novo nó criado                                      */
/* *valorainserir é a mediana que tem que "subir"                  */

  Mapa* novo;

  novo = (Mapa*) malloc(sizeof(struct smapa));
  if (novo==NULL) { printf ("erro no malloc! \n"); exit(1);}

  /* COMPLETAR */

  return novo;
}

int insere2 (Mapa* m, int chave, int* valorainserir, Mapa** novofilho) {

  int inseriraqui = 0; /* indica se deve inserir neste nó */

  if (m==NULL) {
    printf("erro! subárvore nula! \n"); exit (1);
  }

  if (m->esq != NULL) { /* não é folha, só insere neste nó se chamada recursiva retornar mediana  */
    if (chave < m->kp) {
      inseriraqui = insere2(m->esq, chave, valorainserir, novofilho); 
    }
    else if (((m->kg != -1) && (chave < m->kg)) || (m->kg == -1)) {
      /* ou está entre as duas chaves ou só tem uma chave no nó */
      inseriraqui = insere2(m->meio, chave, valorainserir, novofilho);
    }
    else { /* chave > m->kg */
      inseriraqui = insere2(m->dir, chave, valorainserir, novofilho);
    }
  }
  else { /* este nó é folha, tem que inserir nele de qq jeito */
    *valorainserir = chave;
    inseriraqui = 1;
    *novofilho = NULL; /* neste caso novo item não tem uma subarvore associada */
  } 

  if (!inseriraqui) return 0; /* inserção já está completa */

  if (m->kg==-1) {
  /* tem  espaço no nó */
  /* COMPLETAR */
    return 0; /* como havia espaço, não sobem valores a serem inseridos */
  }

  *novofilho = overflowQuebra (m, valorainserir, *novofilho); 

  return 1; /* quando há quebra sempre sobe a mediana para nova inserção */ 
}

Mapa* insere (Mapa* m, int chave) {
  int valorquesubiu;
  Mapa* novofilho;
  Mapa* novaraiz;
  if (m==NULL) {
    m = novoNo (chave);
  }
  else {
    if (insere2 (m, chave, &valorquesubiu, &novofilho)) {
      /* cria nova raiz */
      novaraiz = novoNo (valorquesubiu);
      novaraiz->esq = novofilho;
      novaraiz->meio = m;
      m = novaraiz;
    } 
  }

  return m;
}


int busca (Mapa *m, int chave) {
  return 0;
}
Mapa* retira (Mapa *m, int chave) {
  return m;
}

void destroi (Mapa *m) {
  if (m!= NULL) {
    destroi (m->esq);
    destroi (m->meio);
    destroi (m->dir);
    free (m);
  }
}

void debug_mostra_mapa_int  (Mapa *m) {
  printf ("[");
  if (m!= NULL) {
    printf ("%d:%d ", m->kp, m->kg);
    debug_mostra_mapa_int (m->esq);
    debug_mostra_mapa_int (m->meio);
    if (m->kg != -1) debug_mostra_mapa_int(m->dir);
  }
  printf ("]");
}

void debug_mostra_mapa  (Mapa *m) {
  debug_mostra_mapa_int (m);
  printf("\n");
}
