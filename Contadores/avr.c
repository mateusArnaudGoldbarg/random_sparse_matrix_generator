/*
 * main.c
 *
 * Created: 12/28/2020 10:42:28 AM
 *  Author: mateu
 */ 

#include <avr/io.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define F_CPU 16000000UL
#include "util/delay.h"

//create random values function
float randInRange(float min, float max)
{
  return min + (float) (rand() / (double) (RAND_MAX) * (max - min));
}


int main(){

  //srand (time( NULL));
  int sparsity = 5;
  int kernels = 8;
  int layers = 1;
  int s = 3;
  float m[layers][kernels][s][s];
 
  DDRB |=  0b00000010;
  
  TCCR1A |= 0b10000011;
  TCCR1B |= 0b00001010;

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

    int k = 0;
    int j = 0;
    int l = 0;

  while(l < layers){
    while(k < kernels){
          while(j < nonzeros){
              int index_i = randInRange(0,s);
              int index_j = randInRange(0,s);
              int index_k = randInRange(0,kernels);

              if (m[l][index_k][index_i][index_j] != 0){
                  continue;
              }
              m[l][index_k][index_i][index_j] = randInRange(0.1,0.9);

              j++;
          }
          //j=0;
          k++;
      }
      k=0;
      l++;
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
  
  //PRIMEIRA CAMADA
  float res = 0;
  int pass = 0;
  int a = 0;
  int b = 0;
  int line = 0;

  while(k < kernels){
      for(int i = 0; i < 18; i++){
          for(int j = 0; j< 18; j++){
              pass = 0;
              while(pass < nonzeros){
                      if(k == sparse_m[pass][1]){
                          res+=mO[i + sparse_m[pass][2]][j + sparse_m[pass][3]]*weights[pass];
                      }
                      pass++;
              }
              mr[a][b] = res;
              //line = res;
			  OCR1A = res;
              res = 0;
              b++;
          }
          a++;
          b=0;
      }
      a=0;
  k++;
  }
}


