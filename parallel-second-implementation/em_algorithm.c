#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include "em_algorithm.h"
#include "constants.h"
#include "e_step.h"
#include "m_step.h"

float log_likelihood(Sample *samples, float *mean, float *cov, float *weights, int process_samples)
{
    float log_l = 0;

    for (int i = 0; i < process_samples; i++) // iterate over the training examples
    {
        float s = 0;
        for (int j = 0; j < K; j++)
        {
            float g = gaussian(samples[i], mean, cov, j) * weights[j];
            printf("%f\n", g);
            if (!(g == g)) // g is Nan - matrix is singular
                continue;
            s += g;
        }
        log_l += log(s);
    }
    return log_l;
}

/*
   The function that iteratively run expectation and maximization steps
   for n number of times.
*/
void em_train(Sample *samples, float *mean, float *cov, float *weights, float *p_val, int process_samples, int process_rank)
{
    float *local_p_val = (float *)malloc(process_samples * K * sizeof(float));

    // calc log likelihood
    int patience = 5;
    float local_log_l = log_likelihood(samples, mean, cov, weights, process_samples);
    float log_l = 0;
    MPI_Allreduce(&local_log_l, &log_l, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    FILE *log_file;
    if (process_rank == MASTER_PROCESS)
    {
        log_file = fopen(log_filepath, "a");
        if (log_file == NULL)
        {
            printf("Error opening the file!");
            exit(1);
        }
        fprintf(log_file, "%f\n", log_l);
    }

    for (int i = 0; i < max_iter; i++)
    {
        e_step(samples, mean, cov, weights, local_p_val, process_samples);
        m_step_parallel(local_p_val, samples, mean, cov, weights, process_rank, process_samples);

        // calc log likelihood
        float local_log_l = log_likelihood(samples, mean, cov, weights, process_samples);
        float log_l_next = 0;
        MPI_Allreduce(&local_log_l, &log_l_next, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

        if (process_rank == MASTER_PROCESS)
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

    if (process_rank == MASTER_PROCESS)
        fclose(log_file);

    MPI_Gather(local_p_val, process_samples * K, MPI_FLOAT, p_val, process_samples * K, MPI_FLOAT, MASTER_PROCESS, MPI_COMM_WORLD);

    if (local_p_val)
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
