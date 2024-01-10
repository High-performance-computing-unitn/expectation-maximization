#include <math.h>
#include <stdlib.h>

#include "linear_op.h"
#include "constants.h"
#include "utils.h"

/*
    Function that returns the gaussian probability density estimate.
*/
double gaussian(double *x, double *mean, double *cov, int D)
{
    // x - mean
    double *x_u = (double *)calloc(D, sizeof(double));
    for (int i = 0; i < D; i++)
        x_u[i] = x[i] - mean[i];

    // calculate the inverse of the covariance matrix and the determinant
    double det = determinant(cov, D);
    double *inv = (double *)calloc(D * D, sizeof(double));
    inverse(cov, inv, D);

    // multiply (x-mean) and inverse of covariance
    double *x_u_inv = (double *)calloc(D, sizeof(double));
    matmul(inv, x_u, x_u_inv, D);
    free(inv);

    // calculate the dot product of (x-mean) and the result of the previous step
    double in_exp = dotProduct(x_u_inv, x_u, D);
    free(x_u);
    free(x_u_inv);

    // calculate the exponent
    in_exp = exp(-0.5 * in_exp);

    double out_exp = 1. / sqrt(pow(2 * PI, D) * det);

    return out_exp * in_exp;
}

/*
    Function that resets the values of the covariance matrix if it becomes the singular.
*/
void reset_cov(double *cov, int k, int D)
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
    Function that resets the values of the mean vector if the covariance matrix becomes the singular.
*/
void reset_mean(double *mean, int k, int D)
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
void e_step(double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D)
{
    int p_val_ind = 0;

    for (int i = 0; i < N * D;) // iterate over the training examples
    {
        double *row = (double *)calloc(D, sizeof(double)); // copy row
        for (int col = 0; col < D; col++)
            row[col] = X[i + col];

        double p_x = 0.;                                         // the sum of pdf of all clusters
        double *gaussians = (double *)calloc(K, sizeof(double)); // store the result of gaussian pdf to avoid computing it twice

        for (int j = 0; j < K; j++) // iterate over clusters
        {
            double *c = (double *)calloc(D * D, sizeof(double));
            double *m = (double *)calloc(D, sizeof(double));
            get_cluster_mean_cov(mean, cov, m, c, j, D); // copy mean and cov

            double g = gaussian(row, m, c, D) * weights[j]; // calculate pdf

            if (!(g == g)) // g is Nan - matrix is singular
            {
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
            p_x = 1e-52;

        for (int j = 0; j < K; j++) // calculate probability for each cluster assignment
        {
            double pij = gaussians[j] / p_x;
            p_val[p_val_ind + j] = pij;
        }
        
        free(gaussians);

        p_val_ind += K;
        i += D;
    }
}
