#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# define STEPS 100

void recorrido( double inicio[2], double final[2], double *theta, double *phi);
void vector_ortonormal(double v1[3], double v2[3], double v0[3]);
void coordenadas(double v[3], double *theta, double *phi);

int main(int argc, char **argv){
  if (argc!=5){
    printf("ERROR: Se esperaban cuatro argumentos\n");
    return 1;
  }

  double inicio[2] ={atof(argv[1]),atof(argv[2])}; //Punto de inicio, en la forma (theta,phi)
  double final[2] ={atof(argv[3]),atof(argv[4])}; //Punto de llegada, en la forma (theta,phi)

  // Se revisa que los números ingresados sí sean válidos
  if ( (final[0]>180) || (final[0]<0) || (final[1]>=360) || (final[1]<0) ||  (inicio[0]>180) || (inicio[0]<0) || (inicio[1]>360) || (inicio[1]<0) ){
    printf("Alguno de los argumentos no es valido: %f %f %f %f \n",inicio[0]*(180/M_PI),inicio[1]*(180/M_PI),final[0]*(180/M_PI),final[1]*(180/M_PI));
    return 1;
  }

  int j;

  for(j=0;j<2;j++){
    inicio[j]=inicio[j]*(M_PI/180.0);
    final[j]=final[j]*(M_PI/180.0);
  }

  double *theta;
  double *phi; 

  theta=malloc(STEPS*sizeof(double));
  phi= malloc(STEPS*sizeof(double));

  recorrido(inicio,final,theta, phi);

  int i; 
  for(i=0; i<STEPS; i++){
    printf ("%f \t %f \n",theta[i]*(180.0/M_PI), phi[i]*(180.0/M_PI)); 
  }

  return 0;
}

/* Modifica theta y phi de modo que den el camino más corto del punto inicial al final */
void recorrido( double inicio[2], double final[2], double *theta, double *phi ){
  int i;

 //vectores de los dos puntos dados
  double v1[3]= {cos(inicio[1])*sin(inicio[0]), sin(inicio[1])*sin(inicio[0]),cos(inicio[0])};
  double v2[3]= {cos(final[1])*sin(final[0]), sin(final[1])*sin(final[0]),cos(final[0])};
  double v0[3];

  vector_ortonormal(v1,v2,v0);

  double punto_12 = v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
  double punto_02 = v0[0]*v2[0]+v0[1]*v2[1]+v0[2]*v2[2];

  //se busca el punto t0 en para el cual gamma(t0) es v2, donde gamma(t) = v1*cost + v2*sint
  double t0 = acos(punto_12);
  if (punto_02<0)
    t0=2*M_PI-t0;

  double *x=malloc(STEPS*sizeof(double));
  double *y=malloc(STEPS*sizeof(double));
  double *z=malloc(STEPS*sizeof(double));

  if (t0<=M_PI){
    double dt = t0/(STEPS-1);
    double t_actual =0;
    int i;
    for (i=0; i<STEPS; i++){
      x[i]=v1[0]*cos(t_actual)+v0[0]*sin(t_actual);
      y[i]=v1[1]*cos(t_actual)+v0[1]*sin(t_actual);
      z[i]=v1[2]*cos(t_actual)+v0[2]*sin(t_actual);
      t_actual += dt;
    }
  }


  else {
    double t_actual = 0;
    double dt= (t0)/(STEPS-1);
    printf("dt %f \n", dt);
    int i;
    for (i=0; i<STEPS; i++){
      x[i]=v1[0]*cos(t_actual)+v0[0]*sin(t_actual);
      y[i]=v1[1]*cos(t_actual)+v0[1]*sin(t_actual);
      z[i]=v1[2]*cos(t_actual)+v0[2]*sin(t_actual);
      t_actual -= dt;
    }
  }

  for (i=0; i<STEPS; i++){
    double vec[3]={x[i],y[i],z[i]};
    coordenadas(vec,&(theta[i]),&(phi[i]));
  }
}

/* Encuentra un vector ortogonal a v1 que se encuentre en el plano generado por v1, v2 
En caso tal que v1 sea colineal a v2, retorna un vector ortogonal a v1 cualquiera (normalizado)*/
void vector_ortonormal(double v1[3], double v2[3], double v0[3]){
  double ppunto = v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
  if (ppunto==1 || ppunto==-1){
    if (v1[1]!=0){
      double v[3]={-v1[1],v1[0],0};
      double norma= sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2));
      int i;
      for (i=0; i<3; i++)
	v0[i] = v[i]/norma;
    }
    else {
      v0[0]=0;
      v0[1]=1;
      v0[2]=0;
    }
  }
  else {
    double v[3]= {v2[0]-ppunto*v1[0],v2[1]-ppunto*v1[1],v2[2]-ppunto*v1[2]};
    double norma= sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2));
    int i;
    for (i=0; i<3; i++)
      v0[i] = v[i]/norma;
  }
}

/* Función que devuelve las cordenadas sobre la esfera dado un punto en ella */
void coordenadas(double v[3], double *theta, double *phi){
  if (v[2]==1){
    *theta =0;
    *phi=0;
  }
  else if (v[2]==-1){
    *theta = M_PI;
    *phi = 0;
  }
  else {
    *theta = acos(v[2]);
    double p = v[0]/sin(*theta);
    if (p>1) // Para evitar que p se salga del rango de acos por falta de precisión
      p=1;
    else if (p<-1) // Para evitar que p se salga del rango de acos por falta de precisión
      p=-1;
    *phi = acos(p);
    if (v[1]/sin(*theta)<0)
      *phi = 2*M_PI - *phi;
  }
}
