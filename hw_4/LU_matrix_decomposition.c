#include<stdio.h>
#include<stdlib.h>

float *load_matrix(char *filename, int *n, int *m);
float *multiply(float *m1,float *m2,int n_row_1, int n_col_1, int n_row_2,int n_col_2);
float *traspose(float *A, int n_row,int n_col);
void lu_decomposition(float *A, float *U, float *L, int n);

int main(int argc, char **argv){
  int n_row,n_col;
  char *filename = argv[1];
  float *data = load_matrix(filename,&n_row,&n_col);
  float *data_traspose = traspose(data,n_row,n_col);  
  /*

  float *matrix = multiply(data_traspose,data, n_col,n_row,n_row,n_col);
  float *U = malloc(n_col*n_col*sizeof(float));
  float *L = malloc(n_col*n_col*sizeof(float));
  lu_decomposition(matrix,U,L,n_col);

  int i,j;
  for(i=0;i<n_col;i++){
    for(j=0;j<n_col;j++){
      printf(" %f ", U[i*n_col + j]);
    }
    printf("\n");
  }
  */
  return 0;
}

/* Function that loads a matrix into the program
 */
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


/* Function that multiplies two matrices
 */
float *multiply(float *m1,float *m2,int n_row_1, int n_col_1, int n_row_2,int n_col_2){
  if (n_col_1!=n_col_2){
    exit(1);
    printf("There was an attempt to multiply two matrices that can't be multiply");
  }
  float *m;
  int i,j,k, n = n_row_1, p=n_col_2;
  m= malloc(n*p*sizeof(float));
  float actual;
  for(i=0;i<n;i++){
    for (j=0;j<p;j++){
      actual=0;
      for (k=0;k<n_col_1;k++)
	actual+=m1[n_col_1*i+k]*m2[n_col_2*k+j];
    m[p*i+j]=actual; 
    }
  }  
  return m;
}

/* Function that trasposes the matrix A
 */
float *traspose(float *A, int n_row,int n_col){
  float *m = malloc(n_row*n_col*sizeof(float));
  int i, j;
  for (i=0; i<n_row; i++)
    for(j=0; j<n_col; i++)
      m[j*n_row+i]=A[i*n_col+j];
  return A;
}

/* Function that makes the LU decompsoiton, returns the answer by parameter
 */
void lu_decomposition(float *A, float *U, float *L, int n){
  int i,j,k;
  int found = 0;
  float temp;
  U=A;
  for (i=0; i<n; i++){
    if (U[i*n+i]==0){ // if a(i,i)=0, change lines
      for (j=i+1; j<n && found==0 ; i++){
	if (U[j*n+i] !=0){
	  U[i*n+i]=U[j*n+i];
	  found = 1;
	  for (k=i+1; k<n; k++){ //Swap the two lines
	    temp = U[i*n+k];
	    U[i*n+k]=U[j*n+k];
	    U[j*n+k]=temp;
	  }
	}
      }
      if(found == 0){
	printf("There was an attempt to lu_decompose a sngular matrix");
      }
    }
    for(j=i+1;j<n;j++){
	L[j*n+i]=U[j*n+i]/U[i*n*i];
	U[j*n+i]=0;
      for(k=i+1;k<n; k++){
	U[j*n+k]=U[j*n+k]-L[j*n+i]*U[i*n+k];
      }
    }
  }
}
