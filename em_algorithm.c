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
void em_train(int n_iter, float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]) {
    for (int i = 0; i < n_iter; i++) {
        e_step(X, mean, cov, weights, p_val, N);
        m_step(X, mean, cov, weights, p_val);
    }
}


/*
    The function that initializes the initial values of mean
    in the range (0, 1).
*/
void init_mean(float mean[K][D]) {
    for (int k = 0; k < K; k++) {
        for (int d = 0; d < D; d++) {
            mean[k][d] = (rand() % 10 + 1) * 0.1;
        }
    }
}


/*
    The function that initializes the initial values of covariance matrix.
    In order to make the matrix non-singular, it assigns the values
    in range (0, 1) in the main diagonal, and 1e-6 everywhere else.
*/
void init_cov(float cov[K][D][D]) {
    for (int k = 0; k < K; k++) {
        for (int r = 0; r < D; r++) {
            for (int c = 0; c < D; c ++) {
                if (r == c) {
                    cov[k][r][c] = (rand() % 10 + 1) * 0.1;
                }
                else {
                    cov[k][r][c] = 1e-6;
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
void init_weights(float weights[K]) {
    for (int k = 0; k < K; k++) {
        weights[k] = 1.f / K;
    }
}


/*
    Function that initializes mean, covariance and weights.
*/
void initialize(float mean[K][D], float cov[K][D][D], float weights[K]) {
    init_mean(mean);
    init_cov(cov);
    init_weights(weights);
}


void initialize_parallel(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], int my_rank) {
    if (my_rank == 0) {
        fill_matrix(X);
        standardize(X);
        initialize(mean, cov, weights);
    }
}


void divide_matrix_and_dist(float X[N][D], float local_examples[N][D], float mean[K][D],
                            float cov[K][D][D], float weights[K], int row_per_process) {
    const int el_per_process = row_per_process * D;

    // scatter matrix values to processes
    MPI_Scatter(X, el_per_process, MPI_FLOAT, local_examples, el_per_process, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // broadcast mean, covariance, weights to all processes
    MPI_Bcast(mean, K*D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(cov, K*D*D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(weights, K, MPI_FLOAT, 0, MPI_COMM_WORLD);
}


void em_parallel(int n_iter, float X[N][D], float mean[K][D], float cov[K][D][D],
                 float weights[K], float p_val[N][K], int my_rank, int row_per_process) {

    initialize_parallel(X, mean, cov, weights, my_rank);

    // allocate memory for local matrix values
    float local_examples[row_per_process][D];
    divide_matrix_and_dist(X, local_examples, mean, cov, weights, row_per_process);

    float local_p_val[row_per_process][K];

    for (int i = 0; i < n_iter; i++) {
        // E STEP
        // each process computes e_step on its local dataset
        e_step(local_examples, mean, cov, weights, local_p_val, row_per_process);

        m_step_parallel(local_p_val, local_examples, mean, cov, weights, my_rank, row_per_process);
    }

    // TODO gather p_val
    if (my_rank == 2) {
        for (int i = 0; i < row_per_process; i++) {
            for (int d = 0; d < K; d++) {
                printf("%f ", local_p_val[i][d]);
            }
            printf("\n");
        }
    }
}
