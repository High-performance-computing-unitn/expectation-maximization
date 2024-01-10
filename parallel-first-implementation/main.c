#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#include "utils.h"
#include "constants.h"
#include "em_algorithm.h"
#include "linear_op.h"
#include "e_step.h"
#include "m_step.h"
#include "file_reader.h"

char log_filepath[1024];

int main(int argc, char *argv[])
{
    int comm_sz, my_rank;
    double start, finish;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    srand(time(NULL));

    // get the input parameters
    int N = atoi(argv[1]);
    int D = atoi(argv[2]);
    int K = atoi(argv[3]);
    int max_iter = atoi(argv[4]);
    char *FILE_PATH = argv[5];

    // create the log likelihood file path and write first line
    if (my_rank == 0)
    {
        snprintf(log_filepath, sizeof(log_filepath), "expectation-maximization/parallel-first-implementation/log-likelihood-results/N%s_K%s_D%s.txt", argv[1], argv[3], argv[2]);
        FILE *log_file = fopen(log_filepath, "a");
        if (log_file == NULL)
        {
            printf("Error opening the log likelihood file!");
            exit(1);
        }
        fprintf(log_file, "\n\n--------------\nExecution for N: %d, K: %d, D: %d\nWith %d processes\n\n", N, K, D, comm_sz);
        fclose(log_file);
    }

    // allocate memory for the matrices
    double *examples = calloc(N * D, sizeof(double));

    double *weights = calloc(K, sizeof(double));
    double *mean = calloc(K * D, sizeof(double));
    double *covariance = calloc(K * D * D, sizeof(double));
    double *p_val = calloc(N * K, sizeof(double));

    int *data_count = (int *)calloc(comm_sz, sizeof(int));
    int *data_displ = (int *)calloc(comm_sz, sizeof(int));
    int *p_count = (int *)calloc(comm_sz, sizeof(int));
    int *p_displ = (int *)calloc(comm_sz, sizeof(int));

    // divide the rows among the processes 
    divide_rows(data_count, data_displ, p_count, p_displ, N, D, K, comm_sz);

    // wait for all processes before starting the timer
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    em_parallel(max_iter, examples, mean, covariance,
                weights, p_val, my_rank, data_count, data_displ,
                p_count, p_displ, N, D, K, FILE_PATH);
    
    // wait for all processes before ending the timer
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();

    // master process print the results
    if (my_rank == 0)
    {
        printf("Algorithm completed in: %f seconds with: %d samples\nP values produced by the algorithm\n", finish - start, N);
        for (int i = 0; i < N; i++)
        {
            for (int d = 0; d < K; d++)
            {
                printf("%f ", p_val[i * K + d]);
            }
            printf("\n");
        }
    }

    // free memory and finalize 
    free_em_data(examples, mean, covariance, weights, p_val);
    free_rows_data(data_count, data_displ, p_count, p_displ);

    MPI_Finalize();
    return 0;
}
