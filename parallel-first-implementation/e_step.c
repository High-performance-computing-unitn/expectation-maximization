#include <math.h>
#include <stdlib.h>

#include "linear_op.h"
#include "constants.h"
#include "utils.h"

/*
    Function that returns the gaussian probability density estimate.
*/
float gaussian(float *x, float *mean, float *cov, int D)
{
    // x - mean
    float *x_u = (float *)malloc(D * sizeof(float));
    for (int i = 0; i < D; i++)
        x_u[i] = x[i] - mean[i];

    // calculate the inverse of the covariance matrix and the determinant
    float det;
    float *inv = (float *)malloc(D * D * sizeof(float));
    inverse(cov, inv, &det, D);

    // multiply (x-mean) and inverse of covariance
    float *x_u_inv = (float *)malloc(D * sizeof(float));
    matmul(inv, x_u, x_u_inv, D);
    free(inv);

    // calculate the dot product of (x-mean) and the result of the previous step
    float in_exp = dotProduct(x_u_inv, x_u, D);
    free(x_u);
    free(x_u_inv);

    // calculate the exponent
    in_exp = exp(-0.5 * in_exp);

    float out_exp = 1. / sqrt(pow(2 * PI, D) * det);

    return out_exp * in_exp;
}

/*
    Function that resets the values of the covariance matrix
    if it becomes the singular.
*/
void reset_cov(float *cov, int k, int D)
{
    int start_ind = k * D * D;

    for (int r = 0; r < D; r++)
        for (int c = 0; c < D; c++)
            if (r == c)
                cov[start_ind + r * D + c] = (rand() % 10 + 1) * 0.1;
            else
                cov[start_ind + r * D + c] = 1e-6;
}

/*
    Function that resets the values of the mean vector
    if the covariance matrix becomes the singular.
*/
void reset_mean(float *mean, int k, int D)
{
    int start_ind = k * D;
    for (int d = 0; d < D; d++)
        mean[start_ind + d] = (rand() % 10 + 1) * 0.1;
}

/*
    Function that performs the e-step of the algorithm.
    Calculates the soft cluster assignment of each training example.
    Stores the results in the p_val matrix passed as an argument.
*/
void e_step(float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D)
{
    int p_val_ind = 0;

    for (int i = 0; i < N * D;) // iterate over the training examples
    {

        float *row = (float *)malloc(D * sizeof(float));
        for (int col = 0; col < D; col++)
            row[col] = X[i + col];

        float p_x = 0.;                                        // the sum of pdf of all clusters
        float *gaussians = (float *)malloc(K * sizeof(float)); // store the result of gaussian pdf to avoid computing it twice

        for (int j = 0; j < K; j++) // iterate over clusters
        {

            float *c = (float *)malloc(D * D * sizeof(float));
            float *m = (float *)malloc(D * sizeof(float));
            get_cluster_mean_cov(mean, cov, m, c, j, D);

            float g = gaussian(row, m, c, D) * weights[j]; // calculate pdf

            if (!(g == g))
            {                           // g is Nan - matrix is singular
                reset_mean(mean, j, D); // randomly reassign
                reset_cov(cov, j, D);   // randomly reassign
                get_cluster_mean_cov(mean, cov, m, c, j, D);
                g = gaussian(row, m, c, D) * weights[j]; // calculate again pdf
            }
            free(c);
            free(m);

            gaussians[j] = g; // save pdf
            p_x += g;
        }
        free(row);

        if (p_x == 0) // assign small value to avoid zero division
            p_x = 1e-5;

        for (int j = 0; j < K; j++)
        { // calculate probability for each cluster assignment
            float pij = gaussians[j] / p_x;
            p_val[p_val_ind + j] = pij;
        }
        free(gaussians);

        p_val_ind += K;
        i += D;
    }
}
