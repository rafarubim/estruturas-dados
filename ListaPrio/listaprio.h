typedef struct _listaprio ListaP;


int *cria_listaordenada (ListaP *lp, int* tam);
/* cria nova lista de prioridades, opcionalmente passando uma lista inicial de prios */
ListaP *listap_cria (int max, int qtos, int* iniciais);

/* insere uma nova prioridade na lista */
void listap_insere (ListaP *lp, int prioridade); 

/* remove e retorna a maior prioridade */
int listap_remove(ListaP *lp);

/* libera a lista de prioridades */
void listap_libera(ListaP *lp);

/* só para debug: enxerga representação interna! */
void debug_listap_show (ListaP *hp, char* title);


