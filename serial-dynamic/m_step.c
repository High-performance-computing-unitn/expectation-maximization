#include <stdlib.h>
#include "const.h"
#include "utils.h"

int N, D, K;

/*
    For each cluster if calculates the sum of probabilities
    of assignment to this cluster.
    Stores the result in res vector passed as a parameter.
*/
void calc_sum_pij(float **p_val, float *res) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        float s = 0;
        for (int i = 0; i < N; i++) { // iterate over training examples
            s += p_val[i][k]; // add probability of assignment of example 'i' to cluster 'k'
        }
        res[k] = s;
    }
}


/*
    Calculate the numinator part of covariance matrix formula.
*/
void calc_covariance_num(float **X, float **mean, float ***cov, float **p_val) {
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
        for (int i = 0; i < N; i++) { // iterate over training examples
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
void m_step_covariance(float ***cov, float *sum_pij) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int r = 0; r < D; r++) { // iterate over dimensions
            for (int c = 0; c < D; c++) {
                cov[k][r][c] = cov[k][r][c] / sum_pij[k];
            }
        }
    }
}



/*
    Calculate the numinator part of the mean formula.
*/
void calc_mean_num(float **X, float **p_val, float **res) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int i = 0; i < N; i++) { // iterate over training examples
            for (int j = 0; j < D; j ++) { // iterate over dimensions
                res[k][j] += p_val[i][k] * X[i][j];
            }
        }
    }
}


/*
    Function that updates the values of mean for each cluster.
*/
void m_step_mean(float **mean, float **mean_nom, float *sum_pij) {
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
void m_step_weights(float *sum_pij, float *weights) {
    float den = 0;
    for (int k = 0; k < K; k++) {
        den += sum_pij[k];
    }
    for (int k = 0; k < K; k++) {
        weights[k] = sum_pij[k] / den;
    }

}


void m_step(float **X, float **mean, float ***cov, float *weights, float **p_val) {
    float *sum_pij = allocate_array(K);
    calc_sum_pij(p_val, sum_pij);

    // update mean
    float **mean_num = allocate_matrix(K, D);
    calc_mean_num(X, p_val, mean_num);
    m_step_mean(mean, mean_num, sum_pij);

    // update covariance
    calc_covariance_num(X, mean, cov, p_val);
    m_step_covariance(cov, sum_pij);

    // update weights
    m_step_weights(sum_pij, weights);

    free(sum_pij);
    free_matrix(mean_num, K);
}
