#ifndef EM_PROJECT_UTILS_H
#define EM_PROJECT_UTILS_H

//copy values of mean and covariance
void get_cluster_mean_cov(double *mean, double *cov, double *m_res, double *cov_res, int k, int D);

void free_em_data(double *X, double *mean, double *cov, double *weights, double *p_val);

#endif //EM_PROJECT_UTILS_H
