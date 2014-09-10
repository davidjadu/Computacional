#include <stdio.h>
#include <stdlib.h>
#define NPOINTS 1000000

int main (){
  int *lista;
  int i;

  lista = malloc(NPOINTS*sizeof(int));

  for (i=0; i<NPOINTS; i++){
    lista[i]=0;
  }

  return 0;
}
