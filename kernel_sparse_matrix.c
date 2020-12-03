#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//size of array
#define size 5


//create random values function
int randInRange(int min, int max)
{
  return min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1));
}
//print array
void print_matrix(int m[size][size]){
    for (int i=0; i < size; i++){
        for(int j = 0; j < size; j ++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}
void check_sparsity(int m[size][size]){
    int non_zeros = 0;
    int zeros = 0;
    float m_sparsity;
    for (int i=0; i < size; i++){
        for(int j = 0; j < size; j ++){
            if(m[i][j] == 0){
                zeros++;
            } else{
                non_zeros++;
            }
        }
    }
    m_sparsity = (((size*size) - non_zeros)/(float)(size*size))*100;
    printf("generated matrix with sparsity = %.4f%% \n", m_sparsity);

}

//create random sparse array
void sparse_matrix_generate(int sparsity, int kernels){



    int m[kernels][size][size];

    for(int k = 0; k < kernels;k++){
        for (int i = 0; i < size ; i++){
            for(int j = 0; j < size ; j++){
                m[k][i][j] = 0;
            }
        }
    }
/*
    for(int k = 0; k < kernels;k++){
        for (int i=0; i < size; i++){
            for(int j = 0; j < size; j ++){
                printf("%d ", m[k][i][j]);
            }
            printf("\n");
        }
        printf("\n \n");
    }
*/
    int nonzeros = (100 - sparsity)/100.0 * ((size*size));
    printf("%d \n",nonzeros);

    int k = 0;
    int j = 0;

    while(k < kernels){
        while(j < nonzeros){
            int index_i = randInRange(0,size);
            int index_j = randInRange(0,size);
            if (m[k][index_i][index_j] != 0){
                continue;
            }
            m[k][index_i][index_j] = randInRange(1,9);
            j++;
        }
        j=0;
        k++;
    }



    for(int k = 0; k < kernels;k++){
        for (int i=0; i < size; i++){
            for(int j = 0; j < size; j ++){
                printf("%d ", m[k][i][j]);
            }
            printf("\n");
        }
        printf("\n \n");
    }

}

int main()
{
    int sparcity;
    int kernels = 3;
    printf("Choose the sparsity in percent(%%) \n");
    scanf("%d",&sparcity);
    printf("Choose number of kernels \n");
    scanf("%d",&kernels);
    sparse_matrix_generate(sparcity,kernels);
    return 0;
}
