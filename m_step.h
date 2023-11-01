#ifndef EM_PROJECT_M_STEP_H
#define EM_PROJECT_M_STEP_H

#include "constants.h"

// run maximization step
void m_step(float X[N][D], float mean[K][D], float cov[K][D][D], float weights[K], float p_val[N][K]);

void calc_sum_pij(float p_val[N][K], float res[K], int rows_per_process);

void calc_mean_num(float X[N][D], float p_val[N][K], float res[K][D], int rows_per_process);

void m_step_mean(float mean[K][D], float mean_nom[K][D], float sum_pij[K]);

void calc_covariance_num(float X[N][D], float mean[K][D], float cov[K][D][D],
                         float p_val[N][K], int rows_per_process);

void m_step_covariance(float cov[K][D][D], float cov_num[K][D][D], float sum_pij[K]);

#endif //EM_PROJECT_M_STEP_H
