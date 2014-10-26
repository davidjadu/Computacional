#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float func_initial(float x);
void copy(double *new, double *old, int length);

int main(){
  int points = 100;
  int n_time = 700;
  float c = 1.0;
  float sigma = 0.02;
  float nu = 0.07;
  float dx=2.0*M_PI/points;
  float dt = sigma*dx*dx/nu;
  float alpha = dx*nu ;
  double*u_past = malloc(points*sizeof(double));
  u_past[0]=0.0;
  u_past[points-1]=0.0;
  int i,j;
  FILE *out = fopen("data.dat","w");

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
      u[i] = u_past[i] - u_past[i]*dt/dx*(u_past[i]-u_past[i-1]) + nu * alpha * (u_past[i+1] -2.0*u_past[i]+u_past[i-1]);
    }
    u[-1] = u_past[-1] - u_past[-1]*dt/dx*(u_past[-1]-u_past[-2]) + nu * alpha * (u_past[0] -2.0*u_past[-1]+u_past[-2]);
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
  return sin(x);
}

void copy(double *new, double *old, int length){
  int i;
  for (i=0; i<length; i++)
    new[i]=old[i];
}
