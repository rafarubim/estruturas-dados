#include <stdio.h>
#include "listaprio.h"

int main(void) {
  int i,n=8;
  int info, v[]={25, 48, 37, 12, 57, 86, 33, 92};
  ListaP* lp = listap_cria(30, 8, v);
  for (i=0;i<n;i++) {
    listap_insere(lp,v[i]);
    printf("insere %d, ", v[i]);
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

