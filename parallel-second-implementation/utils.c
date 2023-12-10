#include <stdlib.h>

/*
    Function that copies the values of mean and covariance
*/
void get_cluster_mean_cov(double *mean, double *cov, double *m_res, double *cov_res, int k, int D)
{
    int start_ind = k * D * D;
    for (int r = 0; r < D; r++)
        for (int d = 0; d < D; d++)
            cov_res[r * D + d] = cov[start_ind + r * D + d];

    for (int d = 0; d < D; d++)
        m_res[d] = mean[k * D + d];
}

void free_em_data(double *X, double *mean, double *cov, double *weights, double *p_val)
{
    free(X);
    free(weights);
    free(mean);
    free(cov);
    free(p_val);
}
