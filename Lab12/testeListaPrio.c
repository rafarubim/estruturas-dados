#include <stdio.h>
#include "listaprio.h"

int main(void) {
  int i,n=8;
  int info, vPrios[]={25, 48, 37, 12, 57, 86, 33, 92};
	int vDados[] = {1, 2, 3, 4, 5, 6, 7, 8};
  ListaP* lp = listap_cria(30/*, 0, NULL, NULL*/);
	/* Comentei parâmetros e inicializei-os com valores padrão para bater com header da professora */
  for (i=0;i<n;i++) {
    listap_insere(lp,vPrios[i],vDados[i]);
    printf("insere %d:%d, ", vDados[i], vPrios[i]);
    debug_listap_show(lp, "lp=");
  }
  do{
    info = listap_remove(lp);
    printf("remove %d ", info);
    debug_listap_show(lp, "lp=");
  } while(info>0);

  listap_libera(lp);
  return 0;
}
