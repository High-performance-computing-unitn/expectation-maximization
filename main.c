#include <time.h>
#include <stdlib.h>
#include "constants.h"
#include "em_algorithm.h"
#include "linear_op.h"
#include "File reader/reader.c"


int main() {
    srand(time(NULL));

    float examples[N][D] = {0};
    fill_matrix(examples);
    standardize(examples);

    float weights[K] = {0};
    float mean[K][D] = {0};
    float covariance[K][D][D] = {0};
    float p_val[N][K] = {0};

    initialize(mean, covariance, weights);

    em_train(50, examples, mean, covariance, weights, p_val);

    return 0;
}
