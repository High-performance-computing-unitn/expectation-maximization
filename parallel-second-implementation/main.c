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
    clock_t start, end;
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
        START READING FROM FILE
    */
    start = clock();

    char **rows = (char **)malloc(MAX_LINES * sizeof(char *)); // allocate memory for array of rows of the file

    Sample *samples = (Sample *)malloc(sample_size * sizeof(Sample)); // allocate an array of samples

    fill_matrix(samples, rows, process_samples, my_rank, FILE_PATH); // read the file and store its content

    for (int i = 0; i < MAX_LINES; i++)
    {
        free(rows[i]);
    }
    free(rows);

    end = clock();
    printf("Process %d read file succesfully in: %f seconds\n", my_rank, (double)(end - start) / CLOCKS_PER_SEC);

    /*
        EM ALGORTIHM
    */

    start = clock();

    standardize(samples, process_samples);

    /*
        MEMORY ALLOCATION
    */

    float *weights = (float *)malloc(K * sizeof(float));

    float **mean = (float **)malloc(K * sizeof(float *));
    for (int i = 0; i < K; i++)
        mean[i] = (float *)malloc(D * sizeof(float));

    float ***covariance = (float ***)malloc(K * sizeof(float **));
    for (int i = 0; i < K; i++)
    {
        covariance[i] = (float **)malloc(D * sizeof(float *));
        for (int j = 0; j < D; j++)
            covariance[i][j] = (float *)malloc(D * sizeof(float));
    }

    float **p_val = (float **)malloc(N * sizeof(float *));
    for (int i = 0; i < N; i++)
        p_val[i] = (float *)malloc(K * sizeof(float));

    /*
        EM ALGORITHM
    */

    initialize(mean, covariance, weights);

    em_train(samples, mean, covariance, weights, p_val, process_samples, my_rank);

    end = clock();
    printf("Process %d completed in: %f seconds\n", my_rank, (double)(end - start) / CLOCKS_PER_SEC);

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

    for (int i = 0; i < K; i++)
    {
        free(mean[i]);
    }
    free(mean);

    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < D; j++)
        {
            free(covariance[i][j]);
        }
        free(covariance[i]);
    }
    free(covariance);

    for (int i = 0; i < N; i++)
    {
        free(p_val[i]);
    }
    free(p_val);

    free(samples);

    MPI_Finalize();
    return 0;
}