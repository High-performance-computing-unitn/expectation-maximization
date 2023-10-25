#include <math.h>
#include "constants.h"


void calc_sum_pij(float p_val[N][K], float res[K]) {
    for (int k = 0; k < K; k++) {
        float s = 0;
        for (int i = 0; i < N; i++) {
            s += p_val[i][k];
        }
        res[k] = s;
    }
}


void calc_covariance_nom(float X[N][D], float mean[K][D], float cov[K][D][D], float p_val[N][K]) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int r = 0; r < D; r++) { // iterate over dimensions
            for (int c = 0; c < D; c++) {

                float nom_sum = 0;
                for (int i = 0; i < N; i++) { // iterate over rows (examples)
                    float r_part = X[i][r] - mean[k][r];
                    float c_part = X[i][c] - mean[k][c];
                    nom_sum += p_val[i][k] * r_part * c_part;
                }
                if (r == c) {
                    if (fabsf(nom_sum) < 0.0001) {
                        nom_sum = 0.0001f;
                    }
                }
                cov[k][r][c] = nom_sum;
            }
        }
    }
}


void m_step_covariance(float cov[K][D][D], float sum_pij[K]) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int r = 0; r < D; r++) { // iterate over dimensions
            for (int c = 0; c < D; c++) {
                cov[k][r][c] = cov[k][r][c] / sum_pij[k];
            }
        }
    }
}


void calc_mean_nom(float X[N][D], float p_val[N][K], float res[K][D]) {
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < D; j ++) {
                res[k][j] += p_val[i][k] * X[i][j];
            }
        }
    }
}


void m_step_mean(float mean[K][D], float mean_nom[K][D], float sum_pij[K]) {
    for (int k = 0; k < K; k++) {
        for (int j = 0; j < D; j ++) {
            mean[k][j] = mean_nom[k][j] / sum_pij[k];
        }
    }
}


void m_step_weights(float sum_pij[K], float weights[K]) {
    float den = 0;
    for (int k = 0; k < K; k++) {
        den += sum_pij[k];
    }
    for (int k = 0; k < K; k++) {
        weights[k] = sum_pij[k] / den;
    }

}


void m_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]) {
    // covariance
    float sum_pij[K];
    calc_sum_pij(p_val, sum_pij);
    calc_covariance_nom(X, mean, cov, p_val);
    m_step_covariance(cov, sum_pij);

    // mean
    float mean_nom[K][D];
    calc_mean_nom(X, p_val, mean_nom);
    m_step_mean(mean, mean_nom, sum_pij);

    // weights
    m_step_weights(sum_pij, weights);
}
