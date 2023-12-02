#ifndef EM_PROJECT_UTILS_H
#define EM_PROJECT_UTILS_H

//copy values of mean and covariance
void get_cluster_mean_cov(double *mean, double *cov, double *m_res, double *cov_res, int k, int D);

// divide the matrix for each process
void divide_rows(int* data_count, int* data_displ, int* p_count, int* p_displ,
                 int N, int D, int K, int comm_sz);

void free_em_data(double *X, double *mean, double *cov, double *weights, double *p_val);

void free_rows_data(int* data_count, int* data_displ, int* p_count, int* p_displ);

#endif //EM_PROJECT_UTILS_H
