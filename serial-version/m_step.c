#include <stdlib.h>

/*
    For each cluster it calculates the sum of probabilities of assignment to this cluster.
    Stores the result in res vector passed as a parameter.
*/
void calc_sum_pij(double *p_val, double *res, int K, int N)
{
    for (int k = 0; k < K; k++) // iterate over clusters
    {
        double s = 0;
        for (int i = 0; i < N; i++) // iterate over training examples
        {
            s += p_val[i * K + k];  // add probability of assignment of example 'i' to cluster 'k'
        }
        if (s==0) {
            s = 1e-52;
        }
        res[k] = s;
    }
}

/*
    Calculate the numerator part of covariance matrix formula.
*/
void calc_covariance_num(double *X, double *mean, double *cov, double *p_val, int K, int N, int D)
{
    // erase previous values of the covariance matrix for each cluster k
    for (int k = 0; k < K; k++)
    {
        int start_ind = k * D * D;
        for (int r = 0; r < D; r++)
            for (int c = 0; c < D; c++)
                cov[start_ind + r * D + c] = 0;
    }

    double offset = 1e-6;

    for (int k = 0; k < K; k++) // iterate over clusters
    {
        int start_ind = k * D * D;
        for (int i = 0; i < N; i++)         // iterate over training examples
            for (int r = 0; r < D; r++)     // iterate over row dimension
                for (int c = 0; c < D; c++) // iterate over column dimension
                {
                    // calculate the values of covariance matrix of cluster 'k' row 'r' and column 'c'
                    cov[start_ind + r * D + c] += p_val[i * K + k] * (X[i * D + r] - mean[k * D + r]) * (X[i * D + c] - mean[k * D + c]);

                    if (r == c) // add small offset if this is the main diagonal to avoid the singularity problem
                        cov[start_ind + r * D + c] += offset;
                }
    }
}

/*
    Function that updates the values of the covariance matrix for each cluster.
*/
void m_step_covariance(double *cov, double *sum_pij, int K, int D)
{
    for (int k = 0; k < K; k++) // iterate over clusters
    {
        int start_ind = k * D * D;

        for (int r = 0; r < D; r++) // iterate over dimensions
            for (int c = 0; c < D; c++)
                cov[start_ind + r * D + c] = cov[start_ind + r * D + c] / sum_pij[k];
    }
}

/*
    Calculate the numerator part of the mean formula.
*/
void calc_mean_num(double *X, double *p_val, double *res, int K, int N, int D)
{
    for (int k = 0; k < K; k++)         // iterate over clusters
        for (int i = 0; i < N; i++)     // iterate over training examples
            for (int j = 0; j < D; j++) // iterate over dimensions
                res[k * D + j] += p_val[i * K + k] * X[i * D + j];
}

/*
    Function that updates the values of mean for each cluster.
*/
void m_step_mean(double *mean, double *mean_nom, double *sum_pij, int K, int D)
{
    for (int k = 0; k < K; k++)     // iterate over clusters
        for (int j = 0; j < D; j++) // iterate over dimensions
            // calculate the value of mean of cluster 'k' at the dimension 'j'
            mean[k * D + j] = mean_nom[k * D + j] / sum_pij[k];
}

/*
    Function that updates the values of weights for each cluster.
*/
void m_step_weights(double *sum_pij, double *weights, int K)
{
    double den = 0;
    for (int k = 0; k < K; k++)
        den += sum_pij[k];
    for (int k = 0; k < K; k++)
        weights[k] = sum_pij[k] / den;
}

void m_step(double *X, double *mean, double *cov, double *weights, double *p_val, int K, int N, int D)
{
    double *sum_pij = (double *)calloc(K, sizeof(double));
    calc_sum_pij(p_val, sum_pij, K, N);

    // update mean
    double *mean_num = (double *)calloc(K * D, sizeof(double));
    calc_mean_num(X, p_val, mean_num, K, N, D);
    m_step_mean(mean, mean_num, sum_pij, K, D);
    free(mean_num);

    // update covariance
    calc_covariance_num(X, mean, cov, p_val, K, N, D);
    m_step_covariance(cov, sum_pij, K, D);

    // update weights
    m_step_weights(sum_pij, weights, K);
    free(sum_pij);
}
