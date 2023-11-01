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
    float p_val[N][K];

    const int row_per_process = N / comm_sz;

    em_parallel(10, examples, mean, covariance, weights, p_val, my_rank, row_per_process);

    MPI_Finalize();
    return 0;
}
