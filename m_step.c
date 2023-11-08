#include <mpi.h>
#include <stdlib.h>



/*
    For each cluster it calculates the sum of probabilities
    of assignment to this cluster.
    Stores the result in res vector passed as a parameter.
*/
void calc_sum_pij(float *p_val, float *res, int K, int N) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        float s = 0;
        for (int i = 0; i < N; i++) { // iterate over training examples
            s += p_val[i * K + k]; // add probability of assignment of example 'i' to cluster 'k'
        }
        res[k] = s;
    }
}


/*
    Calculate the numerator part of covariance matrix formula.
*/
void calc_covariance_num(float *X, float *mean, float *cov, float *p_val, int K, int N, int D) {
    // erase previous values of the covariance matrix for each cluster k
    for (int k = 0; k < K; k++) {
        int start_ind = k * D * D;
        for (int r = 0; r < D; r++) {
            for (int c = 0; c < D; c++) {
                cov[start_ind + r * D + c] = 0;
            }
        }
    }

    float offset = 1e-6;

    for (int k = 0; k < K; k++) { // iterate over clusters
        int start_ind = k * D * D;
        for (int i = 0; i < N; i++) { // iterate over training examples
            for (int r = 0; r < D; r++) { // iterate over row dimension
                for (int c = 0; c < D; c++) { // iterate over column dimension

                    // calculate the values of covariance matrix of cluster 'k' row 'r' and column 'c'
                    cov[start_ind + r * D + c] += p_val[i * K + k] * (X[i * D + r] - mean[k * D + r]) * (X[i * D + c] - mean[k * D + c]);

                    if (r == c) { // add small offset if this is the main diagonal to avoid the singularity problem
                        cov[start_ind + r * D + c] += offset;
                    }
                }
            }
        }
    }
}


/*
    Function that updates the values of the covariance matrix for each cluster.
*/
void m_step_covariance(float *cov, float *cov_num, float *sum_pij, int K, int D) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        int start_ind = k * D * D;

        for (int r = 0; r < D; r++) { // iterate over dimensions
            for (int c = 0; c < D; c++) {
                cov[start_ind + r * D + c] = cov_num[start_ind + r * D + c] / sum_pij[k];
            }
        }
    }
}



/*
    Calculate the numerator part of the mean formula.
*/
void calc_mean_num(float *X, float *p_val, float *res, int K, int N, int D) {
    for (int k = 0; k < K; k++) { // iterate over clusters
        for (int i = 0; i < N; i++) { // iterate over training examples
            for (int j = 0; j < D; j ++) { // iterate over dimensions
                res[k * D + j] += p_val[i * K + k] * X[i * D + j];
            }
        }
    }
}


/*
    Function that updates the values of mean for each cluster.
*/
void m_step_mean(float *mean, float *mean_nom, float *sum_pij, int K, int D) {
    for (int k = 0; k < K; k++) {
        for (int j = 0; j < D; j ++) {

            // calculate the value of mean of cluster 'k' at the dimension 'j'
            mean[k * D + j] = mean_nom[k * D + j] / sum_pij[k];
        }
    }
}


/*
    Function that updates the values of weights for each cluster.
*/
void m_step_weights(float *sum_pij, float *weights, int K) {
    float den = 0;
    for (int k = 0; k < K; k++) {
        den += sum_pij[k];
    }
    for (int k = 0; k < K; k++) {
        weights[k] = sum_pij[k] / den;
    }

}


void m_step(float *X, float *mean, float *cov, float *weights, float *p_val, int K, int N, int D) {
    float *sum_pij = (float *) malloc(K *sizeof(float));
    calc_sum_pij(p_val, sum_pij, K , N);

    // update mean
    float *mean_num = (float *) malloc(K * D * sizeof(float));
    calc_mean_num(X, p_val, mean_num, K, N, D);
    m_step_mean(mean, mean_num, sum_pij, K, D);
    free(mean_num);

    // TODO correct later
    // update covariance
//    calc_covariance_num(X, mean, cov, p_val, K, N, D);
//    m_step_covariance(cov, sum_pij, K, D);

    // update weights
    m_step_weights(sum_pij, weights, K);
    free(sum_pij);
}


