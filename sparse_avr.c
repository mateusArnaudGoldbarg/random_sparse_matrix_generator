#include <avr/io.h>
  
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int randInRange(int min, int max)
{
  return min + (int) (rand() / (double) (RAND_MAX) * (max - min + 1));
}


int main(){
  Serial.begin(9600);
  srand (time( NULL));
  int sparsity = 80;
  int kernels = 3;
  int layers = 1;
  int s = 5;
  int m[layers][kernels][s][s];
  
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
              m[l][k][index_i][index_j] = randInRange(1,9);
              j++;
              
          }
          j=0;
          k++;
      }
      k=0;
      l++;
  }
Serial.println("ESTOU AQUI");


    //printando matriz esparsa
  for(int l = 0; l< layers; l++){
    for(int k = 0; k < kernels;k++){
        Serial.println(k);
          for (int i=0; i < s; i++){
              for(int j = 0; j < s; j ++){
                  Serial.print(m[l][k][i][j]);
                  Serial.print(" ");
              }
              Serial.print("\n");
          }
          Serial.println("\n");
      }
  }
    
  
  while(1){
   
  }
  
}
