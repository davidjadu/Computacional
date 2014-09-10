#include <stdio.h>
#include <stdlib.h>
float *load_matrix(char *filename, int *n, int *m);
int main(int argc, char **argv){
  float *matrix;
  int n_row, n_cols;
  int i, j;

  matrix = load_matrix(argv[1], &n_row, &n_cols);

  for(i=0;i<n_row;i++){
    for(j=0;j<n_cols;j++){
      printf(" %f ", matrix[i*n_cols + j]);
    }
    printf("\n");
  }

  return 0;
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
  printf("%d %d\n", n_row, n_cols);

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

