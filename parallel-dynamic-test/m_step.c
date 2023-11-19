#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "linear_op.h"
#include "constants.h"

/*
    For each cluster it calculates the sum of probabilities
    of assignment to this cluster.
    Stores the result in res vector passed as a parameter.
*/
void calc_sum_pij(float **p_val, float *res, int process_samples)
{
    for (int k = 0; k < K; k++)
    { // iterate over clusters
        float s = 0;
        for (int i = 0; i < process_samples; i++)
        {                     // iterate over training examples
            s += p_val[i][k]; // add probability of assignment of example 'i' to cluster 'k'
        }
        res[k] = s;
    }
}

/*
    Calculate the numerator part of the mean formula.
*/
void calc_mean_num(Sample *samples, float **p_val, float **res, int process_samples)
{
    for (int k = 0; k < K; k++)
    { // iterate over clusters
        for (int i = 0; i < process_samples; i++)
        { // iterate over training examples
            for (int j = 0; j < D; j++)
            { // iterate over dimensions
                res[k][j] += p_val[i][k] * samples[i].dimensions[j];
            }
        }
    }
}

/*
    Calculate the numerator part of covariance matrix formula.
*/
void calc_covariance_num(Sample *samples, float **mean, float ***cov, float **p_val, int process_samples)
{
    // erase previous values of the covariance matrix for each cluster k
    for (int k = 0; k < K; k++)
    {
        for (int c = 0; c < D; c++)
        {
            for (int r = 0; r < D; r++)
            {
                cov[k][c][r] = 0;
            }
        }
    }

    float offset = 1e-6;

    for (int k = 0; k < K; k++)
    { // iterate over clusters
        for (int i = 0; i < process_samples; i++)
        { // iterate over training examples
            for (int r = 0; r < D; r++)
            { // iterate over row dimension
                for (int c = 0; c < D; c++)
                { // iterate over column dimension

                    // calculate the values of covariance matrix of cluster 'k' row 'r' and column 'c'
                    cov[k][r][c] += p_val[i][k] * (samples[i].dimensions[r] - mean[k][r]) * (samples[i].dimensions[c] - mean[k][c]);

                    if (r == c)
                    { // add small offset if this is the main diagonal to avoid the singularity problem
                        cov[k][r][c] += offset;
                    }
                }
            }
        }
    }
}

/*
    Function that updates the values of mean for each cluster.
*/
void m_step_mean(float **mean, float **mean_num, float *sum_pij)
{
    for (int k = 0; k < K; k++)
    {
        for (int j = 0; j < D; j++)
        {
            // calculate the value of mean of cluster 'k' at the dimension 'j'
            mean[k][j] = mean_num[k][j] / sum_pij[k];
        }
    }
}

void parallel_sum_pij(float **local_p_val, float *sum_pi, int process_samples)
{
    // each process computes sum pi
    float *local_sum_pi = (float *)malloc(K * sizeof(float));
    calc_sum_pij(local_p_val, local_sum_pi, process_samples);

    // collect sum from all processes and distribute result
    MPI_Reduce(local_sum_pi, sum_pi, K, MPI_FLOAT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);

    free(local_sum_pi);
}

void parallel_mean(Sample *samples, float **local_p_val, float *sum_pi, float **mean, int process_rank, int process_samples)
{
    // each process calculate mean numerator of its local examples
    float **local_mean_num = (float **)malloc(K * sizeof(float *));
    for (int i = 0; i < K; i++)
        local_mean_num[i] = (float *)malloc(D * sizeof(float));

    calc_mean_num(samples, local_p_val, local_mean_num, process_samples);

    // calculate sum across all processes and send result to process 0
    float **total_mean_num = (float **)malloc(K * sizeof(float *));
    for (int i = 0; i < K; i++)
        total_mean_num[i] = (float *)malloc(D * sizeof(float));

    float *send_buff = (float *)malloc(K * D * sizeof(float));
    float *recv_buff = (float *)malloc(K * D * sizeof(float));

    matrix_flatten(send_buff, local_mean_num, K, D);

    MPI_Reduce(send_buff, recv_buff, K * D, MPI_FLOAT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);

    matrix_expand(recv_buff, total_mean_num, K, D);

    // update mean values
    if (process_rank == MASTER_PROCESS)
    {
        m_step_mean(mean, total_mean_num, sum_pi);
    }

    matrix_flatten(send_buff, mean, K, D);

    // broadcast mean values to all processes
    MPI_Bcast(send_buff, K * D, MPI_FLOAT, MASTER_PROCESS, MPI_COMM_WORLD);

    matrix_expand(send_buff, mean, K, D);

    free(send_buff);
    free(recv_buff);
    for (int i = 0; i < K; i++)
    {
        free(local_mean_num[i]);
        free(total_mean_num[i]);
    }
    free(local_mean_num);
    free(total_mean_num);
}

