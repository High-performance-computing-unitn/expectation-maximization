//
// Created by Olha Khomyn on 10/11/23.
//

#ifndef EM_PROJECT_UTILS_H
#define EM_PROJECT_UTILS_H

void divide_rows(int* data_count, int* data_displ, int* p_count, int* p_displ,
                 int N, int D, int K, int comm_sz);

void free_em_data(float *X, float *mean, float *cov, float *weights, float *p_val);

void free_rows_data(int* data_count, int* data_displ, int* p_count, int* p_displ);

#endif //EM_PROJECT_UTILS_H
