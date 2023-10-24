#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "linear_op.h"


// change - draw from normal distribution
void fill_mat(float mat[N][D]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            mat[i][j] = rand() % 20;
        }
    }
}


int main() {
    srand(time(NULL));
    float examples[N][D] = {0};
    fill_mat(examples);

    float weights[K] =  {0};
    float mean[K][D] = {0};
    float covariance[K][D][D] = {0};

//    float inv[D][D];
//
    int m[D][D] = {{5, -2, 2, 7}, {1, 0, 0, 3},
                   {-3, 1, 5, 0}, {3, -1, -9, 4}};
    for (int i =0; i<D;i++) {
        for (int j=0; j<D;j++){
            covariance[0][i][j] = m[i][j];
        }
    }

//    int x[D] = {47, 100, 27, 81};
//    int u[D] = {1, 2, 3, 4};
//
//    float g = gaussian(x, u, covariance[0]);

//    printf("%f", g);


//
//    inverse(covariance[0], inv);
//
//    for (int i =0; i<D;i++) {
//        for (int j=0; j<D;j++){
//            printf("%f ", inv[i][j]);
//        }
//    }

    int p_val[N][K] = {0};

    // initialize
    for (int i = 0; i < N; i++) {
        int ind = rand() % K;
        p_val[i][ind] = 1;
    }

    return 0;


}
