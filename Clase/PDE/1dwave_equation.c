#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float func_initial(float x);
void copy(float *new, float *old, int length);

int main(){
  int points = 1000;
  float dx=1.0/points;
  int n_time = 1000;
  float dt = 0.0005;
  float r=dt/dx;
  float *u_initial = malloc(points*sizeof(float));
  u_initial[0]=0.0;
  u_initial[points-1]=0.0;
  int i,j;
  FILE *out = fopen("data.dat","w");

  for(i=1; i<points-1;i++){
    u_initial[i]=func_initial(i*dx);
  }
  fprintf(out, "%f ", 0.0);
  for(i=0; i< points; i++){
    fprintf(out, "%f ", u_initial[i]);
  }
  fprintf(out, "\n");
  float *u_future = malloc(points*sizeof(float));
  u_future[0] = 0.0;
  u_future[points-1] = 0.0;



  for(i=1; i<points-1;i++){
    u_future[i]=u_initial[i]+(r*r/2.0)*(u_initial[i+1]-2.0*u_initial[i]+u_initial[i-1]);
  }
  fprintf(out, "%f ", dt);
  for(i=0; i< points; i++){
    fprintf(out, "%f ", u_future[i]);
  }
  fprintf(out, "\n");
  float *u_present = malloc(points*sizeof(float));
  float *u_past = malloc(points*sizeof(float));
  copy(u_past, u_initial, points);
  copy(u_present, u_future,points);

  for (j=2; j<n_time; j++){
    for(i=1; i<points-1; i++){
      u_future[i] = (2.0*(1.0-r*r))*u_present[i] - u_past[i] + (r*r)*(u_present[i+1] +  u_present[i-1]);
    }
  fprintf(out, "%f ", dt*j);
  for(i=0; i< points; i++){
    fprintf(out, "%f ", u_future[i]);
  }
  fprintf(out, "\n");

  copy(u_past, u_present, points);
  copy(u_present, u_future, points);

  }
  return 0;
}


float func_initial(float x){
  return exp(-(x-0.3)*(x-0.3)/0.01);
}

void copy(float *new, float *old, int length){
  int i;
  for (i=0; i<length; i++)
    new[i]=old[i];
}
