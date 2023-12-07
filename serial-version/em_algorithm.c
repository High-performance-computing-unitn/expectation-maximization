#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "m_step.h"
#include "e_step.h"
#include "utils.h"
#include "constants.h"

/*
    Function that computes the log likelihood to check if the algorithm is converging
*/
double log_likelihood(double *X, double *mean, double *cov, double *weights, int K, int N, int D)
{
    double log_l = 0;

    for (int i = 0; i < N * D;) // iterate over the training examples
    { 
        double *row = (double *)calloc(D, sizeof(double));
        for (int col = 0; col < D; col++)
            row[col] = X[i + col];

        double s = 0;
        for (int j = 0; j < K; j++)
        {
            double *c = (double *)calloc(D * D, sizeof(double));
            double *m = (double *)calloc(D, sizeof(double));
            get_cluster_mean_cov(mean, cov, m, c, j, D); // copy mean and covariance

            double g = gaussian(row, m, c, D) * weights[j]; // compute pdf
            if (!(g == g)) // g is Nan - matrix is singular
                continue;
            s += g;

            free(c);
            free(m);
        }
        free(row);

        log_l += log(s); // compute log likelihood

        i += D;
    }
    return log_l;
}

/*
   The function that iteratively run expectation and maximization steps for n iterations or until convergence.
*/
void em_train(int n_iter, double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D)
{
    int patience = 5; // offset for convergence
    double log_l = log_likelihood(X, mean, cov, weights, K, N, D); // compute log likelihood

    // open file for log likelihood and print the first value
    FILE *log_file = fopen(log_filepath, "a");
    if (log_file == NULL)
    {
        printf("Error opening the log likelihood file!");
        exit(1);
    }
    fprintf(log_file, "%f\n", log_l);

    // EM steps

    for (int i = 0; i < n_iter; i++)
    {
        e_step(X, mean, cov, weights, p_val, K, N, D); //e step
        m_step(X, mean, cov, weights, p_val, K, N, D); //m step

        double log_l_next = log_likelihood(X, mean, cov, weights, K, N, D); // compute log likelihood

        fprintf(log_file, "%f\n", log_l_next); // write result on file

        // check if the value is the same as before reduce the patience and, if patience is 0 algorithm has coverged
        if (roundf(log_l) == roundf(log_l_next))
        {
            if (patience == 0)
                break;
            else
                patience--;
        }
        log_l = log_l_next;
    }
    fclose(log_file);
}

/*
    The function that initializes the initial values of mean in the range (0, 1).
*/
void init_mean(double *mean, int K, int D)
{
    for (int k = 0; k < K; k++)
        for (int d = 0; d < D; d++)
            mean[k * D + d] = (rand() % 10 + 1) * 0.1;
}

/*
    The function that initializes the initial values of covariance matrix.
    In order to make the matrix non-singular, it assigns the values
    in range (0, 1) in the main diagonal, and 1e-6 everywhere else.
*/
void init_cov(double *cov, int K, int D)
{
    for (int k = 0; k < K; k++)
    {
        int start_ind = k * D * D;
        for (int r = 0; r < D; r++)
            for (int c = 0; c < D; c++)
                if (r == c)
                    cov[start_ind + r * D + c] = 1.;
                else
                    cov[start_ind + r * D + c] = 0.;
    }
}

/*
    The function that initializes the initial values of the weights.
    All clusters will have equal weight initially equal to 1 / K, where K - number of clusters.
*/
void init_weights(double *weights, int K)
{
    for (int k = 0; k < K; k++)
        weights[k] = 1.f / K;
}

/*
    Function that initializes mean, covariance and weights.
*/
void initialize(double *mean, double *cov, double *weights, int K, int D)
{
    init_mean(mean, K, D);
    init_cov(cov, K, D);
    init_weights(weights, K);
}
