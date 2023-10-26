#include <math.h>
#include <stdlib.h>

#include "constants.h"
#include "linear_op.h"


float gaussian(float x[D], float mean[D], float cov[D][D]) {
    // x - mean
    float x_u[D];
    for (int i = 0; i < D; i++) {
        x_u[i] = x[i] - mean[i];
    }

    float det;
    float inv[D][D];
    inverse(cov, inv, &det);

    float x_u_inv[D];
    matmul(inv, x_u, x_u_inv);
    float in_exp = dotProduct(x_u_inv, x_u);
    in_exp = exp(-0.5 * in_exp);

    float out_exp = 1. / sqrt(pow(2 * M_PI, D) * det);

    return out_exp * in_exp;
}


void reset_cov(float cov[D][D]) {
    for (int r = 0; r < D; r++) {
        for (int c = 0; c < D; c++) {
            if (r == c) {
                cov[r][c] = (rand() % 10 + 1) * 0.1;
            }
            else {
                cov[r][c] = 1e-6;
            }
        }
    }
}


void reset_mean(float mean[D]) {
    for (int d = 0; d < D; d++) {
        mean[d] = (rand() % 10 + 1) * 0.1;
    }
}


void e_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]) {
    for (int i = 0; i < N; i++) {
        float p_x = 0.;
        float gaussians[K];
        for (int j = 0; j < K; j++) {
            float g = gaussian(X[i], mean[j], cov[j]) * weights[j];
            if (!(g==g)) { // g is Nan - matrix is singular
                // randomly reassign
                reset_mean(mean[j]);
                reset_cov(cov[j]);
                g = gaussian(X[i], mean[j], cov[j]) * weights[j];
            }
            gaussians[j] = g;
            p_x += g;
        }
        if (p_x == 0) { // assign small value to avoid zero division
            p_x = 1e-5;
        }

        for (int j = 0; j < K; j++) {
            float pij = gaussians[j] / p_x;
            p_val[i][j] = pij;
        }
    }
}