void parallel_sum_pij(float *local_p_val, float *sum_pi, int row_per_process, int K) {
    // each process computes sum pi
    float* local_sum_pi = malloc(K * sizeof(float ));
    calc_sum_pij(local_p_val, local_sum_pi, K, row_per_process);

    // collect sum from all processes and distribute result
    MPI_Reduce(local_sum_pi, sum_pi, K, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    free(local_sum_pi);
}


void parallel_mean(float *local_examples, float *local_p_val, float *sum_pi,
                   float *mean, int my_rank, int row_per_process, int K, int D) {
    // each process calculate mean numerator of its local examples

    float* local_mean_num = malloc(K * D * sizeof(float ));
    calc_mean_num(local_examples, local_p_val, local_mean_num, K, row_per_process, D);

    // calculate sum across all processes and send result to process 0
    float *total_mean_num = malloc(K * D * sizeof(float ));
    MPI_Reduce(local_mean_num, total_mean_num, K*D, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    free(local_mean_num);

    // update mean values
    if (my_rank == 0) {
        m_step_mean(mean, total_mean_num, sum_pi, K, D);

//        for (int i = 0; i < K; i++) {
//            for (int d = 0; d < D; d++) {
//                printf("%f ", mean[i][d]);
//            }
//            printf("\n");
//        }
    }
    free(total_mean_num);

    // broadcast mean values to all processes
    MPI_Bcast(mean, K * D, MPI_FLOAT, 0, MPI_COMM_WORLD);
}


void parallel_cov(float *local_examples, float *local_p_val, float *mean, float *sum_pi,
                  float *cov, int my_rank, int row_per_process, int K, int D) {
    float *local_cov_num = malloc(K * D * D * sizeof(float ));
    calc_covariance_num(local_examples, mean, local_cov_num, local_p_val, K, row_per_process, D);

    // calculate sum across all processes and send result to process 0
    float *total_cov_num = malloc(K * D * D * sizeof(float ));
    MPI_Reduce(local_cov_num, total_cov_num, K*D*D, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    free(local_cov_num);

    // update cov values
    if (my_rank == 0) {
        m_step_covariance(cov, total_cov_num, sum_pi, K, D);

//        for (int i = 0; i < K; i++) {
//            for (int d = 0; d < D; d++) {
//                for (int r = 0; r < D; r++) {
//                    printf("%f ", covariance[i][d][r]);
//                }
//                printf("\n");
//            }
//            printf("\n");
//        }
    }
    free(total_cov_num);

    // broadcast cov values to all processes
    MPI_Bcast(cov, K * D * D, MPI_FLOAT, 0, MPI_COMM_WORLD);
}


void parallel_weights(float *sum_pi, float *weights, int my_rank, int K) {
    // process 0 updates weights
    if (my_rank == 0) {
        m_step_weights(sum_pi, weights, K);
    }

    // broadcast cov values to all processes
    MPI_Bcast(weights, K, MPI_FLOAT, 0, MPI_COMM_WORLD);
}


void m_step_parallel(float *local_p_val, float *local_examples, float *mean,
                     float *cov, float *weights, int my_rank, int row_per_process, int K, int D) {
    // M STEP
    float *sum_pi = malloc(K * sizeof(float ));
    parallel_sum_pij(local_p_val, sum_pi, row_per_process, K);

    //calc mean
    parallel_mean(local_examples, local_p_val, sum_pi, mean, my_rank, row_per_process, K, D);

    //calc covariance
    parallel_cov(local_examples, local_p_val, mean, sum_pi, cov, my_rank, row_per_process, K, D);

    // calc weights
    parallel_weights(sum_pi, weights, my_rank, K);
    free(sum_pi);
}
