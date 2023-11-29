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
            printf("Error opening the file!");
            exit(1);
        }
        fprintf(log_file, "\n\n ------------------------------------------ \n Execution for N: %d, K: %d, D: %d\n", N, K, D);
        fclose(log_file);
    }

    int process_samples = N / world_size;

    /*
        READING FROM FILE
    */
    start = MPI_Wtime();

    char **rows = (char **)malloc(MAX_LINES * sizeof(char *)); // allocate memory for array of rows of the file

    Sample *samples = (Sample *)malloc((process_samples + 1) * sizeof(Sample)); // allocate an array of samples

    fill_matrix(samples, rows, process_samples, my_rank, FILE_PATH); // read the file and store its content

    for (int i = 0; i < MAX_LINES; i++)
    {
        if (rows[i])
            free(rows[i]);
    }
    if (rows)
        free(rows);

    finish = MPI_Wtime();
    printf("Process %d read file succesfully in: %e seconds\n", my_rank, finish - start);

    /*
        MEMORY ALLOCATION
    */

    float *weights = (float *)malloc(K * sizeof(float));
    float *mean = (float *)malloc(K * D * sizeof(float));
    float *covariance = (float *)malloc(K * D * D * sizeof(float));
    float *p_val = (float *)malloc(N * K * sizeof(float));

    /*
        EM ALGORTIHM
    */

    start = MPI_Wtime();

    standardize(samples, process_samples); // standardize samples

    initialize(mean, covariance, weights); // initialize mean, covariance and weights

    em_train(samples, mean, covariance, weights, p_val, process_samples, my_rank); // start algorithm

    finish = MPI_Wtime();

    if (my_rank == MASTER_PROCESS)
    {
        printf("Process %d completed in: %e seconds\n", my_rank, finish - start);
        // uncomment to print result of the algorithm
        // for (int i = 0; i < N; i++)
        // {
        //     for (int j = 0; j < K; j++)
        //     {
        //         printf("%f ", p_val[i * K + j]);
        //     }
        //     printf("\n");
        // }
    }

    /*
        MEMORY FREE AND FINALIZATION
    */
    if (weights)
        free(weights);
    if (mean)
        free(mean);
    if (covariance)
        free(covariance);
    if (p_val)
        free(p_val);
    if (samples)
        free(samples);
    
    MPI_Finalize();
    return 0;
}