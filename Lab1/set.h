typedef unsigned int Set;

/* cria um conjunto com n elementos */
Set* setCreate(void);

/* destroi (desaloca) o conjunto */
Set* setDestroy(Set* set);

/* insere o elemento i no conjunto */
void setInsert(Set *set, int i);

/* remove o elemento i do conjunto */
void setRemove(Set *set, int i);

/* cria uma copia do conjunto */
Set* setCopy(Set* set);

/* cria o complemento de conjunto */
Set* setComplement(Set* set);

/* cria a uniao de dois conjunto que podem ter tamanhos diferentes */
/* naturalmente o numero de elementos do universo e' o do maior dos dois */
Set* setUnion( Set *set1,  Set *set2);

/* calcula a intersecao de dois conjuntos, a cardinalidade e' a do menor */
Set* setIntersection( Set *set1,  Set *set2);

/* calcula a diferenca de set1-set2. a cardinalidade e'a de set1. */
Set* setDifference(Set *set1, Set *set2);

/* verifica se o elemento i pertence ao conjunto */
int setIsMember( Set *set, int i);

/* verifica de set2 e' um sub conjunto de set1 */
int setIsSubset( Set *set1,  Set *set2);

/* verifica se dois conjuntos sao iguais */
int setIsEqual( Set *set1,  Set *set2);

/* informa a cardilaidade do conjunto */
int setNumberOfElements(Set* set);

/* mostra os elementos do conjunto */
void setShow(char* title, Set* set);
