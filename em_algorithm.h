#ifndef EM_PROJECT_EM_ALGORITHM_H
#define EM_PROJECT_EM_ALGORITHM_H

#include "constants.h"

// initialize initial values of mean, covariance and weights
void initialize(float mean[K][D], float cov[K][D][D], float weights[K]);

// run expectation-maximization algorithm
void em_train(int n_iter, float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]);

void em_parallel(int n_iter, float X[N][D], float mean[K][D], float cov[K][D][D],
                 float weights[K], float p_val[N][K], int my_rank, int row_per_process);

#endif //EM_PROJECT_EM_ALGORITHM_H
