#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "linear_op.h"

/*
    Function that returns the gaussian probability density estimate.
*/
double gaussian(Sample x, double *mean, double *cov, int j)
{
    int starting_index_mean = j * D;
    int starting_index_cov = j * D * D;

    // x - mean
    double *x_u = (double *)calloc(D, sizeof(double));
    for (int i = 0; i < D; i++)
        x_u[i] = x.dimensions[i] - mean[starting_index_mean + i];

    // calculate the inverse of the covariance matrix and the determinant
    double det;
    double *inv = (double *)calloc(D * D, sizeof(double));
    inverse(cov, inv, &det, D, starting_index_cov);

    // multiply (x-mean) and inverse of covariance
    double *x_u_inv = (double *)calloc(D, sizeof(double));
    matmul(inv, x_u, x_u_inv);

    // calculate the dot product of (x-mean) and the result of the previous step
    double in_exp = dotProduct(x_u_inv, x_u);

    // calculate the exponent
    in_exp = exp(-0.5 * in_exp);

    double out_exp = 1. / sqrt(pow(2 * PI, D) * det);

    free(x_u);
    free(x_u_inv);
    free(inv);

    return out_exp * in_exp;
}

/*
    Function that resets the values of the covariance matrix if it becomes the singular.
*/
void reset_cov(double *cov, int j)
{
    int starting_index = j * D * D;
    for (int r = 0; r < D; r++)
        for (int c = 0; c < D; c++)
            if (r == c)
                cov[starting_index + r * D + c] = (rand() % 10 + 1) * 0.1;
            else
                cov[starting_index + r * D + c] = 1e-6;
}

/*
    Function that resets the values of the mean vector if the covariance matrix becomes the singular.
*/
void reset_mean(double *mean, int j)
{
    int starting_index = j * D;
    for (int d = 0; d < D; d++)
        mean[starting_index + d] = (rand() % 10 + 1) * 0.1;
}

/*
    Function that performs the e-step of the algorithm.
    Calculates the soft cluster assignment of each training example.
    Stores the results in the p_val matrix passed as an argument.
*/
void e_step(Sample *X, double *mean, double *cov, double *weights, double *p_val, int row_per_process)
{
    for (int i = 0; i < row_per_process; i++) // iterate over the training examples
    {
        double p_x = 0.;                                         // the sum of pdf of all clusters
        double *gaussians = (double *)calloc(K, sizeof(double)); // store the result of gaussian pdf to avoid computing it twice

        for (int j = 0; j < K; j++)
        {
            double g = gaussian(X[i], mean, cov, j) * weights[j]; // calculate pdf
            if (!(g == g))
            {                                                  // g is Nan - matrix is singular
                reset_mean(mean, j);                           // randomly reassign
                reset_cov(cov, j);                             // randomly reassign
                g = gaussian(X[i], mean, cov, j) * weights[j]; // calculate again pdf
            }
            gaussians[j] = g; // save pdf
            p_x += g;
        }

        if (p_x == 0) // assign small value to avoid zero division
            p_x = 1e-52;

        for (int j = 0; j < K; j++) // calculate probability for each cluster assignment
        {
            double pij = gaussians[j] / p_x;
            p_val[i * K + j] = pij;
        }

        free(gaussians);
    }
}
