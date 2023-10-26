#include <time.h>
#include <stdlib.h>
#include "constants.h"
#include "em_algorithm.h"


// change - draw from normal distribution
void fill_mat(float mat[N][D]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            mat[i][j] = (rand() % 10 + 1) * 0.1;
        }
    }
}


int main() {
    srand(time(NULL));

    float examples[N][D] = {0};
    fill_mat(examples);

    float weights[K] = {0};
    float mean[K][D] = {0};
    float covariance[K][D][D] = {0};
    float p_val[N][K] = {0};

    initialize(mean, covariance, weights);

    em_train(50, examples, mean, covariance, weights, p_val);

    return 0;
}
