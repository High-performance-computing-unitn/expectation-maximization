#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "const.h"
#include "file_reader.h"
#include "em_algorithm.h"

char log_filepath[1024];

int main(int argc, char *argv[])
{
    clock_t start = clock(); // get starting time for file reading
    srand(time(NULL));

    // create the filepath for the log likelihood storing and print the first line
    snprintf(log_filepath, sizeof(log_filepath), "expectation-maximization/serial-version/log-likelihood-results/N%s_K%s_D%s.txt", argv[1], argv[3], argv[2]);
    FILE *log_file = fopen(log_filepath, "w");
    if (log_file == NULL)
    {
        printf("Error opening the file!");
        exit(1);
    }
    fprintf(log_file, "\n\n ------------------------------------------ \n Execution for N: %d, K: %d, D: %d\n", N, K, D);
    fclose(log_file);
    
    // get the input parameters
    int N = atoi(argv[1]);
    int D = atoi(argv[2]);
    int K = atoi(argv[3]);
    int max_iter = atoi(argv[4]);
    char *FILE_PATH = argv[5];

    float *examples = malloc((N * D) * sizeof(float));
    fill_matrix(examples, N, D, FILE_PATH); // fill the matrix of samples

    clock_t end = clock(); // get ending time for file reading
    printf("Time to read file: %f seconds with: %d samples\n", (double)(end - start) / CLOCKS_PER_SEC, N);

    start = clock(); // get starting time for EM algorithm
    standardize(examples, N, D); // standardize the examples

    float *weights = malloc((K) * sizeof(float));
    float *mean = malloc((K * D) * sizeof(float));
    float *covariance = malloc((K * D * D) * sizeof(float));
    float *p_val = malloc((N * K) * sizeof(float));

    initialize(mean, covariance, weights, K, D); // initialize mean, covariance and weights

    em_train(max_iter, examples, mean, covariance, weights, p_val, K, N, D); // start the algorithm

    end = clock(); // get the ending time of the EM algorithm
    printf("Completed in: %f seconds with: %d samples\n", (double)(end - start) / CLOCKS_PER_SEC, N);

    // uncomment to print results of the algorithm
    //  for (int i = 0; i < N; i++)
    //  {
    //      for (int j = 0; j < K; j++)
    //      {
    //          printf("%f ", p_val[i * K + j]);
    //      }
    //      printf("\n");
    //  }

    free(weights);
    free(mean);
    free(covariance);
    free(p_val);

    return 0;
}