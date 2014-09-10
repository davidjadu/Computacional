#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

  int n = atoi(argv[1]);

  if(n<0 || n>2500000){
    printf("ERROR: n esta fuera del rango permitido\n");
    return 1;
  }

  FILE *f;

  f=fopen("Pi_2500000.txt", "r");

  int i,c,suma=0;

  for (i=0; i<n;i++)
    if ((c=getc(f))>='0' && c<= '9') // evita entradas que no son números
      suma+=c-'0';
    else if (c==EOF)
      break;
    else i--; 

  fclose(f);

  printf("%d\n", suma);

  return 0;
}
