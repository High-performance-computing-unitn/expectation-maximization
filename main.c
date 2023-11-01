#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#include "constants.h"
#include "em_algorithm.h"
#include "linear_op.h"
#include "e_step.h"
#include "m_step.h"
#include "File reader/reader.h"


int main() {
    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    srand(time(NULL));

    float examples[N][D];

    float weights[K];
    float mean[K][D];
    float covariance[K][D][D];

    if (my_rank == 0) {
        fill_matrix(examples);
        standardize(examples);
        initialize(mean, covariance, weights);
    }

    // divide matrix row to processes; assume N is dividable by comm_sz for now
    const int row_per_process = N / comm_sz;
    const int el_per_process = row_per_process * D;

    // allocate memory for local matrix values
    float local_examples[row_per_process][D];
    float local_p_val[row_per_process][K];

    // scatter matrix values to processes
    MPI_Scatter(*examples, el_per_process, MPI_FLOAT, *local_examples, el_per_process, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // broadcast mean, covariance, weights to all processes
    MPI_Bcast(mean, K*D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(covariance, K*D*D, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(weights, K, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // E STEP
    // each process computes e_step on its local dataset
    e_step(local_examples, mean, covariance, weights, local_p_val, row_per_process);

    // M STEP
    // each process computes sum pi
    float local_sum_pi[K];
    calc_sum_pij(local_p_val, local_sum_pi, row_per_process);

    // collect sum from all processes and distribute result
    float sum_pi[K];
    MPI_Reduce(local_sum_pi, sum_pi, K, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    //calc mean
    // each process calculate mean numerator of its local examples
    float local_mean_num[K][D];
    calc_mean_num(local_examples, local_p_val, local_mean_num, row_per_process);

    // calculate sum across all processes and send result to process 0
    float total_mean_num[K][D];
    MPI_Reduce(local_mean_num, total_mean_num, K*D, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // update mean values
    if (my_rank == 0) {
        m_step_mean(mean, total_mean_num, sum_pi);

//        for (int i = 0; i < K; i++) {
//            for (int d = 0; d < D; d++) {
//                printf("%f ", mean[i][d]);
//            }
//            printf("\n");
//        }
    }

    // broadcast mean values to all processes
    MPI_Bcast(mean, K*D, MPI_FLOAT, 0, MPI_COMM_WORLD);



    MPI_Finalize();
    return 0;
}
