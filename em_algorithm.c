#include <stdlib.h>

#include "constants.h"
#include "m_step.h"
#include "e_step.h"


void em_train(int n_iter, float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]) {
    for (int i = 0; i < n_iter; i++) {
        e_step(X, mean, cov, weights, p_val);
        m_step(X, mean, cov, weights, p_val);
    }
}


void init_mean(float mean[K][D]) {
    for (int k = 0; k < K; k++) {
        for (int d = 0; d < D; d++) {
            mean[k][d] = (rand() % 10 + 1) * 0.1;
        }
    }
}

void init_cov(float cov[K][D][D]) {
    for (int k = 0; k < K; k++) {
        for (int r = 0; r < D; r++) {
            for (int c = 0; c < D; c ++) {
                if (r == c) {
                    cov[k][r][c] = (rand() % 10 + 1) * 0.1;
                }
                else {
                    cov[k][r][c] = 1e-6;
                }
            }
        }
    }
}


void init_weights(float weights[K]) {
    for (int k = 0; k < K; k++) {
        weights[k] = 1.f / K;
    }
}


void initialize(float mean[K][D], float cov[K][D][D], float weights[K]) {
    init_mean(mean);
    init_cov(cov);
    init_weights(weights);
}
