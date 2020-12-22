#include <avr/io.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


float randInRange(float min, float max)
{
	return min + (float) (rand() / (double) (RAND_MAX) * (max - min));
}

int main(){
	DDRB |=  0b00000010;
	TCCR1A |= 0b10000011;
	TCCR1B |= 0b00001010;
	
	srand (time(NULL)); //<-Not Working for MICROCHIP STUDIO
	int sparsity = 0;
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

	float mr[18][18];

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
	//PRIMEIRA CAMADA
	int a = 0;
	int b = 0;
	float res = 0;
	int ker = 0;
	while(1){
		while(ker < kernels){
			for (int i = 0; i< 18 ; i++){
				for (int j = 0; j < 18 ; j++){
					for (int k = 0; k<s;k++){
						for (int l = 0 ; l < s;l++){
							res += mO[i+k][j+l]*m[0][ker][k][l];
						}
					}
					mr[a][b] = res;
					OCR1A = res;
					res = 0;
					b++;
				}
				b=0;
				a++;
			}
			a=0;
			ker++;
		}
	}
}
