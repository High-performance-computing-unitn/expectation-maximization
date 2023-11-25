#ifndef EM_PROJECT_EM_ALGORITHM_H
#define EM_PROJECT_EM_ALGORITHM_H

#include "constants.h"

// initialize initial values of mean, covariance and weights
void initialize(float *mean, float *cov, float *weights, int K, int D);

// run expectation-maximization algorithm
void em_train(int n_iter, float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D);

void em_parallel(int n_iter, float *X, float *mean, float *cov, float *weights,
                 float *p_val, int my_rank, int* data_count, int* data_displ, int* p_count, int* p_displ,
                 int N, int D, int K, char *FILE_PATH);

#endif //EM_PROJECT_EM_ALGORITHM_H
