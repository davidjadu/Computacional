#include<stdio.h>
#include<stdlib.h>
#include<math.h>


float func_initial(float x);
void copy(double *new, double *old, int length);

int main(){
  int points = 50;
  double n_time = 1500;
  double c = 1.0;
  double sigma = 0.2;
  double nu = 0.3;
  double dx=1.0/points;
  double dt = sigma*dx*dx/nu;
  double alpha = dx*nu ;
  double *u_past = malloc(points*sizeof(double));
  u_past[0]=0.0;
  u_past[points-1]=0.0;
  int i,j;
  FILE *out = fopen("data_c.dat","w");

  for(i=1; i<points-1;i++){
    u_past[i]=func_initial(i*dx);
  }

  fprintf(out, "%f ", 0.0);
  for(i=0; i< points; i++){
    fprintf(out, "%f ", u_past[i]);
  }
  fprintf(out, "\n");

  double *u = malloc(points*sizeof(double));

  for (j=2; j<n_time; j++){
    for(i=0; i<points-1; i++){
      u[i] = nu * alpha * u_past[i+1]  + (1.0 - 2.0*nu*alpha)*u_past[i] + nu*alpha*u_past[i-1];
    }
    copy (u_past, u ,points);
    fprintf(out, "%f ", dt*j);
    for(i=0; i< points; i++){
      fprintf(out, "%f ", u[i]);
    }
    fprintf(out, "\n");
  }

  return 0;
}

float func_initial(float x){
  if (x>0.33 && x<0.66)
    return 1.0;
  else 
    return 0.0;
}

void copy(double *new, double *old, int length){
  int i;
  for (i=0; i<length; i++)
    new[i]=old[i];
}
