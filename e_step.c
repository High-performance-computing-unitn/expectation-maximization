#include <math.h>

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
    matmul(inv, x, x_u_inv);
    float in_exp = dotProduct(x_u_inv, x);
    in_exp = exp(-0.5 * in_exp);

    float out_exp = 1. / sqrt(pow(2 * M_PI, D) * det);

    return out_exp * in_exp;
}


void e_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]) {
    for (int i = 0; i < N; i++) {
        float p_x = 0.;
        float gaussians[K];
        for (int j = 0; j < K; j++) {
            float g = gaussian(X[i], mean[j], cov[j]) * weights[j];
            gaussians[j] = g;
            p_x += g;
        }

        for (int j = 0; j < K; j++) {
            float pij = gaussians[j] / p_x;
            p_val[i][j] = pij;
        }
    }
}
