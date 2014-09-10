#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
  double *x, *y, *z;
  int puntos = atoi(argv[1]);
  int i,j;

  x = malloc(puntos*sizeof(double));
  y = malloc(puntos*sizeof(double));
  z = malloc(puntos*sizeof(double));
  
  for(i=0; i<puntos;){
    x[i]=2.0*drand48()-1.0;
    y[i]=2.0*drand48()-1.0;
    z[i]=2.0*drand48()-1.0;
    if (pow(x[i],2)+pow(y[i],2)+pow(z[i],2)<=1)
      i++;
  }

  FILE *fileout;

  fileout = fopen("sphere.data", "w");

  for (j=0; j<puntos; j++){
    fprintf(fileout, "%f\t%f\t%f\n", x[j],y[j],z[j]);
  }
}
