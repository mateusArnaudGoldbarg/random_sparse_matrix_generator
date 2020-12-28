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
  int sparsity = 5;
  int kernels = 8;
  int layers = 1;
  int s = 3;
  float m[layers][kernels][s][s];

  int mO[20][20] = {
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

  float mr[18][18];
  int nonzeros = (100 - sparsity)/100.0 * ((s*s*kernels));
  //int tam = nonzeros;
  for(int l = 0; l< layers; l++){
    for(int k = 0; k < kernels;k++){
          for (int i = 0; i < s ; i++){
              for(int j = 0; j < s ; j++){
                  m[l][k][i][j] = 0;
              }
          }
      }
  }

/*
  for(int k = 0; k < kernels;k++){
      int index_i = randInRange(0,s);
      int index_j = randInRange(0,s);
      m[0][k][index_i][index_j] = randInRange(0.1,0.9);
      nonzeros--;
  }
*/
    int k = 0;
    int j = 0;
    int l = 0;
    //printf("%d\n",nonzeros);

  while(l < layers){
    while(k < kernels){
          while(j < nonzeros){
              //printf("%d \n",j);
              int index_i = randInRange(0,s);
              int index_j = randInRange(0,s);
              int index_k = randInRange(0,kernels);
              //printf("%d, %d, %d \n",index_k, index_i,index_j);
              if (m[l][index_k][index_i][index_j] != 0){
                  continue;
              }
              m[l][index_k][index_i][index_j] = randInRange(0.1,0.9);
              //printf("%f\n",m[l][index_k][index_i][index_j]);
              j++;
          }
          //j=0;
          k++;
      }
      k=0;
      l++;
  }



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
  int xm=0;
  int ym=0;

  int sparse_m[nonzeros][5];
  float weights[nonzeros];


  for(int l = 0; l< layers; l++){
    for(int k = 0; k < kernels;k++){
          for (int i = 0; i < s ; i++){
              for(int j = 0; j < s ; j++){
                  if(m[l][k][i][j] != 0){
                      printf("AAAAAAAAA \n");
                      sparse_m[xm][ym] = l;
                      sparse_m[xm][ym+1] = k;
                      sparse_m[xm][ym+2] = i;
                      sparse_m[xm][ym+3] = j;
                      weights[xm] = m[l][k][i][j];
                      xm++;
                  }
              }
          }
      }
  }


  for (int i = 0; i < nonzeros; i++){
      for(int j = 0; j < 4; j++){
          printf("%d ",sparse_m[i][j]);
      }
      printf(" %f ",weights[i]);
      printf("\n");
  }

  printf("\n\n");

  //PRIMEIRA CAMADA
  float res = 0;
  int pass = 0;
  int a = 0;
  int b = 0;
  int line = 0;

  while(k < kernels){
      //printf("ESTOU AQUI\n");
      for(int i = 0; i < 18; i++){
          for(int j = 0; j< 18; j++){
              pass = 0;
              while(pass < nonzeros){
                      if(k == sparse_m[pass][1]){
                          //diff_i = sparse_m[pass][2];
                          //diff_j = sparse_m[pass][3];
                          res+=mO[i + sparse_m[pass][2]][j + sparse_m[pass][3]]*weights[pass];
                         // printf("%d, %d, %d, %d \n",diff_i,diff_j, i+diff_i, j+diff_j);
                      }
                      pass++;
                      //printf("%d\n",pass);
              }
              mr[a][b] = res;
              line = res;
              //printf("%d, %d = %d\n",a,b,line);
              res = 0;
              b++;
          }
          a++;
          b=0;

      }
      a=0;
      for (int ii = 0; ii< 18 ; ii ++){
          for (int jj =0 ; jj < 18 ; jj++){
              printf("%f ", mr[ii][jj]);
          }
          printf("\n");
      }
      printf("\n\n");
  k++;
  //printf("%d\n\n",k);
  }













  /*
      for(int l = 0; l< layers; l++){
        for(int k = 0; k < kernels;k++){
              for (int i = 0; i < s ; i++){
                  for(int j = 0; j < s ; j++){
                      if(m[l][k][i][j] != 0){
                          sparce_m[xm][ym] = l;
                          sparce_m[xm][ym+1] = k;
                          sparce_m[xm][ym+2] = i;
                          sparce_m[xm][ym+3] = j;
                          sparce_m[xm][ym+4] = m[l][k][i][j];
                          xm++;
                      }
                  }
              }
          }
      }

    printf("MATRIZ ESPARSA \n");
    for (int i = 0; i < nonzeros; i++){
        for(int j = 0; j < 5; j++){
            printf("%f ",sparce_m[i][j]);
        }
        printf("\n");
    }


    printf("\n\n");
    for (int i = 0; i< 20 ; i ++){
        for (int j =0 ; j< 20 ; j++){
            printf("%f ", mO[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");


    //PRIMEIRA CAMADA
    float res = 0;
    int pass = 0;
    int diff_i = 0;
    int diff_j = 0;
    int a = 0;
    int b = 0;
    int line = 0;

    while(k < kernels){
        //printf("ESTOU AQUI\n");
        for(int i = 0; i < 18; i++){
            for(int j = 0; j< 18; j++){
                pass = 0;
                while(pass < nonzeros){
                        if(k == sparce_m[pass][1]){
                            diff_i = sparce_m[pass][2];
                            diff_j = sparce_m[pass][3];
                            res+=mO[i + diff_i][j +diff_j]*sparce_m[pass][4];
                           // printf("%d, %d, %d, %d \n",diff_i,diff_j, i+diff_i, j+diff_j);
                        }
                        pass++;
                        //printf("%d\n",pass);
                }
                mr[a][b] = res;
                line = res;
                printf("%d, %d = %d\n",a,b,line);
                res = 0;
                b++;
            }
            a++;
            b=0;

        }
        a=0;
        for (int ii = 0; ii< 18 ; ii ++){
            for (int jj =0 ; jj < 18 ; jj++){
                printf("%f ", mr[ii][jj]);
            }
            printf("\n");
        }
        printf("\n\n");
    k++;
    printf("%d\n\n",k);
    }
    */

}

