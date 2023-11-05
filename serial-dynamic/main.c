#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "utils.h"
#include "file_reader.h"
#include "em_algorithm.h"

int N, D, K;

int main()
{
    // get starting time
    clock_t start = clock();

    // allocate memory for array of rows of the file
    char **rows = (char **)malloc(MAX_LINES * sizeof(char *));
    if (rows == NULL)
    {
        printf("Cannot allocate memory");
        exit(0);
    }

    // read the file and store its content
    read_file(rows);

    // allocate memory for the matrix of samples
    float **examples = allocate_matrix(N, D);

    // fill the matrix with values
    fill_matrix(rows, examples);

    // free the rows array
    for (int i = 0; i < MAX_LINES; i++)
    {
        free(rows[i]);
    }
    free(rows);

    clock_t end = clock();
    printf("Time to read file: %f seconds with: %d samples\n", (double)(end - start) / CLOCKS_PER_SEC, N);

    start = clock();

    standardize(examples);

    float *weights = allocate_array(K);
    float **mean = allocate_matrix(K, D);
    float ***covariance = allocate_3d_array(K, D, D);
    float **p_val = allocate_matrix(N, K);

    initialize(mean, covariance, weights);

    em_train(50, examples, mean, covariance, weights, p_val);

    end = clock();
    printf("Completed in: %f seconds with: %d samples\n", (double)(end - start) / CLOCKS_PER_SEC, N);

    // free the allocated memory
    free_matrix(examples, N);

    free(weights);
    free_matrix(mean, K);
    free_3d_array(covariance, K, D);
    free_matrix(p_val, N);

    return 0;
}