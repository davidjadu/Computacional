#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float qB0_m = 2874; // qB0/m [1/s]
float Rt = 6378.1E3; // m
float c = 3E8; // m/s^2
float m = 0.938272; // GeV/c^2

float vx_prime(float x,float y,float z,float vx,float vy,float vz,float v0);
float vy_prime(float x,float y,float z,float vx,float vy,float vz,float v0);
float vz_prime(float x,float y,float z,float vx,float vy,float vz,float v0);

int main(int argc, char **argv){
  int points =10000;
  float KE = atof(argv[1]); // KE is GeV
  float alpha = atof(argv[2]);
  float x=2,y=0,z=0;
  float x_old, y_old,z_old,vx_old,vy_old,vz_old,x_old2, y_old2,z_old2,vx_old2,vy_old2,vz_old2;
  float v0 = c*sqrt(1- 1/pow( KE/(2*m*pow(c,2)) + 1 ,2) ); // Note is constant as the only force is the magnetic field. Hence gamma is constant
  float vx = 0, vy = v0*sin(alpha), vz = v0*cos(alpha);
  float t=0;
  float dt = 100.0/points;

  char filename[50];
  sprintf(filename, "trayectoria_%f_%f.dat",KE,alpha);
  FILE *out= fopen(filename,"w");
  fprintf(out,"%f %f %f %f\n",t,x,y,z);
  x_old=x,y_old=y,z_old=z,vx_old=vx,vy_old=vy,vz_old=vz;
  vx = vx_old + dt*vx_prime(x_old,y_old,z_old,vx_old,vy_old,vz_old,v0);
  vy = vy_old + dt*vy_prime(x_old,y_old,z_old,vx_old,vy_old,vz_old,v0);
  vz = vz_old + dt*vz_prime(x_old,y_old,z_old,vx_old,vy_old,vz_old,v0);
  x=x_old+dt*vx;
  y=y_old+dt*vy;
  z=z_old+dt*vz;
  fprintf(out,"%f %f %f %f\n",t,x,y,z);
  x_old2=x_old,y_old2=y_old,z_old2=z_old,vx_old2=vx_old,vy_old2=vy_old,vz_old2=vz_old;
  x_old=x,y_old=y,z_old=z,vx_old=vx,vy_old=vy,vz_old=vz;

  int i;

  //Leap frog
  for(i=0; i<points; i++){
    vx=vx_old2 + 2*dt*vx_prime(x_old,y_old,z_old,vx_old,vy_old,vz_old,v0);
    vy=vy_old2 + 2*dt*vy_prime(x_old,y_old,z_old,vx_old,vy_old,vz_old,v0);
    vz=vz_old2 + 2*dt*vz_prime(x_old,y_old,z_old,vx_old,vy_old,vz_old,v0);
    x=x_old2 + 2*dt*vx_old;
    y=y_old2 + 2*dt*vy_old;
    z=z_old2 + 2*dt*vz_old;
    t=t+dt;
    fprintf(out,"%f %f %f %f\n",t,x*Rt,y*Rt,z*Rt);
    x_old2=x_old,y_old2=y_old,z_old2=z_old,vx_old2=vx_old,vy_old2=vy_old,vz_old2=vz_old;
    x_old=x,y_old=y,z_old=z , vx_old=vx ,vy_old=vy,vz_old=vz;
  }
  fclose(out);
  return 0;

}

float vx_prime(float x,float y,float z,float vx,float vy,float vz,float v0){
  return qB0_m*(-vy*(2*pow(z,2)-pow(x,2)-pow(y,2))+3*y*z*vz)/pow(pow(x,2)+pow(y,2)+pow(z,2),5.0/2.0);
}

float vy_prime(float x,float y,float z,float vx,float vy,float vz,float v0){
  return qB0_m*(-vx*(2*pow(z,2)-pow(x,2)-pow(y,2))+3*x*z*vz)/pow(pow(x,2)+pow(y,2)+pow(z,2),5.0/2.0);
}

float vz_prime(float x,float y,float z,float vx,float vy,float vz,float v0){
  return qB0_m*(-3*vx*y*z+3*x*z*vy)/pow(pow(x,2)+pow(y,2)+pow(z,2),5.0/2.0);
}
