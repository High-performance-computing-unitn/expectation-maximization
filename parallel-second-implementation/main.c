#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include "constants.h"
#include "file_reader.h"
#include "linear_op.h"
#include "em_algorithm.h"

int N, D, K, max_iter, last_process;
char log_filepath[1024];

int main(int argc, char *argv[])
{
    /*
        INITIALIZATION OF VARIABLES
    */
    double start, finish;
    int world_size, my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // get input parameters
    N = atoi(argv[1]);
    D = atoi(argv[2]);
    K = atoi(argv[3]);
    max_iter = atoi(argv[4]);
    char *FILE_PATH = argv[5];
    last_process = world_size - 1;

    // master process creates the file path for log likelihood file and writes first line
    if (my_rank == MASTER_PROCESS)
    {
        snprintf(log_filepath, sizeof(log_filepath), "expectation-maximization/parallel-second-implementation/log-likelihood-results/N%s_K%s_D%s.txt", argv[1], argv[3], argv[2]);

        FILE *log_file = fopen(log_filepath, "a");
        if (log_file == NULL)
        {
            printf("Error opening the log likelihood file!");
            exit(1);
        }
        fprintf(log_file, "\n\n--------------\nExecution for N: %d, K: %d, D: %d\nWith %d processes\n", N, K, D, world_size);
        fclose(log_file);
    }

    int process_samples = N / world_size;

    /*
        READING FROM FILE
    */
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    char **rows = (char **)calloc(MAX_LINES, sizeof(char *)); // allocate memory for array of rows of the file

    Sample *samples = (Sample *)calloc(process_samples + 1, sizeof(Sample)); // allocate an array of samples

    fill_matrix(samples, rows, process_samples, my_rank, FILE_PATH); // read the file and store its content

    for (int i = 0; i < MAX_LINES; i++)
        free(rows[i]);
    free(rows);

    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();

    if (my_rank == MASTER_PROCESS)
        printf("Time to read file: %f seconds with: %d samples\n", finish - start, N);

    /*
        MEMORY ALLOCATION
    */

    double *weights = (double *)calloc(K, sizeof(double));
    double *mean = (double *)calloc(K * D, sizeof(double));
    double *covariance = (double *)calloc(K * D * D, sizeof(double));
    double *p_val = (double *)calloc(N * K, sizeof(double));

    /*
        EM ALGORTIHM
    */

    standardize(samples, process_samples); // standardize samples

    initialize(mean, covariance, weights); // initialize mean, covariance and weights

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    em_train(samples, mean, covariance, weights, p_val, process_samples, my_rank); // start algorithm

    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();

    if (my_rank == MASTER_PROCESS)
    {
        printf("Algorithm completed in: %f seconds with: %d samples\nP values produced by the algorithm\n", finish - start, N);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < K; j++)
            {
                printf("%f ", p_val[i * K + j]);
            }
            printf("\n");
        }
    }

    /*
        MEMORY FREE AND FINALIZATION
    */
    free(weights);
    free(mean);
    free(covariance);
    free(p_val);
    free(samples);

    MPI_Finalize();
    return 0;
}