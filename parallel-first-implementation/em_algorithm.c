#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <stdio.h>

#include "constants.h"
#include "m_step.h"
#include "e_step.h"
#include "linear_op.h"
#include "file_reader.h"
#include "utils.h"

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

/*
    Function that reads input data, standardize it and initialize cov, mean and weights 
    before scattering all the values to the processes
*/
void initialize_parallel(double *X, double *mean, double *cov, double *weights, int my_rank, int N, int D, int K, char *FILE_PATH)
{
    if (my_rank == 0)
    {
        double start = MPI_Wtime();
        fill_matrix(X, N, D, FILE_PATH);
        double finish = MPI_Wtime();
        printf("Time to read file: %f seconds with: %d samples\n", finish - start, N);
        standardize(X, N, D);
        initialize(mean, cov, weights, K, D);
    }
}

/*
    Function that divide the matrix and distribute the values to all the processes    
*/
void divide_matrix_and_dist(double *X, double *local_examples, double *mean,
                            double *cov, double *weights, int *data_count, int *data_displ,
                            int my_rank, int N, int D, int K)
{

    // scatter matrix values to processes
    MPI_Scatterv(X, data_count, data_displ, MPI_DOUBLE, local_examples,
                 data_count[my_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // broadcast mean, covariance, weights to all processes
    MPI_Bcast(mean, K * D, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(cov, K * D * D, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(weights, K, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

/*
    Function that computes the log likelihood to check for convergence
*/
double log_likelihood(double *X, double *mean, double *cov, double *weights, int K, int N, int D)
{
    double log_l = 0;

    for (int i = 0; i < N * D;) // iterate over the training examples
    { 
        double *row = (double *)calloc(D, sizeof(double)); // copy the row
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

        log_l += log(s); // calculate log lokelihood

        i += D;
    }
    return log_l;
}

/*
    Function that computes the EM algorithm parallel
*/
void em_parallel(int n_iter, double *X, double *mean, double *cov, double *weights,
                 double *p_val, int my_rank, int *data_count, int *data_displ,
                 int *p_count, int *p_displ, int N, int D, int K, char *FILE_PATH)
{

    // initialize the values in a parallel fashion
    initialize_parallel(X, mean, cov, weights, my_rank, N, D, K, FILE_PATH);

    int row_per_process = data_count[my_rank] / D;

    // allocate memory for local matrix values
    double *local_examples = calloc(data_count[my_rank], sizeof(double));
    // divide the matrix and distribute it to all processes
    divide_matrix_and_dist(X, local_examples, mean, cov, weights, data_count, data_displ, my_rank, N, D, K);

    double *local_p_val = calloc(p_count[my_rank], sizeof(double));

    // calc log likelihood
    int patience = 5; // patience to check the algorithm has really converged
    double local_log_l = log_likelihood(local_examples, mean, cov, weights, K, row_per_process, D);
    double log_l;
    // sum the likelihood of all processes to check
    MPI_Allreduce(&local_log_l, &log_l, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    // process 0 opens the file and store the first value
    FILE *log_file;
    if (my_rank == 0)
    {
        log_file = fopen(log_filepath, "a");
        if (log_file == NULL)
        {
            printf("Error opening the log likelihood file!");
            exit(1);
        }
        fprintf(log_file, "%f\n", log_l);
    }

    for (int i = 0; i < n_iter; i++)
    {
        // E STEP
        // each process computes e_step on its local dataset
        e_step(local_examples, mean, cov, weights, local_p_val, K, row_per_process, D);
        // M STEP PARALLEL
        // each process computes the m_step and shares the values during its execution
        m_step_parallel(local_p_val, local_examples, mean, cov, weights, my_rank, row_per_process, K, D);

        // calc log likelihood
        double local_log_l = log_likelihood(local_examples, mean, cov, weights, K, row_per_process, D);
        double log_l_next;
        // sum the likelihood of all processes to check
        MPI_Allreduce(&local_log_l, &log_l_next, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        // process 0 stores the result
        if (my_rank == 0)
            fprintf(log_file, "%f\n", log_l_next);

        // check the value of log likelihood and if it is the same reduce patience, if patience is 0 algorithm has converged
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

    // gather p_val from the processes to print them
    MPI_Gatherv(local_p_val, p_count[my_rank], MPI_DOUBLE, p_val, p_count, p_displ, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    free(local_p_val);
}
