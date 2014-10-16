#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const float sigma = 10.0;
const float beta = 8.0/3.0;
const float ro = 28.0;
const int points = 1000;

float x_prime(float t,float x,float y,float z);
float y_prime(float t,float x,float y,float z);
float z_prime(float t,float x,float y,float z);
void one_result(float *t, float*x, float *y, float *z);

int main(){
  int plots =20;
  float *t = malloc(points*sizeof(float));
  float *x = malloc(points*sizeof(float));
  float *y = malloc(points*sizeof(float));
  float *z = malloc(points*sizeof(float));
  int i,m;
  for(m=0; m<plots; m++){
    srand48(m);
    x[0]=20.0*drand48()-10.0;
    y[0]=20.0*drand48()-10.0;
    z[0]=20.0*drand48()-10.0;
    t[0]=0;
    one_result(t,x,y,z);
    char filename[50];
    sprintf(filename, "Data/datos%d.dat", m);
    FILE *out = fopen(filename,"w");
    for(i=0;i<points; i++)
      fprintf(out, "%f %f %f \n", x[i],y[i],z[i]);
  }
  return 0;
}

float x_prime(float t,float x,float y,float z){
  return sigma*(y-x);
}

float y_prime(float t,float x,float y,float z){
  return x*(ro-z)-y;
}

float z_prime(float t,float x,float y,float z){
  return x*y-beta*z;
}

void one_result(float *t, float *x, float *y, float *z){
  float h = 3.0/points;
  int i;
  for (i=1;i<points; i++){
    float x_middle = x[i-1]+ h/2.0*x_prime(t[i-1],x[i-1],y[i-1],z[i-1]);
    float y_middle = y[i-1]+ h/2.0*y_prime(t[i-1],x[i-1],y[i-1],z[i-1]);
    float z_middle = z[i-1]+ h/2.0*z_prime(t[i-1],x[i-1],y[i-1],z[i-1]);

    x[i]=x[i-1]+x_prime(t[i-1]+h/2.0,x_middle,y_middle,z_middle)*h;
    y[i]=y[i-1]+y_prime(t[i-1]+h/2.0,x_middle,y_middle,z_middle)*h;
    z[i]=y[i-1]+z_prime(t[i-1]+h/2.0,x_middle,y_middle,z_middle)*h;
    t[i]=t[i-1]+h;
  }
}
