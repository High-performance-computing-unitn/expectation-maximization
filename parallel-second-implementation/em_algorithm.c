#include <stdlib.h>
#include <mpi.h>
#include "em_algorithm.h"
#include "constants.h"
#include "e_step.h"
#include "m_step.h"


// float log_likelihood(Sample *X, float *mean, float *cov, float *weights, int process_samples)
// {
//     float log_l = 0, s, g;

//     for (int i = 0; i < process_samples; i++) // iterate over the training examples
//     {
//         s = 0;
//         for (int j = 0; j < K; j++)
//         {
//             g = gaussian(X[i], mean, cov, j) * weights[j];

//             if (!(g == g)) // g is Nan - matrix is singular
//                 continue;
//             s += g;
//         }

//         log_l += log(s);
//     }
//     return log_l;
// }


/*
   The function that iteratively run expectation and maximization steps
   for n number of times.
*/
void em_train(Sample *samples, float *mean, float *cov, float *weights, float *p_val, int process_samples, int process_rank)
{
    float *local_p_val = (float *)malloc(process_samples * K * sizeof(float));

    for (int i = 0; i < max_iter; i++)
        e_step(samples, mean, cov, weights, local_p_val, process_samples);
        m_step_parallel(local_p_val, samples, mean, cov, weights, process_rank, process_samples);

    MPI_Gather(local_p_val, process_samples * K, MPI_FLOAT, p_val, process_samples * K, MPI_FLOAT, MASTER_PROCESS, MPI_COMM_WORLD);

    free(local_p_val);
}

/*
    The function that initializes the initial values of mean
    in the range (0, 1).
*/
void init_mean(float *mean)
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
void init_cov(float *cov)
{
    for (int k = 0; k < K; k++)
        for (int r = 0; r < D; r++)
            for (int c = 0; c < D; c++)
                if (r == c)
                    cov[k * D * D + r * D + c] = (rand() % 10 + 1) * 0.1;
                else
                    cov[k * D * D + r * D + c] = 1e-6;
}

/*
    The function that initializes the initial values of the weights.
    All clusters will have equal weight initially equal to 1 / K,
    where K - number of clusters.
*/
void init_weights(float *weights)
{
    for (int k = 0; k < K; k++)
        weights[k] = 1.f / K;
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
