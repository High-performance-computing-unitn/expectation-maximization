#include <stdlib.h>
#include "em_algorithm.h"
#include "constants.h"
#include "e_step.h"
#include "m_step.h"

/*
   The function that iteratively run expectation and maximization steps
   for n number of times.
*/
void em_train(Sample *samples, float *mean, float *cov, float *weights, float *p_val, int process_samples, int process_rank)
{
    float *local_p_val = (float *)malloc(process_samples * K * sizeof(float));

    for (int i = 0; i < max_iter; i++)
    {
        e_step(samples, mean, cov, weights, local_p_val, process_samples);
        m_step_parallel(local_p_val, samples, mean, cov, weights, process_rank, process_samples);
    }

    /*
        TO DO GATHER P VALUES
    */

    free(local_p_val);
}

/*
    The function that initializes the initial values of mean
    in the range (0, 1).
*/
void init_mean(float *mean)
{
    for (int k = 0; k < K; k++)
    {
        for (int d = 0; d < D; d++)
        {
            mean[k * D + d] = (rand() % 10 + 1) * 0.1;
        }
    }
}

/*
    The function that initializes the initial values of covariance matrix.
    In order to make the matrix non-singular, it assigns the values
    in range (0, 1) in the main diagonal, and 1e-6 everywhere else.
*/
void init_cov(float *cov)
{
    for (int k = 0; k < K; k++)
    {
        for (int r = 0; r < D; r++)
        {
            for (int c = 0; c < D; c++)
            {
                if (r == c)
                {
                    cov[k * D * D + r * D + c] = (rand() % 10 + 1) * 0.1;
                }
                else
                {
                    cov[k * D * D + r * D + c] = 1e-6;
                }
            }
        }
    }
}

/*
    The function that initializes the initial values of the weights.
    All clusters will have equal weight initially equal to 1 / K,
    where K - number of clusters.
*/
void init_weights(float *weights)
{
    for (int k = 0; k < K; k++)
    {
        weights[k] = 1.f / K;
    }
}

/*
    Function that initializes mean, covariance and weights.
*/
void initialize(float *mean, float *cov, float *weights)
{
    init_mean(mean);
    init_cov(cov);
    init_weights(weights);
}
