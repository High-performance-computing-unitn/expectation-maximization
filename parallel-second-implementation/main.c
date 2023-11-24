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

    N = atoi(argv[1]);
    D = atoi(argv[2]);
    K = atoi(argv[3]);
    max_iter = atoi(argv[4]);
    char *FILE_PATH = argv[5];

    last_process = world_size - 1;

    int process_samples = N / world_size;
    int sample_size = process_samples + 1;

    /*
        READING FROM FILE
    */
    start = MPI_Wtime();

    char **rows = (char **)malloc(MAX_LINES * sizeof(char *)); // allocate memory for array of rows of the file

    Sample *samples = (Sample *)malloc(sample_size * sizeof(Sample)); // allocate an array of samples

    fill_matrix(samples, rows, process_samples, my_rank, FILE_PATH); // read the file and store its content

    for (int i = 0; i < MAX_LINES; i++)
    {
        free(rows[i]);
    }
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

    standardize(samples, process_samples);

    initialize(mean, covariance, weights);

    em_train(samples, mean, covariance, weights, p_val, process_samples, my_rank);

    finish = MPI_Wtime();
    printf("Process %d completed in: %e seconds\n", my_rank, finish - start);

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < K; j++)
    //     {
    //         printf("%f ", p_val[i * K + j]);
    //     }
    //     printf("\n");
    // }

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