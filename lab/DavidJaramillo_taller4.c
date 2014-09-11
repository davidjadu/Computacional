#include<stdio.h>
#include<stdlib.h>

float *load_matrix(char *filename, int *n);
float *multiplicar(float *m1,float *m2,int n);
float maximo(float *m, int n);
float *elevar(float *m,int k, int n);
float *suma(float *m1, float *m2, int n);
void multiplicar_escalar(float k, float *m, int n);
int factorial(int k);
void asignar(float *m1, float *m2,int n);

int main(int argc, char **argv){
  float *m;
  int n,i,j;
  float epsilon = 0.01;

  m = load_matrix(argv[1],&n);

  float *resultado = malloc(n*n*sizeof(float));

  asignar(m,resultado,n);

  for (i=0; i<n;i++)
    resultado[n*i+i]++;

  int k=2;
  float error;

  do{
    float *actual = elevar(m,k,n);
    multiplicar_escalar(1.0/factorial(k), actual, n);
    resultado = suma(resultado, actual, n);
    error = maximo(actual,n);
    printf("error: %f \n", error);
    k++;
  }while (error > epsilon);

  for (i=0; i<n; i++){
    for(j=0; j<n;j++){
      printf("%f ", resultado[n*i+j]);
    }
    printf("\n");
  }


}

float *load_matrix(char *filename, int *n){
  float *matrix;
  FILE *in;
  int n_row, n_cols;
  int i;
  int j;

  if(!(in=fopen(filename, "r"))){
    printf("Problem opening file %s\n", filename);
    exit(1);
  }

  fscanf(in, "%d %d\n", &n_row, &n_cols);

  // Se revisa que la matriz sea cuarada
  if (n_row!=n_cols){
    printf("La matriz no es cuadrada \n");
    exit(1);
  }

  matrix = malloc(n_row * n_cols * sizeof(float));

  for(i=0;i<n_row;i++){
    for(j=0;j<n_cols;j++){
      fscanf(in, "%f", &matrix[i*n_cols + j]);
    }
  }    
  *n = n_row;
  return matrix;
}

// Multiplica dos matrices
float *multiplicar(float *m1,float *m2,int n){
  float *m;
  m=malloc(n*n*sizeof(float));
  int i,j,k;
  float actual;
  for(i=0;i<n;i++){
    for (j=0;j<n;j++){
      actual=0;
      for (k=0;k<n;k++)
	actual+=m1[n*i+k]*m2[n*k+j];
    m[n*i+j]=actual; 
    }
  }
  return m;
}

// eleva la matriz m a la k>=2
float *elevar(float *m,int k, int n){
  int i;
  float *actual = multiplicar(m,m,n);
  for (i=2; i<k; i++)
    actual = multiplicar(actual,m,n);
  return actual;
}

// funcion que retorna el maximo valor del arreglo (en valor absoluto)
float maximo(float *m,int n){
  int i;
  float max=0,actual =0;
  for (i=0; i< n*n; i++){
    actual = (m[i]>0)? m[i]:-m[i];
    if (actual>max)
      max=actual;
  }
  return max;
}

// Multiplica una Matriz por un escalar
void multiplicar_escalar(float k, float *m, int n){
  int i;
  for (i=0; i< n*n; i++){
    m[i]=k*m[i];
  }
}

// Suma dos matrices
float *suma(float *m1, float *m2, int n){
  int i;
  for (i=0; i< n*n; i++){
    m1[i]=m1[i]+m2[i];
  }
  return m1;
}

//Factorial de un número
int factorial(int k){
  int i;
  int resp=1;
  for (i=2; i<k+1; i++)
    resp*=i;
  return resp;
}

//Asigna el valor de una matriz a otra (solo se asigna valor numérico)
void asignar(float *m1, float *m2,int n){
  int i,j;
  for (i=0; i<n;i++)
    for(j=0;j<n;j++)
      m2[i*n+j]=m1[i*n+j];
}