/*
    Function that updates the values of the covariance matrix for each cluster.
*/
void m_step_covariance(float ***cov, float ***cov_num, float *sum_pij)
{
    for (int k = 0; k < K; k++)
    { // iterate over clusters
        for (int r = 0; r < D; r++)
        { // iterate over dimensions
            for (int c = 0; c < D; c++)
            {
                cov[k][r][c] = cov_num[k][r][c] / sum_pij[k];
            }
        }
    }
}

void parallel_cov(Sample *samples, float **local_p_val, float **mean, float *sum_pi, float ***cov, int process_rank, int process_samples)
{
    float ***local_cov_num = (float ***)malloc(K * sizeof(float **));
    for (int i = 0; i < K; i++)
    {
        local_cov_num[i] = (float **)malloc(D * sizeof(float *));
        for (int j = 0; j < D; j++)
        {
            local_cov_num[i][j] = (float *)malloc(D * sizeof(float));
        }
    }

    calc_covariance_num(samples, mean, local_cov_num, local_p_val, process_samples);

    // calculate sum across all processes and send result to process 0
    float ***total_cov_num = (float ***)malloc(K * sizeof(float **));
    for (int i = 0; i < K; i++)
    {
        total_cov_num[i] = (float **)malloc(D * sizeof(float *));
        for (int j = 0; j < D; j++)
        {
            total_cov_num[i][j] = (float *)malloc(D * sizeof(float));
        }
    }

    float *send_buff = (float *)malloc(K * D * D * sizeof(float));
    float *recv_buff = (float *)malloc(K * D * D * sizeof(float));

    cube_flatten(send_buff, local_cov_num, K, D, D);

    MPI_Reduce(send_buff, recv_buff, K * D * D, MPI_FLOAT, MPI_SUM, MASTER_PROCESS, MPI_COMM_WORLD);

    cube_expand(recv_buff, total_cov_num, K, D, D);

    // update cov values
    if (process_rank == MASTER_PROCESS)
    {
        m_step_covariance(cov, total_cov_num, sum_pi);
    }

    cube_flatten(send_buff, cov, K, D, D);

    // broadcast cov values to all processes
    MPI_Bcast(send_buff, K * D * D, MPI_FLOAT, MASTER_PROCESS, MPI_COMM_WORLD);

    cube_expand(send_buff, cov, K, D, D);


    /*
        FREE NOT WORKING
    */
    free(send_buff);
    free(recv_buff);
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < D; j++)
        {
            free(local_cov_num[i][j]);
            free(total_cov_num[i][j]);
        }
        free(local_cov_num[i]);
        free(total_cov_num[i]);
    }
    free(local_cov_num);
    free(total_cov_num);
}

/*
    Function that updates the values of weights for each cluster.
*/
void m_step_weights(float *sum_pij, float *weights)
{
    float den = 0;
    for (int k = 0; k < K; k++)
    {
        den += sum_pij[k];
    }
    for (int k = 0; k < K; k++)
    {
        weights[k] = sum_pij[k] / den;
    }
}

void parallel_weights(float *sum_pi, float *weights, int process_rank)
{
    // process 0 updates weights
    if (process_rank == MASTER_PROCESS)
    {
        m_step_weights(sum_pi, weights);
    }

    // broadcast cov values to all processes
    MPI_Bcast(weights, K, MPI_FLOAT, MASTER_PROCESS, MPI_COMM_WORLD);
}

void m_step_parallel(float **local_p_val, Sample *samples, float **mean, float ***cov, float *weights, int process_rank, int process_samples)
{
    // M STEP
    float *sum_pi = (float *)malloc(K * sizeof(float));
    parallel_sum_pij(local_p_val, sum_pi, process_samples);

    // calc mean
    parallel_mean(samples, local_p_val, sum_pi, mean, process_rank, process_samples);

    // calc covariance
    parallel_cov(samples, local_p_val, mean, sum_pi, cov, process_rank, process_samples);

    // calc weights
    parallel_weights(sum_pi, weights, process_rank);

    free(sum_pi);
}
