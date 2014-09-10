#include <stdio.h>
#include <stdlib.h>

float *load_matrix(char *filename, int *n, int *m);


int main(int argc, char **argv){
  int n,m;
  float *matrix=load_matrix(argv[1],&n,&m);
  float b[3] ={6,2,-6};
  int i ,j;
  float *x=malloc(n*sizeof(float));

  x[n-1]=b[n-1]/matrix[n*n-1];

  float dot;
  for (i=n-2;i>-1;i--){
    dot =0;
    for (j=n-1; j>i;j--){
      dot+=x[j]*matrix[n*i+j];
    }
    x[i]=(b[i]-dot)/(matrix[n*i+i]);
  }
  for (i=0; i<n;i++){
    printf("%f ", x[i]);
  }
  printf("\n");
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
