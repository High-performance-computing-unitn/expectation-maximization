#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <stdio.h>

#include "constants.h"
#include "m_step.h"
#include "e_step.h"
#include "linear_op.h"
#include "reader.h"
#include "utils.h"

/*
   The function that iteratively run expectation and maximization steps
   for n number of times.
*/
void em_train(int n_iter, float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D)
{
    for (int i = 0; i < n_iter; i++)
    {
        e_step(X, mean, cov, weights, p_val, K, N, D);
        m_step(X, mean, cov, weights, p_val, K, N, D);
    }
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
            {
                if (r == c)
                    cov[start_ind + r * D + c] = (rand() % 10 + 1) * 0.1;
                else
                    cov[start_ind + r * D + c] = 1e-6;
            }
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

void initialize_parallel(float *X, float *mean, float *cov, float *weights, int my_rank, int N, int D, int K, char *FILE_PATH)
{
    if (my_rank == 0)
    {
        fill_matrix(X, N, D, FILE_PATH);
        standardize(X, N, D);
        initialize(mean, cov, weights, K, D);
    }
}

void divide_matrix_and_dist(float *X, float *local_examples, float *mean,
                            float *cov, float *weights, int *data_count, int *data_displ,
                            int my_rank, int N, int D, int K)
{

    // scatter matrix values to processes
    MPI_Scatterv(X, data_count, data_displ, MPI_FLOAT, local_examples,
                 data_count[my_rank], MPI_FLOAT, 0, MPI_COMM_WORLD);

    // broadcast mean, covariance, weights to all processes
    MPI_Bcast(mean, K * D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(cov, K * D * D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(weights, K, MPI_FLOAT, 0, MPI_COMM_WORLD);
}

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

void em_parallel(int n_iter, float *X, float *mean, float *cov, float *weights,
                 float *p_val, int my_rank, int *data_count, int *data_displ,
                 int *p_count, int *p_displ, int N, int D, int K, char *FILE_PATH)
{

    initialize_parallel(X, mean, cov, weights, my_rank, N, D, K, FILE_PATH);

    int row_per_process = data_count[my_rank] / D;

    // allocate memory for local matrix values
    float *local_examples = malloc(data_count[my_rank] * sizeof(float));
    divide_matrix_and_dist(X, local_examples, mean, cov, weights, data_count, data_displ, my_rank, N, D, K);

    float *local_p_val = malloc(p_count[my_rank] * sizeof(float));

    // calc log likelihood
    int patience = 5;
    float local_log_l = log_likelihood(local_examples, mean, cov, weights, K, row_per_process, D);
    float log_l;
    MPI_Allreduce(&local_log_l, &log_l, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    FILE *log_file;
    if (my_rank == 0)
    {
        log_file = fopen(log_filepath, "a");
        if (log_file == NULL)
        {
            printf("Error opening the file!");
            exit(1);
        }
        fprintf(log_file, "%f\n", log_l);
    }

    for (int i = 0; i < n_iter; i++)
    {
        // E STEP
        // each process computes e_step on its local dataset
        e_step(local_examples, mean, cov, weights, local_p_val, K, row_per_process, D);
        m_step_parallel(local_p_val, local_examples, mean, cov, weights, my_rank, row_per_process, K, D);

        // calc log likelihood
        float local_log_l = log_likelihood(local_examples, mean, cov, weights, K, row_per_process, D);
        float log_l_next;
        MPI_Allreduce(&local_log_l, &log_l_next, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

        if (my_rank == 0)
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
    free(local_examples);

    if (my_rank == 0)
        fclose(log_file);

    // gather p_val from the processes
    MPI_Gatherv(local_p_val, p_count[my_rank], MPI_FLOAT, p_val,
                p_count, p_displ, MPI_FLOAT, 0, MPI_COMM_WORLD);

    free(local_p_val);
}
