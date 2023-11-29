#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "m_step.h"
#include "e_step.h"
#include "utils.h"
#include "const.h"

float log_likelihood(float *X, float *mean, float *cov, float *weights, int K, int N, int D)
{
    float log_l = 0;

    for (int i = 0; i < N * D;)
    { // iterate over the training examples

        float *row = (float *)malloc(D * sizeof(float));
        for (int col = 0; col < D; col++)
            row[col] = X[i + col];

        float s = 0;
        for (int j = 0; j < K; j++)
        {
            float *c = (float *)malloc(D * D * sizeof(float));
            float *m = (float *)malloc(D * sizeof(float));
            get_cluster_mean_cov(mean, cov, m, c, j, D);

            float g = gaussian(row, m, c, D) * weights[j];
            if (!(g == g)) // g is Nan - matrix is singular
                continue;
            s += g;

            free(c);
            free(m);
        }
        free(row);

        log_l += log(s);

        i += D;
    }
    return log_l;
}

/*
   The function that iteratively run expectation and maximization steps
   for n number of times.
*/
void em_train(int n_iter, float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D)
{

    int patience = 5;
    float log_l = log_likelihood(X, mean, cov, weights, K, N, D);

    FILE *log_file = fopen(log_filepath, "a");
    if (log_file == NULL)
    {
        printf("Error opening the file!");
        exit(1);
    }
    fprintf(log_file, "%f\n", log_l);

    for (int i = 0; i < n_iter; i++)
    {
        e_step(X, mean, cov, weights, p_val, K, N, D);
        m_step(X, mean, cov, weights, p_val, K, N, D);

        // calc log likelihood
        float log_l_next = log_likelihood(X, mean, cov, weights, K, N, D);

        fprintf(log_file, "%f\n", log_l_next);

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
    The function that initializes the initial values of mean
    in the range (0, 1).
*/
void init_mean(float *mean, int K, int D)
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
void init_cov(float *cov, int K, int D)
{
    for (int k = 0; k < K; k++)
    {
        int start_ind = k * D * D;
        for (int r = 0; r < D; r++)
            for (int c = 0; c < D; c++)
                if (r == c)
                    cov[start_ind + r * D + c] = (rand() % 10 + 1) * 0.1;
                else
                    cov[start_ind + r * D + c] = 1e-6;
    }
}

/*
    The function that initializes the initial values of the weights.
    All clusters will have equal weight initially equal to 1 / K,
    where K - number of clusters.
*/
void init_weights(float *weights, int K)
{
    for (int k = 0; k < K; k++)
        weights[k] = 1.f / K;
}

/*
    Function that initializes mean, covariance and weights.
*/
void initialize(float *mean, float *cov, float *weights, int K, int D)
{
    init_mean(mean, K, D);
    init_cov(cov, K, D);
    init_weights(weights, K);
}
