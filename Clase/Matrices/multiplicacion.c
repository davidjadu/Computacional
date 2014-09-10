#include<stdio.h>
#include<stdlib.h>

float *load_matrix(char *filename, int *n, int *m);
float *multiplicar(float *m1,float *m2,int n);
int main(int argc, char **argv){
  float *m1, *m2,*m;
  int n_row,n_col,i,j;

  m1 = load_matrix(argv[1],&n_row,&n_col);
  m2 = load_matrix(argv[2],&n_row,&n_col);

  m=multiplicar(m1,m2,n_col);

  for(i=0;i<n_row;i++){
    for(j=0;j<n_col;j++){
      printf(" %f ", m[i*n_col + j]);
    }
    printf("\n");
  }
}

float *load_matrix(char *filename, int *n, int *m){
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

  matrix = malloc(n_row * n_cols * sizeof(float));

  for(i=0;i<n_row;i++){
    for(j=0;j<n_cols;j++){
      fscanf(in, "%f", &matrix[i*n_cols + j]);
    }
  }    
  *n = n_row;
  *m = n_cols;
  return matrix;
}


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
