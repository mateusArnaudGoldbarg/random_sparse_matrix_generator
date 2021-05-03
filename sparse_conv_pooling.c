#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//create random values function
float randInRange(float min, float max)
{
  return min + (float) (rand() / (double) (RAND_MAX) * (max - min));
}

void printM(int l, int c, float m[l][c]){
    for(int i = 0; i < l; i++){
        for(int j = 0;j < c; j++){
            printf("%f ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printMint(int l, int c, int m[l][c]){
    for(int i = 0; i < l; i++){
        for(int j = 0;j < c; j++){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main(){

  srand (time( NULL));
  int sparsity = 5;
  int kernels = 8;
  int layers = 1;
  int s = 3;
  int maxPooling = 2;
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
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
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

  float mr1[18][18];
  float mr2[18][18];
  float mr3[18][18];
  float mr4[18][18];
  float mr5[18][18];
  float mr6[18][18];
  float mr7[18][18];
  float mr8[18][18];

  float max1[17][17];
  float max2[17][17];
  float max3[17][17];
  float max4[17][17];
  float max5[17][17];
  float max6[17][17];
  float max7[17][17];
  float max8[17][17];

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
  printf("MATRIZ DE ENTRADA\n\n");
  printMint(20,20,mO);
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
              m[l][index_k][index_i][index_j] = randInRange(0.1,1.0);
              //printf("%f\n",m[l][index_k][index_i][index_j]);
              j++;
          }
          //j=0;
          k++;
      }
      k=0;
      l++;
  }


  //KERNELS

  printf("KERNLES COM PESOS ALEATORIOS\n\n");
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

  int sparse_m[nonzeros][4];
  float weights[nonzeros];

  printf("MATRIZ ESPARSAS\n\n");
  for(int l = 0; l< layers; l++){
    for(int k = 0; k < kernels;k++){
          for (int i = 0; i < s ; i++){
              for(int j = 0; j < s ; j++){
                  if(m[l][k][i][j] != 0){
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

  printf("==============================CAMADA CONVOLUCIONAL============================== \n\n");
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
              if(k == 0){
                mr1[a][b] = res;
              }
              if(k == 1){
                mr2[a][b] = res;
              }
              if(k == 2){
                mr3[a][b] = res;
              }
              if(k == 3){
                mr4[a][b] = res;
              }
              if(k == 4){
                mr5[a][b] = res;
              }
              if(k == 5){
                mr6[a][b] = res;
              }
              if(k == 6){
                mr7[a][b] = res;
              }
              if(k == 7){
                mr8[a][b] = res;
              }
              line = res;
              //printf("%d, %d = %d\n",a,b,line);
              res = 0;
              b++;
          }
          a++;
          b=0;

      }
    a=0;
    k++;


  }
  printf("RESULTADO DA CAMADA CONVOLUCIONAL\n\n\n");

  printM(18,18,mr1);
  printM(18,18,mr2);
  printM(18,18,mr3);
  printM(18,18,mr4);
  printM(18,18,mr5);
  printM(18,18,mr6);
  printM(18,18,mr7);
  printM(18,18,mr8);

  //MAXPOOLING
  printf("==============================MAX POOLING==============================\n\n");
  a = 0;
  b = 0;
  int zzz = 0;
  while (zzz < kernels){
  for(int i = 0; i < 18; i++){
      b=0;
      for(int j = 0; j < 18; j++){
          float maxValue = 0;
          for(int k = 0; k<maxPooling;k++){
              for(int l = 0; l < maxPooling;l++){
                  //printf("%d , %d\n\n",a,b);
                  //printf("%f   ?   %f\n\n",maxValue,mr1[k+i][l+j]);

                  //printf("%d , %d\n\n",k+i,j+l);
                  if(mr1[k+i][l+j] > maxValue && zzz ==0){
                      maxValue = mr1[k+i][l+j];
                  }

                  if(mr2[k+i][l+j] > maxValue && zzz ==1){
                      maxValue = mr2[k+i][l+j];
                  }

                  if(mr3[k+i][l+j] > maxValue && zzz ==2){
                      maxValue = mr3[k+i][l+j];
                  }

                  if(mr4[k+i][l+j] > maxValue && zzz ==3){
                      maxValue = mr4[k+i][l+j];
                  }

                  if(mr5[k+i][l+j] > maxValue && zzz ==4){
                      maxValue = mr5[k+i][l+j];
                  }

                  if(mr6[k+i][l+j] > maxValue && zzz ==5){
                      maxValue = mr6[k+i][l+j];
                  }

                  if(mr7[k+i][l+j] > maxValue && zzz ==6){
                      maxValue = mr7[k+i][l+j];
                  }

                  if(mr8[k+i][l+j] > maxValue && zzz ==7){
                      maxValue = mr8[k+i][l+j];
                  }
              }
          }
          //printf("ANALISADO\n");
          if(zzz==0){
            max1[a][b] = maxValue;
          }
          if(zzz==1){
            max2[a][b] = maxValue;
          }
          if(zzz==2){
            max3[a][b] = maxValue;
          }
          if(zzz==3){
            max4[a][b] = maxValue;
          }
          if(zzz==4){
            max5[a][b] = maxValue;
          }
          if(zzz==5){
            max6[a][b] = maxValue;
          }
          if(zzz==6){
            max7[a][b] = maxValue;
          }
          if(zzz==7){
            max8[a][b] = maxValue;
          }

          b++;
      }
    a++;
  }
  a=0;
  zzz++;
  }

  printM(17,17,max1);
  printM(17,17,max2);
  printM(17,17,max3);
  printM(17,17,max4);
  printM(17,17,max5);
  printM(17,17,max6);
  printM(17,17,max7);
  printM(17,17,max8);



}
