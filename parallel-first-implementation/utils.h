//
// Created by Olha Khomyn on 25/11/23.
//

#ifndef EM_PROJECT_UTILS_H
#define EM_PROJECT_UTILS_H

void get_cluster_mean_cov(float *mean, float *cov, float *m_res, float *cov_res, int k, int D);

void divide_rows(int* data_count, int* data_displ, int* p_count, int* p_displ,
                 int N, int D, int K, int comm_sz);

void free_em_data(float *X, float *mean, float *cov, float *weights, float *p_val);

void free_rows_data(int* data_count, int* data_displ, int* p_count, int* p_displ);

#endif //EM_PROJECT_UTILS_H
