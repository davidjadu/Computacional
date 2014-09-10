#include<stdio.h>
#include<stdlib.h>

#define PUNTOS 10000

void print_walk(double *walk);

int main(char argc, char **argv){
  int i;
  double *pasos;
  double x=0;
  int semilla = atoi(argv[1]);
  srand48(semilla);
  pasos = malloc(PUNTOS*sizeof(double));
  pasos[0]=0;
  for (i=0; i<PUNTOS;i++){
    x+=2.0*drand48()-1.0;
    pasos[i]=x;
  }

  print_walk(pasos);

  return 0;
}

void print_walk(double *walk){
  FILE *fileout;

  fileout=fopen("my_walk.dat", "w");

  int i;

  for (i=0; i<PUNTOS; i++){
    fprintf(fileout, "%f\n", walk[i]);
  }

  fclose(fileout);
}
