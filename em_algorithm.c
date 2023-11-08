#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

#include "constants.h"
#include "m_step.h"
#include "e_step.h"
#include "linear_op.h"
#include "File reader/reader.h"


/*
   The function that iteratively run expectation and maximization steps
   for n number of times.
*/
void em_train(int n_iter, float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D) {
    for (int i = 0; i < n_iter; i++) {
        e_step(X, mean, cov, weights, p_val, K, N, D);
        m_step(X, mean, cov, weights, p_val, K, N, D);
    }
}


/*
    The function that initializes the initial values of mean
    in the range (0, 1).
*/
void init_mean(float *mean, int K, int D) {
    for (int k = 0; k < K; k++) {
        for (int d = 0; d < D; d++) {
            mean[k * D + d] = (rand() % 10 + 1) * 0.1;
        }
    }
}


/*
    The function that initializes the initial values of covariance matrix.
    In order to make the matrix non-singular, it assigns the values
    in range (0, 1) in the main diagonal, and 1e-6 everywhere else.
*/
void init_cov(float *cov, int K, int D) {
    for (int k = 0; k < K; k++) {
        int start_ind = k * D * D;
        for (int r = 0; r < D; r++) {
            for (int c = 0; c < D; c ++) {
                if (r == c) {
                    cov[start_ind + r * D + c] = (rand() % 10 + 1) * 0.1;
                }
                else {
                    cov[start_ind + r * D + c] = 1e-6;
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
void init_weights(float *weights, int K) {
    for (int k = 0; k < K; k++) {
        weights[k] = 1.f / K;
    }
}


/*
    Function that initializes mean, covariance and weights.
*/
void initialize(float *mean, float *cov, float *weights, int K, int D) {
    init_mean(mean, K, D);
    init_cov(cov, K, D);
    init_weights(weights, K);
}



void initialize_parallel(float *X, float *mean, float *cov, float *weights, int my_rank, int N, int D, int K) {
    if (my_rank == 0) {
        fill_matrix(X, N, D);
        standardize(X, N, D);
        initialize(mean, cov, weights, K, D);
    }
}


void divide_matrix_and_dist(float *X, float *local_examples, float *mean,
                            float *cov, float *weights, int row_per_process, int N, int D, int K) {
    const int el_per_process = row_per_process * D;

    // scatter matrix values to processes
    MPI_Scatter(X, el_per_process, MPI_FLOAT, local_examples, el_per_process, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // broadcast mean, covariance, weights to all processes
    MPI_Bcast(mean, K*D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(cov, K*D*D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(weights, K, MPI_FLOAT, 0, MPI_COMM_WORLD);
}


void em_parallel(int n_iter, float *X, float *mean, float *cov, float *weights,
                 float *p_val, int my_rank, int row_per_process, int N, int D, int K) {

    initialize_parallel(X, mean, cov, weights, my_rank, N, D, K);

    // allocate memory for local matrix values
    float *local_examples = malloc((row_per_process * D) * sizeof(float ));
    divide_matrix_and_dist(X, local_examples, mean, cov, weights, row_per_process, N, D, K);

    float* local_p_val = malloc((row_per_process * K) * sizeof(float ));

    for (int i = 0; i < n_iter; i++) {
        // E STEP
        // each process computes e_step on its local dataset
        e_step(local_examples, mean, cov, weights, local_p_val, K, row_per_process, D);

        m_step_parallel(local_p_val, local_examples, mean, cov, weights, my_rank, row_per_process, K, D);
    }
    free(local_examples);

    // TODO gather p_val
    if (my_rank == 2) {
        for (int i = 0; i < row_per_process; i++) {
            for (int d = 0; d < K; d++) {
                printf("%f ", local_p_val[i * K + d]);
            }
            printf("\n");
        }
    }

    free(local_p_val);
}
