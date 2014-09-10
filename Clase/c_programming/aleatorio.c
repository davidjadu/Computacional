#include<stdio.h>
#include<stdlib.h>

#define MARCHAS 3
#define PUNTOS 100

double marcha(int *npoints);
int main(int argc, char **argv){
  int sign,i;
  int semilla = atoi(argv[1]);
  srand48(semilla);
  int npoints = PUNTOS;
  for (i=0; i<MARCHAS;++i)
     printf("%f\n", marcha(&npoints));
  printf("valor npoint %d\n",npoints);
  return 0;
}

double marcha(int *npoints){
  int i;
  double x=0;
  for (i=0; i<*npoints; i++)
    x+=2.0*drand48()-1.0;
  *npoints=1234;
  return x;
}




