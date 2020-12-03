#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//create random values function
int randInRange(int min, int max)
{

    return (rand() % max) + min;

}
//print array
void print_matrix(int ****m,int kernels,int layers,int size){
    for(int l = 0; l <layers;l++){
        for(int k = 0; k < kernels;k++){
            for (int i = 0; i < size ; i++){
                for(int j = 0; j < size ; j++){
                    printf("%d ", m[l][k][i][j]);
                }
                printf("\n");
            }
            printf("\n \n");
        }
        printf("\n\n");
    }
}
void check_sparsity(int ****m,int kernels, int layers, int size){
    int non_zeros = 0;
    int zeros = 0;
    float m_sparsity;
    for(int l = 0; l < layers ; l++){
        for(int k = 0 ; k < kernels ; k++){
            for (int i=0; i < size; i++){
                for(int j = 0; j < size; j ++){
                    if(m[l][k][i][j] == 0){
                        zeros++;
                    } else{
                        non_zeros++;
                    }
                }
            }
        }
    }
    m_sparsity = (((size*size) - non_zeros)/(float)(size*size))*100;
    printf("generated matrix with sparsity = %.4f%% \n", m_sparsity);

}

//create random sparse array
void sparse_matrix_generate(int ****m, int sparsity, int kernels, int layers, int size){
    int nonzeros = (100 - sparsity)/100.0 * ((size*size));

    printf("%d \n",nonzeros);

    int k = 0;
    int j = 0;
    int l = 0;

    while(l < layers){
        while(k < kernels){
            while(j < nonzeros){

                int index_i = randInRange(0,size);
                int index_j = randInRange(0,size);
		printf("%d  %d \n",index_i,index_j);
                if (m[l][k][index_i][index_j] != 0){
                    continue;
                }	
                m[l][k][index_i][index_j] = randInRange(1,9);
                j++;
    		printf("%d \n",j);
            }
            j=0;
            k++;
        }
        k=0;
        l++;
    }
}



int**** alloc(int sparsity,int kernels,int layers, int size) {

    int i,j,k;
    int ****matrix;
    int x,y,z,n_pairs;

    x= layers;
    y= kernels;
    z= size;
    n_pairs = size;

    matrix = (int ****) malloc(x*sizeof(int***));

    for (i=0; i<x; i++) {

        matrix[i] = (int ***) malloc(y*sizeof(int**));

        if(matrix[i]==NULL)
            return NULL;

        for (j=0; j<y; j++) {
            matrix[i][j] = (int **) malloc(z*sizeof(int*));

            if (matrix[i][j] == NULL)
                return NULL;

            for (k=0; k<z; k++) {
                matrix[i][j][k] = (int *)calloc(n_pairs,sizeof(int));

                if (matrix[i][j][k] == NULL)
                    return NULL;
            }
        }
    }

    return matrix;
}

void freeMatrix(int ****m,int x, int y, int z) {
    for(int i=0; i<x; i++) {
        for(int j=0; j<y; j++) {
            for(int k=0; k<z; k++)
                free(m[i][j][k]);

            free(m[i][j]);
        }

        free(m[i]);
    }

    free(m);
}

int main(int argc, char *argv[]){
    int sparsity = atoi((const char*)argv[1]);
    int kernels = atoi((const char*)argv[2]);
    int layers = atoi((const char*)argv[3]);
    int size = atoi((const char*)argv[4]);

    int ****m = NULL;
    
    m = alloc(sparsity,kernels,layers,size);
    sparse_matrix_generate(m,sparsity,kernels,layers,size);
    print_matrix(m,kernels,layers,size);
    //free(m,kernels,layers,size);
    return 0;
}
