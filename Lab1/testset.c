#include <stdio.h>
#include "set.h"

int main()
{
	Set* s1 = setCreate();
	Set* s2 = setCreate();
	Set *uniao, *intersecao, *diferenca;
	
	setInsert(s1, 10); 	setInsert(s1, 13); 	setInsert(s1, 20);
	setInsert(s1, 25); 	setInsert(s1, 28); 	setInsert(s1, 30);
	setShow("s1", s1);
	setRemove(s1, 25);
	setShow("s1 remove 25", s1);

	setInsert(s2, 5); 	setInsert(s2, 10); 	setInsert(s2, 20);
	setInsert(s2, 21); 	setInsert(s2, 24); 	setInsert(s2, 28);
	setShow("s2", s2);
	
	uniao = setUnion(s1, s2);  
	setShow("s1Us2", uniao);
	
	intersecao = setIntersection(s1, s2);   
	setShow("s1Is2", intersecao);
	
	diferenca = setDifference(s2, s1);   
	setShow("s2-s1", diferenca);

	s1 = setDestroy(s1);
	s2 = setDestroy(s1);
	uniao = setDestroy(uniao);
	intersecao = setDestroy(intersecao);
	diferenca = setDestroy(diferenca);

	return 0;
}

