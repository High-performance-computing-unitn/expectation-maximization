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

    int D = 5;
    int K = 4;
    int N = 300;

    float* examples = malloc((N * D) * sizeof(float ));

    float* weights = malloc((K) * sizeof(float ));
    float* mean = malloc((K * D) * sizeof(float ));
    float* covariance = malloc((K * D * D) * sizeof(float ));
    float* p_val = malloc((N * K) * sizeof(float ));

    const int row_per_process = N / comm_sz;

    em_parallel(10, examples, mean, covariance, weights, p_val, my_rank, row_per_process, N, D, K);

    free(examples);
    free(weights);
    free(mean);
    free(covariance);
    free(p_val);

    MPI_Finalize();
    return 0;
}
