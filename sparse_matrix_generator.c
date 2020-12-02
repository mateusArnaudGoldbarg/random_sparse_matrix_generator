#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//size of array
#define size 50


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
void sparse_matrix_generate(int sparsity){
    int m[size][size] = {0};
    int n_zeros = (100 - sparsity)/100.0 * ((size*size));
    int j = 0;
    printf("%d \n",n_zeros);
    while(j < n_zeros){
        int index_i = randInRange(0,size);
        int index_j = randInRange(0,size);
        if (m[index_i][index_j] != 0){
            continue;
        }
        m[index_i][index_j] = randInRange(1,9);
        j++;
    }
    print_matrix(m);
    check_sparsity(m);
}

int main()
{
    int sparcity;
    printf("Choose the sparsity in percent(%%) \n");
    scanf("%d",&sparcity);
    sparse_matrix_generate(sparcity);
    return 0;
}
