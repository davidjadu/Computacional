#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double marchar_hasta(int parar, double *x, double *y, double *z,int n);

int main(int argc, char **argv){
  int m = atoi (argv[1]);
  double nd_prom[50], std[50];
  int d[50], nd[50][m];
  int i,j;

  d[0]=10;
  for (i=1; i<50; i++){
    d[i]=10+d[i-1];
  }

  double x,y,z;
  int steps;

  // Se ejecutan cada una de las marchas
  for (i=0; i<m; i++){
    srand48(i);
    x=0;
    y=0;
    z=0;
    steps=0;

    for (j=0; j<50; j++){
      steps = marchar_hasta(d[j],&x,&y,&z,steps);
      nd[j][i] = steps;
    }
  }

  for (i=0; i<50; i++){
    int total=0;
    for (j=0; j<m; j++){
      total += nd[i][j];
    }
    nd_prom[i]=total/(m+0.0);
    double suma_cuadrados = 0;
    for (j=0; j<m; j++){
      suma_cuadrados+= pow (nd[i][j]-nd_prom[i], 2);
    }
    /* El problema pedía calcular la desviación estandar pero en ningun momento
pide imprimirla, si algo la desviación estandar viene dada por std
     */
    std[i]=sqrt(suma_cuadrados + 0.0);
  }

  FILE *fileout;

  fileout = fopen ("final_stats_3D_M.dat","w");

  for (i=0; i<50; i++){
    fprintf(fileout, "%d \t %f \n", d[i],  nd_prom[i]);
  }
}

/* Se ejecuta una marcha aleatoria hasta que se encuentra a una distancia
"parar" del origen, se retorna la cantidad de pasos dados hasta ese punto*/
double marchar_hasta(int parar, double *x, double *y, double *z,int n){
  double dx, dy;

  while (pow(*x,2)+pow(*y,2)+pow(*z,2)<=pow(parar,2)){
    dx=2.0*drand48()-1.0; //Cambio en x
    dy=2.0*drand48()-1.0; //Cambio en y
    if(pow(dx,2)+pow(dy,2)>=1) // Si no se encuentra en la esfera se rechaza
      n--;
    else{
      *x+= dx;
      *y+= dy;
      if (drand48()<0.5)
	*z+=sqrt(1-pow(dx,2)+pow(dy,2));
      else 
	*z-=sqrt(1-pow(dx,2)+pow(dy,2));
    }
    n++;
  }
  return n;
}

/*Después de ver los datos, parece que N_D es proporcional al cuadrado de D.
 */
