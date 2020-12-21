#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//create random values function
float randInRange(float min, float max)
{
  return min + (float) (rand() / (double) (RAND_MAX) * (max - min));
}





int main(){

  srand (time( NULL));
  int sparsity = 80;
  int kernels = 8;
  int layers = 1;
  int s = 3;
  float m[layers][kernels][s][s];
  float mO[20][20] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };

  float mr[19][19];

  for(int l = 0; l< layers; l++){
    for(int k = 0; k < kernels;k++){
          for (int i = 0; i < s ; i++){
              for(int j = 0; j < s ; j++){
                  m[l][k][i][j] = 0;
              }
          }
      }
  }
    int nonzeros = (100 - sparsity)/100.0 * ((s*s));
    int k = 0;
    int j = 0;
    int l = 0;

  while(l < layers){
    while(k < kernels){
          while(j < nonzeros){
              int index_i = randInRange(0,s);
              int index_j = randInRange(0,s);
              if (m[l][k][index_i][index_j] != 0){
                  continue;
              }
              m[l][k][index_i][index_j] = randInRange(0.1,0.9);
              j++;
          }
          j=0;
          k++;
      }
      k=0;
      l++;
  }
    //printando matriz esparsa
  for(int l = 0; l< layers; l++){
    for(int k = 0; k < kernels;k++){

          for (int i=0; i < s; i++){
              for(int j = 0; j < s; j ++){
                  printf("%f",m[l][k][i][j]);
                  printf(" ");
              }
              printf("\n");
          }
          printf("\n");
      }
  }
    //printando MO
    for (int i = 0; i< 20 ; i ++){
        for (int j =0 ; j<20 ; j++){
            printf("%f ", mO[i][j]);
        }
        printf("\n");
    }
printf("\n \n");
    //PRIMEIRA CAMADA
    int a = 0;
    int b = 0;
    float res = 0;
    int ker = 0;

    while(ker < kernels){
        for (int i = 0; i< 18 ; i++){
            for (int j = 0; j < 18 ; j++){
                for (int k = 0; k<s;k++){
                    for (int l = 0 ; l < s;l++){
                        res += mO[i+k][j+l]*m[0][ker][k][l];
                            //printf("%d * %d = (%d, %d) \n",m[0][0][k][l], mO[i+p][j+q], i+p,j+q);
                    }
                }

                //printf("\n \n");
                mr[a][b] = res;
                res = 0;
                b++;
            }
            b=0;
            a++;
        }
        a=0;
        ker++;
        //printando mr
        printf("\n\n");
        for (int i = 0; i< 18 ; i ++){
            for (int j =0 ; j < 18 ; j++){
                printf("%f ", mr[i][j]);
            }
            printf("\n");
        }

    }







/*

    for (int i = 0; i< 18 ; i ++){
        for (int j =0 ; j < 18 ; j++){
            printf("%d ", mr[i][j]);
        }
        printf("\n");
    }

*/

}

