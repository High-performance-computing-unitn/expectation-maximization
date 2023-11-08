#include <stdlib.h>

#include "m_step.h"
#include "e_step.h"


/*
   The function that iteratively run expectation and maximization steps
   for n number of times.
*/
void em_train(int n_iter, float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D) {
    for (int i = 0; i < n_iter; i++) {
        e_step(X, mean, cov, weights, p_val, K, N, D);
        m_step(X, mean, cov, weights, p_val, K, N, D);
    }
}


/*
    The function that initializes the initial values of mean
    in the range (0, 1).
*/
void init_mean(float *mean, int K, int D) {
    for (int k = 0; k < K; k++) {
        for (int d = 0; d < D; d++) {
            mean[k * D + d] = (rand() % 10 + 1) * 0.1;
        }
    }
}


/*
    The function that initializes the initial values of covariance matrix.
    In order to make the matrix non-singular, it assigns the values
    in range (0, 1) in the main diagonal, and 1e-6 everywhere else.
*/
void init_cov(float *cov, int K, int D) {
    for (int k = 0; k < K; k++) {
        int start_ind = k * D * D;
        for (int r = 0; r < D; r++) {
            for (int c = 0; c < D; c ++) {
                if (r == c) {
                    cov[start_ind + r * D + c] = (rand() % 10 + 1) * 0.1;
                }
                else {
                    cov[start_ind + r * D + c] = 1e-6;
                }
            }
        }
    }
}


/*
    The function that initializes the initial values of the weights.
    All clusters will have equal weight initially equal to 1 / K,
    where K - number of clusters.
*/
void init_weights(float *weights, int K) {
    for (int k = 0; k < K; k++) {
        weights[k] = 1.f / K;
    }
}


/*
    Function that initializes mean, covariance and weights.
*/
void initialize(float *mean, float *cov, float *weights, int K, int D) {
    init_mean(mean, K, D);
    init_cov(cov, K, D);
    init_weights(weights, K);
}
