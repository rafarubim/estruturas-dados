#include <stdio.h>
#include "esparsas.h"

int main() {
	
	tsm *mat;
	
	FILE* arq = fopen("entrada.txt", "rt");
	if (!arq)
		{printf("kd o texto\n\n");	exit(1);}
		
	mat = createFromFile(arq);
	
	return 0;
}
