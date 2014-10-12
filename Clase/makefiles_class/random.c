#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
  srand48(atoi(argv[1]));
  int m= atoi(argv[2]);
  int i=0;
  FILE *file = fopen("random.data","w");
  for (i=0; i< m; i++){
    fprintf(file, "%f \n", drand48());
  }
  return 0;
}
