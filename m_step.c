#include "constants.h"


/*
    For each cluster it calculates the sum of probabilities
    of assignment to this cluster.
    Stores the result in res vector passed as a parameter.
*/
void calc_sum_pij(float p_val[N][K], float res[K], int rows_per_process) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        float s = 0;
        for (int i = 0; i < rows_per_process; i++) { // iterate over training examples
            s += p_val[i][k]; // add probability of assignment of example 'i' to cluster 'k'
        }
        res[k] = s;
    }
}


/*
    Calculate the numerator part of covariance matrix formula.
*/
void calc_covariance_num(float X[N][D], float mean[K][D], float cov[K][D][D],
                         float p_val[N][K], int rows_per_process) {
    // erase previous values of the covariance matrix for each cluster k
    for (int k = 0; k < K; k++) {
        for (int c = 0; c < D; c++) {
            for (int r = 0; r < D; r++) {
                cov[k][c][r] = 0;
            }
        }
    }

    float offset = 1e-6;

    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int i = 0; i < rows_per_process; i++) { // iterate over training examples
            for (int r = 0; r < D; r++) { // iterate over row dimension
                for (int c = 0; c < D; c++) { // iterate over column dimension

                    // calculate the values of covariance matrix of cluster 'k' row 'r' and column 'c'
                    cov[k][r][c] += p_val[i][k] * (X[i][r] - mean[k][r]) * (X[i][c] - mean[k][c]);

                    if (r==c) { // add small offset if this is the main diagonal to avoid the singularity problem
                        cov[k][r][c] += offset;
                    }
                }
            }
        }
    }
}


/*
    Function that updates the values of the covariance matrix for each cluster.
*/
void m_step_covariance(float cov[K][D][D], float cov_num[K][D][D], float sum_pij[K]) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int r = 0; r < D; r++) { // iterate over dimensions
            for (int c = 0; c < D; c++) {
                cov[k][r][c] = cov_num[k][r][c] / sum_pij[k];
            }
        }
    }
}



/*
    Calculate the numerator part of the mean formula.
*/
void calc_mean_num(float X[N][D], float p_val[N][K], float res[K][D], int rows_per_process) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int i = 0; i < rows_per_process; i++) { // iterate over training examples
            for (int j = 0; j < D; j ++) { // iterate over dimensions
                res[k][j] += p_val[i][k] * X[i][j];
            }
        }
    }
}


/*
    Function that updates the values of mean for each cluster.
*/
void m_step_mean(float mean[K][D], float mean_nom[K][D], float sum_pij[K]) {
    for (int k = 0; k < K; k++) {
        for (int j = 0; j < D; j ++) {

            // calculate the value of mean of cluster 'k' at the dimension 'j'
            mean[k][j] = mean_nom[k][j] / sum_pij[k];
        }
    }
}


/*
    Function that updates the values of weights for each cluster.
*/
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
    float sum_pij[K];
    calc_sum_pij(p_val, sum_pij, N);

    // update mean
    float mean_num[K][D];
    calc_mean_num(X, p_val, mean_num, N);
    m_step_mean(mean, mean_num, sum_pij);

    // update covariance
    calc_covariance_num(X, mean, cov, p_val, N);
    m_step_covariance(cov, cov, sum_pij);

    // update weights
    m_step_weights(sum_pij, weights);
}
