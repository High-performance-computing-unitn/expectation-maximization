#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "linear_op.h"


/*
    Function that returns the gaussian probability density estimate.
*/
float gaussian(float x[D], float mean[D], float cov[D][D]) {
    // x - mean
    float x_u[D];
    for (int i = 0; i < D; i++) {
        x_u[i] = x[i] - mean[i];
    }

    // calculate the inverse of the covariance matrix and the determinant
    float det;
    float inv[D][D];
    inverse(cov, inv, &det);

    // multiply (x-mean) and inverse of covariance
    float x_u_inv[D];
    matmul(inv, x_u, x_u_inv);

    // calculate the dot product of (x-mean) and the result of the previous step
    float in_exp = dotProduct(x_u_inv, x_u);

    // calculate the exponent
    in_exp = exp(-0.5 * in_exp);

    float out_exp = 1. / sqrt(pow(2 * M_PI, D) * det);

    return out_exp * in_exp;
}


/*
    Function that resets the values of the covariance matrix
    if it becomes the singular.
*/
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


/*
    Function that resets the values of the mean vector
    if the covariance matrix becomes the singular.
*/
void reset_mean(float mean[D]) {
    for (int d = 0; d < D; d++) {
        mean[d] = (rand() % 10 + 1) * 0.1;
    }
}


/*
    Function that performs the e-step of the algorithm.
    Calculates the soft cluster assignment of each training example.
    Stores the results in the p_val matrix passed as an argument.
*/
void e_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K], int row_per_process) {
    for (int i = 0; i < row_per_process; i++) { // iterate over the training examples
        float p_x = 0.; // the sum of pdf of all clusters
        float gaussians[K]; // store the result of gaussian pdf to avoid computing it twice
        for (int j = 0; j < K; j++) { // iterate over clusters
            float g = gaussian(X[i], mean[j], cov[j]) * weights[j]; // calculate pdf
            if (!(g==g)) { // g is Nan - matrix is singular
                reset_mean(mean[j]); // randomly reassign
                reset_cov(cov[j]); // randomly reassign
                g = gaussian(X[i], mean[j], cov[j]) * weights[j]; // calculate again pdf
            }
            gaussians[j] = g; // save pdf
            p_x += g;
        }
        if (p_x == 0) { // assign small value to avoid zero division
            p_x = 1e-5;
        }

        for (int j = 0; j < K; j++) { // calculate probability for each cluster assignment
            float pij = gaussians[j] / p_x;
            p_val[i][j] = pij;
        }
    }
}
